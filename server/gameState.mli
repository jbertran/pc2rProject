module GameState = 
  sig
    type Color = R | G | V | B     
    type Dir = H | B | G | D
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
        murs : (Dir list) array array;
      }
    val init_state: unit -> Game
    val walls: int * int -> Dir list
    val hasWall: int * int * dir -> bool
    val robot: Color -> Coords
    val move_robot: Color * Dir -> unit
    val goal: Color -> Coords
  end 
