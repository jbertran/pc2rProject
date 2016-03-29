(*-----------------------------------*)
(*------------- Ressources ----------*)
(*-----------------------------------*)

type joueur = {
    nom: string;
    id : int;
    socket: Unix.file_descr;
    mutable score: int;
    inchan: in_channel;
    outchan: out_channel;
    mutable playing :bool
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
    outchan = out;
    playing = false
  }

let joueur_liste:joueur list ref = ref [] 
and nbJoueur = ref 0
and mutex_joueurL = Mutex.create ()

(* Ressources session *)
type enchere = {
	id: int;
	username : string;
	mutable cout : int;
	outchan : out_channel
}

let create_enchere uid name outc = {
	id = uid;
	username =name;
	outchan = outc;
	cout = -1
}

let phase =ref 0 (*0: hors session, 1: reflexion, 2: echere, 3: resolution *)
and liste_enchere = ref []
and tourNum = ref 0
and mutex_phase = Mutex.create ()
and scoreMax = 3

(*----------------------------------------*)
(* Fonctions de manipulation des requetes *)
(*----------------------------------------*)

let received_request req =
  let splited = Str.split (Str.regexp "/") req in
  if (List.length splited) > 0 then
  let intitule = List.hd splited
  and args = List.tl splited in
  match intitule with
    "CONNEXION" -> (1, args)
  | "SORT" -> (2, args)
  | "ENCHERE" -> (3, args)
  | "SOLUTION" -> (4, args)
  | _ -> (-1, args)
 else
 	(-1, [])


let bilan tours l =
		let rec create l=
			match l with
				[] -> ""
				| h::t -> "("^h.nom^","^(string_of_int h.score)^")"^(create t)
		in
		(string_of_int tours) ^ (create l)

let bienvenue user =
  "BIENVENUE/" ^ user^"/"

let connecte user =
  "CONNECTE/"^user^"/"

let session ()= 
  "SESSION/"^(GameState.wall_list())^"/"

let deconnexion user = 
  "DECONNEXION/" ^user^"/"
  
let vainqueur t = 
  "VAINQUEUR/" ^(bilan t !joueur_liste)^"/"

let tour t =
	"TOUR/"^(GameState.get_state ())^"/"^(bilan t !joueur_liste)^"/"
	
let tuastrouve () =
	"TUASTROUVE/"

let ilatrouve user coups =
	"ILATROUVE/"^user^"/"^(string_of_int coups)
	
let finreflexion () =
	"FINREFLEXION/"

let validation () =
	"VALIDATION/"
	
let echec user =
	"ECHEC/"^user^"/"

let nouvelEnchere users coups = 
	"NOUVELLEENCHERE/"^users^"/"^(string_of_int coups)^"/"

let finEnchere users coups = 
	"FINENCHERE/"^users^"/"^(string_of_int coups)^"/"

let sasolution users deplacements = 
	"SASOLUTION/"^users^"/"^deplacements^"/"

let bonne () =
	"BONNE/"
	
let mauvaise users =
	"MAUVAISE/"^users^"/"
	
let finreso () =
	"FINRESO/"
	
let troplong users =
	"TROPLONG/"^users^"/"
	
(*-----------------------------------*)
(*Fonctions de gestions de la session*)
(*-----------------------------------*)
let rec fin_session () =
	if !phase = 0 then
		()
	else begin
		liste_enchere := [];
		phase := 0;
		tourNum := 0
	end;
	let ite (playeur:joueur) = output_string playeur.outchan (vainqueur !tourNum); flush playeur.outchan in
	List.iter ite !joueur_liste;
	if !nbJoueur > 1 then
		debut_session()
	else
		()

and end_reso _ =
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	
	liste_enchere := List.tl !liste_enchere;
	
	if (List.length !liste_enchere) =0 then begin
		let ite (playeur:joueur) = output_string playeur.outchan (finreso()); flush playeur.outchan in
			List.iter ite !joueur_liste;
			debut_session ()
	end else begin
		let next = (List.hd !liste_enchere) in
		let ite (playeur:joueur) = output_string playeur.outchan (troplong next.username); flush playeur.outchan in
			List.iter ite !joueur_liste;
			ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle end_reso));
			ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value =60.0})
	end;
	
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL

and begin_reso _ =
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	phase := 3;
	
	let ite ench = 
		let first = (List.hd !liste_enchere) in
		output_string ench.outchan (finEnchere first.username first.cout); flush ench.outchan in
	List.iter ite !liste_enchere;
	ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle end_reso));
	ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value =60.0});
	
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL


and begin_enchere () =
	phase := 2;
	ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle begin_reso));
	ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value =30.0})


and timeout_reflexion _ =
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	if !phase = 1 then
		begin_enchere()
	else ();
	let timeout ench = output_string ench.outchan (finreflexion ()); flush ench.outchan in
	List.iter timeout !liste_enchere;
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL

and begin_reflexion _ = 
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	
	incr tourNum;
	GameState.new_puzzle ();
	phase := 1;
	let playToEnch (pla:joueur) =begin pla.playing <- true; create_enchere pla.id pla.nom pla.outchan end in
	liste_enchere :=List.map playToEnch !joueur_liste;
	
	ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle timeout_reflexion));
	let ite enche = output_string enche.outchan (tour !tourNum); flush enche.outchan in
	List.iter ite !liste_enchere;
	
	ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value = 300.0});
	
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL

and debut_session () =
	GameState.init_state "./conf/basegame.conf";
	let func (play:joueur) = output_string play.outchan (session()); flush play.outchan in
		List.iter func !joueur_liste;
		ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle begin_reflexion));
		ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value = 30.0 })
;;
(*--------------------------------------*)
(* Fonctions de Traitement des requetes *)
(*--------------------------------------*)

let traitement_connecte (player:joueur) =
  Mutex.lock mutex_joueurL;
  incr nbJoueur;
  let rec hello (l:joueur list) =
    match l with
      h :: t ->begin output_string h.outchan (connecte player.nom);
      			flush h.outchan;
      			h::(hello t)
      			end
    | [] -> begin output_string player.outchan (bienvenue player.nom);
    			flush player.outchan;
    		player::[]
    		end
  in joueur_liste := hello !joueur_liste;
  	 Mutex.lock mutex_phase;
  	 if !nbJoueur = 2 && !phase = 0 then
  	 	debut_session()
  	 else 
  	 	if !nbJoueur > 2 then begin
  	 		output_string player.outchan (session ());
  	 		flush player.outchan
  	 	end else ();
  	 Mutex.unlock mutex_phase;
     Mutex.unlock mutex_joueurL;;

let traitement_sortie (player:joueur)= 
  Mutex.lock mutex_joueurL;
  nbJoueur := !nbJoueur -1;
  let rec remove_and_warn (li:joueur list) =
    match li with
      h::t -> if (h.id = player.id) then remove_and_warn t
              else
                begin
                  output_string h.outchan (deconnexion player.nom);
                  flush h.outchan;
                  h::(remove_and_warn t)
                end
    | [] -> []
  in joueur_liste := remove_and_warn !joueur_liste;
  Mutex.unlock mutex_joueurL;
  Unix.close player.socket;
  
  Mutex.lock mutex_joueurL;
  Mutex.lock mutex_phase;
  if !nbJoueur < 2 then
  	fin_session()
  else 
  	();
  Mutex.unlock mutex_phase;
  Mutex.unlock mutex_joueurL;;
  
let traitement_enchere player args =
  Mutex.lock mutex_phase;
  if !phase = 2 then
    if player.playing = true then
      begin
        let rec cost = int_of_string(List.nth args 1)
        and com_ench ench=
          if ench.id = player.id then begin
            output_string ench.outchan (tuastrouve());
            flush ench.outchan;
            end
          else begin output_string ench.outchan (ilatrouve player.nom cost);
          			flush ench.outchan
          		end
        in
        let rec remove l =
          match l with
            []   -> []
          |h::t -> if h.id = player.id then
              t
            else
              h::(remove t)
        and replace (l:enchere list) =
          match l with
            [] ->
              begin
                output_string player.outchan "ERREUR: Vous ne participez pas au tour";
                flush player.outchan;
                []
              end
          | h::t ->
             if h.cout = -1 then
               let newEnchere = { username = player.nom; id = player.id; cout = cost; outchan = player.outchan}
               and newListe = remove (h::t) in
               begin
                 List.iter com_ench !liste_enchere;
                 newEnchere::newListe
               end
             else
               if h.cout < cost then
                 if h.id = player.id then
                   begin
                     output_string player.outchan (echec h.username);
                     flush player.outchan;
                     h::t
                   end
                 else
                   replace t
               else
                 if h.cout = cost then
                   begin
                     output_string player.outchan (echec h.username);
                     flush player.outchan;
                     h::t
                   end
                 else begin
                   let newEnchere = { username = player.nom; id = player.id; cout = cost; outchan = player.outchan}
                   and newListe = remove (h::t) in
                   List.iter com_ench !liste_enchere;
                   newEnchere::newListe
                 end
        in
        liste_enchere :=replace !liste_enchere
      end
    else begin
      output_string player.outchan "REQUETE INVALIDE: Vous ne jouez pas ce tour";
      flush player.outchan
      end
  else begin
    output_string player.outchan "REQUETE INVALIDE: Pas en phase d'enchere";
    flush player.outchan
    end;
  Mutex.unlock mutex_phase
;;

let traitement_solution player args = ()
  

(*-----------------------------------*)
(*--------Serveurs Et Threads--------*)
(*-----------------------------------*)

let creer_serveur max_co = 
  let sock = Unix.socket Unix.PF_INET Unix.SOCK_STREAM 0
  and addr = Unix.inet_addr_of_string "127.0.0.1"
  in
  Unix.bind sock(Unix.ADDR_INET(addr,2016));
  Unix.listen sock max_co;
  sock;;

let serveur_process sock service=
	Unix.signal Sys.sigalrm Sys.Signal_ignore;
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
      | 3 -> traitement_enchere player args
      | 4 -> traitement_solution player args
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

let main ()=
	serveur_process (creer_serveur 10) joueur_service
;;

main ()
