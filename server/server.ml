(*-----------------------------------*)
(* Ressources *)
(*-----------------------------------*)

type joueur = {
    nom: string;
    id : int;
    socket: Unix.file_descr;
    score: int;
    inchan: in_channel;
    outchan: out_channel
  }
let cpt_id = ref 0

let creer_joueur user sock inc out=
  incr cpt_id;
  {
    nom = user;
    id = !cpt_id;
    score = 0;
    socket = sock;
    inchan = inc;
    outchan = out
  }

let joueur_liste = ref [] 
and nbJoueur = ref 0
and mutex_joueurL = Mutex.create ()

(*-----------------------------------*)
(* Traitement des requetes *)
(*-----------------------------------*)

let received_request req =
  let splited = Str.split (Str.regexp "/") req in
  let intitule = List.hd splited
  and args = List.tl splited in
  match intitule with
    "CONNEXION" -> (1, args)
  | "SORT" -> (2, args)
  | "ENCHERE" -> (3, args)
  | "SOLUTION" -> (4, args)
  | _ -> (-1, args)

let bienvenue user =
  "BIENVENUE/" ^ user^"/"

let connecte user =
  "CONNECTE/"^user^"/"

let sorti user =
  "SORTI/" ^user^"/"

let session = 
  "SESSION/"(*^GameState.wall_list*)^"/"

let deconnexion user = 
  "DECONNEXION/" ^user^"/"

let traitement_connecte player =
  Mutex.lock mutex_joueurL;
  joueur_liste := player :: !joueur_liste;
  incr nbJoueur;
  let rec hello l =
    match l with
      h :: t -> output_string h.outchan (connecte player.nom); h::(hello t);
    | [] -> output_string player.outchan (bienvenue player.nom); player::[]
  in joueur_liste := hello !joueur_liste;
     Mutex.unlock mutex_joueurL;;

let traitement_sortie player= 
  Mutex.lock mutex_joueurL;
  nbJoueur := !nbJoueur -1;
  let rec remove_and_warn li =
    match li with
      h::t -> if (h.id = player.id) then remove_and_warn t
              else
                begin
                  output_string h.outchan (sorti player.nom); 
                  h::(remove_and_warn t)
                end
    | [] -> []
  in joueur_liste := remove_and_warn !joueur_liste;
  Mutex.unlock mutex_joueurL;;
  
(*-----------------------------------*)
(* Serveurs Et Threads *)
(*-----------------------------------*)

let creer_serveur max_co = 
  let sock = Unix.socket Unix.PF_INET Unix.SOCK_STREAM 0
  and addr = Unix.inet_addr_of_string "127.0.0.1"
  in
  Unix.bind sock(Unix.ADDR_INET(addr,2016));
  Unix.listen sock max_co;
  sock;;

let serveur_process sock service=
  while true do
    let(s, caller) = Unix.accept sock
    in
    ignore(Thread.create service s)
  done;;

let boucle_joueur player =
  try
    while true do
      let line = input_line player.inchan in
      let (num_req, args) = received_request line in
      match num_req with
	2 -> traitement_sortie player; raise Exit;
      | 3 -> () (* todo*)
      | 4 -> () (* todo*)
      | _ ->
         begin 
           output_string player.outchan ("REQUETE INVALIDE : "^line);
           flush player.outchan
         end
    done;
  with Exit-> ();;

let joueur_service sock=
  let inchan = Unix.in_channel_of_descr sock
  and outchan = Unix.out_channel_of_descr sock in
  let line = input_line inchan in
  let (num_req, args) = received_request line in
  if num_req = 1 then
    let player = (creer_joueur (List.nth args 0) sock inchan outchan) in
    traitement_connecte player;
    boucle_joueur player
  else
    begin 
      output_string outchan "REQUETE INVALIDE: attente d'une requete de la forme: CONNEXION/username"; 
  flush outchan
    end
