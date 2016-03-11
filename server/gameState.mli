module GameState = 
  sig
    type Mur = H 
             | B
             | G 
             | D
    type Coords = 
      {
        mutable x : int;
        mutable y : int;
      }
    type Game = 
      {
        (* Robots *)
        robot_j : Coords;
        robot_v : Coords;
        robot_b : Coords;
        robot_r : Coords;

        (* Destinations *)
        dest_j : Coords;
        dest_v : Coords;
        dest_b : Coords;
        dest_r : Coords;

        (* Matrice murs *)
        murs : (Mur list) array array;
      }
    val init_state: unit -> Game;
  end 
