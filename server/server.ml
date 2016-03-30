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
  | "MESSAGE" -> (5,args)
  | _ -> (-1, args)
 else
 	(-1, [])


(* Transformation des deplacement en liste de ( color * dir ) *)
let isMoveList str =
	let r = Str.regexp "([RBJV][HBGD])*" in
		Str.string_match r str 0

let rec movement_of_string_rec str =
	if (String.length str) = 0 then
		[]
	else
		let first = String.sub str 0 1
		and second = String.sub str 1 1 in
		((GameState.make_color first),(GameState.make_dir second))::(movement_of_string_rec (String.sub str 2 (String.length str - 2)))

let movement_of_string (str:string) =
	if isMoveList str then begin
		print_endline "REUSSI";
		movement_of_string_rec str
	end
	else
	begin
		print_endline ("RATE : "^str);
		[]
	end

let bilan tours l =
		let rec create l=
			match l with
				[] -> ""
				| h::t -> "("^h.nom^","^(string_of_int h.score)^")"^(create t)
		in
		(string_of_int tours) ^ (create l)

let bienvenue user =
  "BIENVENUE/" ^ user^"/\n"

let connecte user =
  "CONNECTE/"^user^"/\n"

let session ()= 
  "SESSION/"^(GameState.wall_list())^"/\n"

let deconnexion user = 
  "DECONNEXION/" ^user^"/\n"
  
let vainqueur t = 
  "VAINQUEUR/" ^(bilan t !joueur_liste)^"/\n"

let tour t =
	"TOUR/"^(GameState.get_state ())^"/"^(bilan t !joueur_liste)^"/\n"
	
let tuastrouve () =
	"TUASTROUVE/\n"

let ilatrouve user coups =
	"ILATROUVE/"^user^"/"^(string_of_int coups)^"/\n"
	
let finreflexion () =
	"FINREFLEXION/\n"

let validation () =
	"VALIDATION/\n"
	
let echec user =
	"ECHEC/"^user^"/\n"

let nouvelEnchere users coups = 
	"NOUVELLEENCHERE/"^users^"/"^(string_of_int coups)^"/\n"

let finEnchere users coups = 
	"FINENCHERE/"^users^"/"^(string_of_int coups)^"/\n"

let sasolution users deplacements = 
	"SASOLUTION/"^users^"/"^deplacements^"/\n"

let bonne () =
	"BONNE/\n"
	
let mauvaise users =
	"MAUVAISE/"^users^"/\n"
	
let finreso () =
	"FINRESO/\n"
	
let troplong users =
	"TROPLONG/"^users^"/\n"

let message args =
	"MESSAGE/"^(List.hd args)^"/"^(List.nth args 1)^"/\n"
	
(*-----------------------------------*)
(*Fonctions de gestions de la session*)
(*-----------------------------------*)

(* Termine la session courante et demare la suivante si possible *)
let rec fin_session () =
	ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval =0.0; it_value =0.0});
	ignore(Sys.signal Sys.sigalrm Sys.Signal_default);
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

(* Fonction appelle lors d'un timeout de la phase de resolution du joueur actif *)
and end_reso _ =
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	
	liste_enchere := List.tl !liste_enchere;
	
	if (List.length !liste_enchere) =0 then begin
		let ite (playeur:joueur) = output_string playeur.outchan (finreso()); flush playeur.outchan in
			List.iter ite !joueur_liste;
			begin_reflexion ()
	end else begin
		let next = (List.hd !liste_enchere) in
		let ite (playeur:joueur) = output_string playeur.outchan (troplong next.username); flush playeur.outchan in
			List.iter ite !joueur_liste;
			ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle end_reso));
			ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value =60.0})
	end;
	
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL

(*Initialise les ressource pour le debut de la phase de resolution*)
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

(*Initialise les ressource pour le debut de la phase d'enchere*)
and begin_enchere () =
	phase := 2;
	ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle begin_reso));
	ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value =30.0})

(* fonction appele lors du timeout de la phase de reflexion *)
and timeout_reflexion _ =
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	if !phase = 1 then begin
		let timeout ench = output_string ench.outchan (finreflexion ()); flush ench.outchan in
		List.iter timeout !liste_enchere;
		begin_enchere()
	end else ();
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL

(* Fonction appele pour initialiser les ressources au debut de la phase de reflexion *)
and begin_reflexion () = 
	incr tourNum;
	GameState.new_puzzle ();
	phase := 1;
	let playToEnch (pla:joueur) =begin pla.playing <- true; create_enchere pla.id pla.nom pla.outchan end in
	liste_enchere :=List.map playToEnch !joueur_liste;
	
	ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle timeout_reflexion));
	let ite enche = output_string enche.outchan (tour !tourNum); flush enche.outchan in
	List.iter ite !liste_enchere;
	
	ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value = 300.0});
	
	
(* Fonction appele lors d'un timeout du debut de la session *) 
and lock_reflexion _ = 
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	begin_reflexion ();
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL

(* Initialise les ressources pour debuter une nouvelle session *)
and debut_session () =
	GameState.init_state "./conf/basegame.conf";
	let func (play:joueur) = output_string play.outchan (session()); flush play.outchan in
		List.iter func !joueur_liste;
		ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle lock_reflexion));
		ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value = 30.0 })
;;
(*--------------------------------------*)
(* Fonctions de Traitement des requetes *)
(*--------------------------------------*)
(* Fonction de traitement de la requete connexion *)
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

(* Fonction de traitement de la requete de deconnexion *)
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
  Mutex.lock mutex_phase;
  
  let rec removeFromEnchere enchL =
  	match enchL with
  	 [] -> []
  	|h::t -> if h.id = player.id then
  				t
  			else
  				(h::(removeFromEnchere t)) in
  liste_enchere := removeFromEnchere !liste_enchere;
  
  Unix.close player.socket;
  if !nbJoueur < 2 then
  	fin_session()
  else 
  	();
  Mutex.unlock mutex_phase;
  Mutex.unlock mutex_joueurL;;
  
(* Fonction de traitement de la requete enchere *)
let traitement_enchere player args =
  Mutex.lock mutex_phase;
  if !phase = 2 then
    if player.playing = true then
      begin
        let rec cost = int_of_string(List.nth args 1)
        and com_ench ench=
          if ench.id = player.id then begin
            output_string ench.outchan (validation());
            flush ench.outchan;
            end
          else begin output_string ench.outchan (nouvelEnchere player.nom cost);
          			flush ench.outchan
          		end
        in
        let rec remove l =
          match l with
            []   -> []
          |h::t -> if h.id = player.id then
              t
            else
              (h::(remove t))
        and replace (l:enchere list) =
          match l with
            [] ->
              begin
                output_string player.outchan "ERREUR: Vous ne participez pas au tour\n";
                flush player.outchan;
                []
              end
          | h::t ->
             if h.cout = -1 then
               let newEnchere = { username = player.nom; id = player.id; cout = cost; outchan = player.outchan}
               and newListe = remove (h::t) in
               begin
                 List.iter com_ench !liste_enchere;
                 (newEnchere::newListe)
               end
             else
               if h.cout < cost then
                 if h.id = player.id then
                   begin
                     output_string player.outchan (echec h.username);
                     flush player.outchan;
                     (h::t)
                   end
                 else
                   (h::(replace t))
               else
                 if h.cout = cost then
                   begin
                     output_string player.outchan (echec h.username);
                     flush player.outchan;
                     (h::t)
                   end
                 else begin
                   let newEnchere = { username = player.nom; id = player.id; cout = cost; outchan = player.outchan}
                   and newListe = remove (h::t) in
                   List.iter com_ench !liste_enchere;
                   (newEnchere::newListe)
                 end
        in
        liste_enchere :=replace !liste_enchere
      end
    else begin
      output_string player.outchan "REQUETE INVALIDE: Vous ne jouez pas ce tour\n";
      flush player.outchan
      end
  else begin
    output_string player.outchan "REQUETE INVALIDE: Pas en phase d'enchere\n";
    flush player.outchan
    end;
  Mutex.unlock mutex_phase
;;

(* Fonction de traitement de la requet solution de la phase reflexion *)
let traitement_solution_reflexion (player:joueur) args = 
	let coups =try  int_of_string (List.nth args 1) with _ -> -1 in
	if coups < 0 then begin
		output_string player.outchan "Requete Invalide lors de la phase de reflexion";
		flush player.outchan
	end else begin
		ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value = 0.0 });
		let rec trouve l =
			match l with
			 [] -> []
			|h::t -> if h.id = player.id then
						trouve t
					 else begin
					 	output_string h.outchan (ilatrouve player.nom coups);
					 	flush h.outchan;
					 	let tail = trouve t in
					 		h::tail
					 end
		and new_ench = { username = player.nom; id = player.id; outchan = player.outchan; cout = coups} in
		liste_enchere := new_ench::(trouve !liste_enchere);
		output_string player.outchan (tuastrouve ());
		flush player.outchan;
		begin_enchere ();
	end
;;

(* Fonction de traitement de la requete solution de resolution *)
let traitement_solution_resolution (player:joueur) args =
	let head = (List.hd !liste_enchere)
	and deplacement = List.nth args 1 in
	if head.id = player.id then
	let liste_move =movement_of_string deplacement in
		if (List.length liste_move) = 0 then begin
			output_string player.outchan "Requete invalide: ce n'est pas une liste de mouvement\n";
			flush player.outchan
		end else begin
			ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval =0.0; it_value = 0.0});
			let transmit_solution (ench:joueur) = output_string ench.outchan (sasolution player.nom deplacement); flush ench.outchan in
			List.iter transmit_solution !joueur_liste;
			if GameState.is_valid liste_move then begin
				let transmit_res (pla:joueur) = output_string pla.outchan (bonne ()); flush pla.outchan in
				List.iter transmit_res !joueur_liste;
				player.score <- player.score +1;
				if player.score  = scoreMax then
					fin_session ()
				else
					begin_reflexion ()
			end else if (List.length !liste_enchere)>1 then begin
					let rec nextPlayer = List.nth !liste_enchere 1
					and ite (pla:enchere) = output_string pla.outchan (mauvaise nextPlayer.username);
					flush pla.outchan in
					List.iter ite !liste_enchere;
					liste_enchere := List.tl !liste_enchere;
					ignore(Sys.signal Sys.sigalrm (Sys.Signal_handle end_reso));
					ignore(Unix.setitimer Unix.ITIMER_REAL {it_interval = 0.0; it_value = 60.0})
				end else begin
					let ite (pla:joueur) = output_string pla.outchan (finreso()); flush pla.outchan in
					List.iter ite !joueur_liste;
					begin_reflexion()
				end
	end else begin
				output_string player.outchan "Ce n'est pas votre tour de jouer\n";
				flush player.outchan;
	end
;;

(* Choisis quel traitement appliquer a la requete solution entre les deux disponible *)
let traitement_solution player args =
	Mutex.lock mutex_joueurL;
	Mutex.lock mutex_phase;
	let test () =match !phase with
	 1 -> traitement_solution_reflexion player args
	|3 -> traitement_solution_resolution player args
	|_ -> begin output_string player.outchan "Requete Invalide: Nous ne sommes ni en phase de reflexion ni en phase de resolution\n"; flush player.outchan end in
	test ();
	Mutex.unlock mutex_phase;
	Mutex.unlock mutex_joueurL;
;;
  
let traitement_message (player:joueur) args =
	let sendMessage (pla:joueur) =
		if pla.id = player.id then 
			()
		else begin
			output_string pla.outchan (message args);
			flush pla.outchan
		end in
	Mutex.lock mutex_joueurL;
	List.iter sendMessage !joueur_liste;
	Mutex.unlock mutex_joueurL;;


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
	ignore(Sys.signal Sys.sigalrm Sys.Signal_ignore);
  while true do
	try
    let(s, caller) = Unix.accept sock
    in
    ignore(Thread.create service s)
    with _ ->()
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
      | 5 -> traitement_message player args
      | _ ->
         begin 
           output_string player.outchan ("REQUETE INVALIDE : "^line^"\n");
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
      output_string outchan "REQUETE INVALIDE: attente d'une requete de la forme: CONNEXION/username\n"; 
  flush outchan
    end

let main ()=
	serveur_process (creer_serveur 10) joueur_service
;;

main ()
