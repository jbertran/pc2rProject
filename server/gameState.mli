    type color = R | G | V | B
    type dir = H | B | G | D
    type game = 
      {
        (* Robots *)
        robots: (int * int) array;
        (* Destinations *)
        dests: (int * int) array;
        (* Matrice murs *)
        murs : dir list array array;
      }
    val init_state : string -> unit
    val wall_list : unit -> string
    val walls : int -> int -> dir list
    val hasWall : int -> int -> dir -> bool
    val robot : color -> (int * int)
    val move_robot : color -> dir -> unit
    val goal : color -> (int * int)
