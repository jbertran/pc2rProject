type color = C_R | C_J | C_V | C_B
type dir = H | B | G | D
type game 

val make_dir : string -> dir
val make_color : string -> color

(* Initialisation de l'état *)
val init_state : string -> unit
val new_puzzle : unit -> unit

(* Récupération de la liste de murs *) 
val wall_list : unit -> string
val walls : int -> int -> dir list
val hasWall : int -> int -> dir -> bool
val addWall : int -> int -> dir -> unit

(* Gestion du robot *)
val robot : color -> (int * int)
val move_robot : (int * int) -> dir -> (int * int)

(* But *)
val goal : unit -> (int * int)

(* Copie de l'état initial *)
val copy_state : unit -> game 
val get_state : unit -> string
val is_valid : (color * dir) list -> bool
