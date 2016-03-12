(**************************)
(******    TYPES      *****)
(**************************)
type color = C_R | C_J | C_V | C_B;;
type dir = H | B | G | D;;
type game = 
  {
    (* Robots *)
    robot_cible: color ref;
    cible : (int * int) ref;
    robots: (int * int) array;
    (* Matrice murs *)
    murs : (dir list) array array;
  };;
  
(**************************)
(******    GLOBALS   ******)
(**************************)
let game_width = 16;;
let game_height = 16;;
let empty_state = 
  {
    robot_cible = ref C_B;
    cible = ref (0, 0);
    robots = Array.make 4 (0, 0);
    murs = (Array.make_matrix game_height game_width []); 
  };;
let game_state = empty_state;;
  
let rec present (a, b) l = 
  match l with
    (x, y)::t -> if a == x && b == y then true else present (a, b) t
  | [] -> false

let init_pos array size plist = 
  for i=0 to (size - 1) do
    let rec get_rnd () = 
      let a = Random.int game_height
      and b = Random.int game_width in
      if (present (a, b) !plist) then (get_rnd ()) else (a, b)
    in
    let c = (get_rnd ()) in
    plist := c::!plist;
    array.(i) <- c;
  done;;

let copy_state () = 
  let newmurs = Array.copy game_state.murs in
  for i = 0 to (game_height - 1) do
    newmurs.(i) <- Array.copy game_state.murs.(i);
  done;
  {
    robot_cible = ref !(game_state.robot_cible);
    cible = ref !(game_state.cible);
    robots = Array.copy game_state.robots;
    murs = newmurs
  }

let addWall x y dir = 
  game_state.murs.(x).(y) <- dir::game_state.murs.(x).(y);;


let set_walls_from_file fp =
  ();;
(*
  let wall_list = Tools.read_walls_file fp in
  let rec set_walls l= 
    match l with 
      (x, y, d)::t -> addWall x y d; set_walls t
    | [] -> ()
  in set_walls wall_list
;;*)

let init_state confFile = 
  (* Murs extérieurs *)
  for i = 0 to (game_height - 1) do
    addWall i 0 G;
    addWall i (game_width - 1) D;
  done;
  for j = 0 to (game_width - 1) do
    addWall 0 j H;
    addWall (game_height - 1) j B;
  done;
  (* Robots et destination *)
  let poslist = ref [] in
  init_pos game_state.robots 4 poslist;
  let r_cible = Random.int 4 in
  let r_color = match r_cible with 0 -> C_R | 1 -> C_J | 2 -> C_V | 3 -> C_B in
  game_state.robot_cible := r_color;
  game_state.cible := (0, 0);
  (* Murs intérieurs *)
  set_walls_from_file confFile;;

let walls x y =
  game_state.murs.(x).(y);;

let hasWall x y dir = 
  let rec hasWall_list l = 
    match l with
      h::t -> if (h == dir) then true else hasWall_list t
    | [] -> false
  in
  hasWall_list game_state.murs.(x).(y);;

let rec print_walls strp x y l =
  match l with
    h::t -> 
    begin 
      let c =
        match h with
          H -> "H"
        | B -> "B"
        | G -> "G"
        | D -> "D"
      in
      strp := !strp ^ "(" ^ (string_of_int x) ^ "," ^ (string_of_int y) ^ "," ^ c ^ ")";
      print_walls strp x y t;
    end
  | [] -> ()
            
let wall_list () = 
  let strp = ref "" in
  for i = 0 to (game_height - 1) do
    for j = 0 to (game_width - 1) do
      print_walls strp i j game_state.murs.(i).(j);
    done;
  done;
  !strp;;

let goal () = 
  !(game_state.cible)
;;

let robot col = 
  match col with
    C_R -> game_state.robots.(0)
  | C_B -> game_state.robots.(1)
  | C_J -> game_state.robots.(2)
  | C_V -> game_state.robots.(3)
;;
  
let rec move_robot pos dir = 
  let x, y = pos in
  match dir with 
    H ->  
    if ((hasWall x y H) || (hasWall (x-1) y B)); then
      (x, y)
    else
      move_robot ((x-1), y) dir
  | B ->
     if ((hasWall x y B) || (hasWall (x+1) y H)); then
       (x, y)
     else
       move_robot ((x+1), y) dir
  | G ->
     if ((hasWall x y G) || (hasWall x (y-1) D)); then
       (x, y)
     else
       move_robot (x, (y-1)) dir
  | D -> 
     if ((hasWall x y D) || (hasWall x (y+1) G)); then
       (x, y)
     else
       move_robot (x, (y+1)) dir
;;

let set_robot gs pos col = 
  let (x, y) = pos in
  match col with 
    C_R -> gs.robots.(0) <- (x, y)
  | C_B -> gs.robots.(0) <- (x, y)
  | C_J -> gs.robots.(0) <- (x, y)
  | C_V -> gs.robots.(0) <- (x, y)
;;

let get_state () =
  let robots = ref "" in
  for i=0 to 3; do
    let (x, y) = game_state.robots.(i) in
    robots := !robots ^ (string_of_int x) ^ "," ^ (string_of_int y) ^ ",";
  done;
  let (xc, yc) = !(game_state.cible)
  and col = match !(game_state.robot_cible) with C_R -> "R"  | C_J -> "J" 
                                          | C_V -> "V"  | C_B -> "B" 
  in
  "(" ^ !robots ^ (string_of_int xc) ^ "," ^ (string_of_int yc) ^ "," ^ col ^ ")"
;;

let is_valid movelist = 
  let tmpstate = copy_state () in
  let rec valid_rec l = 
    match l with
      (col, d)::tail -> 
      let (xm, ym) = move_robot (robot col) d in
      set_robot tmpstate (xm, ym) col;
      valid_rec tail
    | [] -> 
       let (xc, yc) = !(tmpstate.cible)
       and (xr, yr) = (robot !(tmpstate.robot_cible)) in
       ((xc == xr) && (yc == yr))
  in valid_rec movelist
;;
    
