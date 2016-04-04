open Str

(**************************)
(******    TYPES      *****)
(**************************)
type color = C_R | C_J | C_V | C_B;;
type dir = H | B | G | D;;
type game = 
  {
    mutable height : int;
    mutable width : int;
    (* Robots *)
    mutable robot_cible: color;
    mutable cible : (int * int);
    robots: (int * int) array;
    (* Matrice murs *)
    mutable murs : (dir list) array array;
  };;
exception Unknown_color of string;;
exception Unknown_direction of string;;

(**************************)
(******    GLOBALS   ******)
(**************************)
let empty_state = 
  {
    height = 2;
    width = 2;
    robot_cible = C_B;
    cible = (0, 0);
    robots = Array.make 4 (0, 0);
    murs = (Array.make_matrix 2 2 []); 
  };;

let game_state = empty_state;;


(**************************)
(******   HELPERS    ******)
(**************************)

let make_dir str =
  match str with
    "H" -> H
  | "B" -> B
  | "G" -> G
  | "D" -> D
  | _ -> raise (Unknown_direction "Wrong direction");;
    
let make_color str = 
  match str with 
    "R" -> C_R
  | "J" -> C_J 
  | "V" -> C_V 
  | "B" -> C_B
  | _ -> raise (Unknown_color "Wrong color");;

let read_walls_file filepath = 
  let reader = open_in filepath 
  and line = ref "" 
  and wall_list = ref [] in
  try 
    line := input_line reader;
    let h::w::[] = List.map int_of_string (split (regexp "[ \t]+") !line) in
    line := input_line reader;
    while (not (string_match (regexp "-1 -1") !line 0)); do
      let sp1::sp2::sp3::[] = split (regexp " ") !line in
      let d = make_dir sp3 in
      wall_list := ((int_of_string sp1), (int_of_string sp2), d)::(!wall_list);
      line := input_line reader
    done;
    close_in reader;
    (h, w, !wall_list)
  with 
  | End_of_file 
  | Match_failure _ -> 
     close_in reader;
     prerr_string "File format error!";
     (-1, -1, []);;

let rec present (a, b) l = 
  match l with
    (x, y)::t -> if a == x && b == y then true else present (a, b) t
  | [] -> false

(* Initialiser les robots au hasard *)
let init_pos array size plist = 
  for i=0 to (size - 1) do
    let rec get_rnd () = 
      let a = Random.int game_state.height
      and b = Random.int game_state.width in
      if (present (a, b) !plist) then (get_rnd ()) else (a, b)
    in
    let c = (get_rnd ()) in
    plist := c::!plist;
    array.(i) <- c;
  done;;

let copy_state () = 
  let newmurs = Array.copy game_state.murs in
  for i = 0 to (game_state.height - 1) do
    newmurs.(i) <- Array.copy game_state.murs.(i);
  done;
  {
    height = game_state.height;
    width = game_state.width;
    robot_cible = game_state.robot_cible;
    cible = game_state.cible;
    robots = Array.copy game_state.robots;
    murs = newmurs
  }

let addWall x y dir = 
  game_state.murs.(x).(y) <- dir::game_state.murs.(x).(y);;

let rec set_walls wallList =
    match wallList with 
      (x, y, d)::t -> addWall x y d; set_walls t
    | [] -> ()
;;

let init_state confFile = 
  let (h, w, wallList) = read_walls_file confFile in
  game_state.height <- h;
  game_state.width <- w;
  (* Préparation des murs *)
  game_state.murs <- (Array.make_matrix h w []);
  (* Murs extérieurs *)
  for i = 0 to (game_state.height - 1) do
    addWall 0 i G;
    addWall (game_state.width - 1) i D;
  done;
  for j = 0 to (game_state.width - 1) do
    addWall j 0 H;
    addWall j (game_state.height - 1) B;
  done;
  (* Robots et destination *)
  let poslist = ref [] in
  init_pos game_state.robots 4 poslist;
  let r_cible = Random.int 4 in
  let r_color = match r_cible with 0 -> C_R | 1 -> C_J | 2 -> C_V | 3 -> C_B in
  game_state.robot_cible <- r_color;
  game_state.cible <- (0, 0);
  (* Murs intérieurs *)
  set_walls wallList;;

let rec print_walls strp x y l =
  let append strp c = 
    strp := !strp ^ "(" ^ (string_of_int x) ^ "," ^ (string_of_int y) ^ "," ^ c ^ ")"
  in
  match l with
    h::t -> 
    begin 
      match h with
        H -> if (x == 0) then print_walls strp x y t else append strp "H"
      | B -> if (x == (game_state.height - 1)) then print_walls strp x y t 
               else append strp "B"
      | G -> if (y == 0) then print_walls strp x y t else append strp "G"
      | D -> if (y == (game_state.width - 1)) then print_walls strp x y t
             else append strp "D"
    end
  | [] -> ()
            
let wall_list () = 
  let strp = ref "" in
  for i = 0 to (game_state.height - 1) do
    for j = 0 to (game_state.width - 1) do
      print_walls strp i j game_state.murs.(i).(j);
    done;
  done;
  !strp;;

(**************************)
(******  ACCESSORS   ******)
(**************************)

let goal () = 
  game_state.cible
;;

let colToInt col = 
  match col with
    C_R -> 0
  | C_B -> 1
  | C_J -> 2
  | C_V -> 3

let robot col = 
  match col with
    C_R -> game_state.robots.(0)
  | C_B -> game_state.robots.(1)
  | C_J -> game_state.robots.(2)
  | C_V -> game_state.robots.(3)
;;

let hasRobot x y = 
  let ret = ref false in
  for i=0 to 3 do
    let (xr, yr) = game_state.robots.(i) in
    if ((xr == x) && (yr == y)) then ret := true else ()
  done;
  !ret;;

let get_state () =
  let robots = ref "" in
  for i=0 to 3; do
    let (x, y) = game_state.robots.(i) in
    robots := !robots ^ (string_of_int x) ^ "," ^ (string_of_int y) ^ ",";
  done;
  let (xc, yc) = game_state.cible
  and col = match game_state.robot_cible with C_R -> "R"  | C_J -> "J" 
                                          | C_V -> "V"  | C_B -> "B" 
  in
  "(" ^ !robots ^ (string_of_int xc) ^ "," ^ (string_of_int yc) ^ "," ^ col ^ ")"
;;

let walls x y =
  game_state.murs.(x).(y);;

let hasWall x y dir = 
  let rec hasWall_list l = 
    match l with
      h::t -> if (h == dir) then true else hasWall_list t
    | [] -> false
  in
  hasWall_list game_state.murs.(x).(y);;
  

(**************************)
(******   MOVEMENT   ******)
(**************************)

let rec move_robot pos d = 
  let x, y = pos in
  match d with 
    H ->  
    if ((hasWall x y H) || (hasWall x (y-1) B) || (hasRobot x (y-1))); then
      (x, y)
    else
      move_robot (x, (y-1)) d
  | B ->
     if ((hasWall x y B) || (hasWall x (y+1) H) || (hasRobot x (y+1))); then
       (x, y)
     else
       move_robot (x, (y+1)) d
  | G ->
     if ((hasWall x y G) || (hasWall (x-1) y D) || (hasRobot (x-1) y)); then
       (x, y)
     else
       move_robot ((x-1), y) d
  | D -> 
     if ((hasWall x y D) || (hasWall (x+1) y G) || (hasRobot (x+1) y)); then
       (x, y)
     else
       move_robot ((x+1), y) d
;;

let set_robot gs pos col = 
  let (x, y) = pos in
  match col with 
    C_R -> gs.robots.(0) <- (x, y)
  | C_B -> gs.robots.(1) <- (x, y)
  | C_J -> gs.robots.(2) <- (x, y)
  | C_V -> gs.robots.(3) <- (x, y)
;;

let new_target () =
  let targetList = [(0, 0); (15, 0); (0, 15); (15, 15)] in
  let pos = Random.int 4 in
  (List.nth targetList pos)
;;

(* Initialiser robots, robot cible et cible au hasard *)
let new_puzzle () =
  let cnum = Random.int 4 in
  let color = match cnum with
      0 -> C_R
    | 1 -> C_J
    | 2 -> C_V
    | 3 -> C_B
  in
  game_state.robot_cible <- color;
  let pl = ref [] in
  init_pos game_state.robots 4 pl;
  game_state.cible <- (new_target ())
;;


(**************************)
(***** SOL. CHECKING ******)
(**************************)


let is_valid movelist = 
  let tmpstate = copy_state () in
  let rec valid_rec l = 
    match l with
      (col, d)::tail -> 
      let (xm, ym) = move_robot (tmpstate.robots.(colToInt col)) d in
      begin
      set_robot tmpstate (xm, ym) col;
      valid_rec tail
      end
    | [] -> 
       let (xc, yc) = tmpstate.cible
       and (xr, yr) = tmpstate.robots.(colToInt tmpstate.robot_cible) in
       ((xc == xr) && (yc == yr))
  in valid_rec movelist
;;
    
