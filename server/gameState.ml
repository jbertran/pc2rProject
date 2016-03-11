

let init_state = 
  {
    (* Positions robots randomisées *)
    robot_j = random_coords ();
    robot_v = random_coords ();
    robot_b = random_coords ();
    robot_r = random_coords ();

    (* Destinations randomisées *)
    dest_j = random_coords ();
    dest_v = random_coords ();
    dest_b = random_coords ();
    dest_r = random_coords ();
    
    (* Matrice vide 
       Récupérer les bons murs (cf. jeu) *)
    murs = (make_matrix 16 16); 
  };;


