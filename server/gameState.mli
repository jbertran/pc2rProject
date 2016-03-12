type color = C_R | C_J | C_V | C_B
type dir = H | B | G | D
type game = 
  {
    (* Robots *)
    mutable robot_cible : color;
    mutable cible : (int * int);
    robots: (int * int) array;
    (* Matrice murs *)
    murs : dir list array array;
  }

(* Initialisation de l'état *)
val init_state : string -> unit
val set_walls_from_file : string -> unit

(* Récupération de la liste de murs *) 
val wall_list : unit -> string
val walls : int -> int -> dir list
val hasWall : int -> int -> dir -> bool

(* Gestion du robot *)
val robot : color -> (int * int)
val move_robot : (int * int) -> dir -> (int * int)

(* But *)
val goal : unit -> (int * int)

(* Copie de l'état initial *)
val copy_state : unit -> game 
val get_state : unit -> string
val is_valid : (color * dir) list -> bool
