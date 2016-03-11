    (**************************)
    (******    TYPES      *****)
    (**************************)
    type color = R | G | V | B;;
    type dir = H | B | G | D;;
    type game = 
      {
        (* Robots *)
        robots: (int * int) array;
        (* Destinations *)
        dests: (int * int) array;
        (* Matrice murs *)
        murs : (dir list) array array;
      };;
      
    (**************************)
    (******    GLOBALS   ******)
    (**************************)
    let empty_state = 
      {
        robots = Array.make 4 (0, 0);
        dests = Array.make 4 (0, 0);
        murs = (Array.make_matrix 16 16 []); 
      };;
    let game_state = empty_state;;
    let game_width = 16;;
    let game_height = 16;;
      
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

    let addWall x y dir = 
      game_state.murs.(x).(y) <- dir::game_state.murs.(x).(y);;

    let set_walls_from_file fp =
      print_string ("Placeholder pour lire "^fp);;

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
      (* Robots et destinations *)
      let poslist = ref [] in
      init_pos game_state.robots 4 poslist;
      init_pos game_state.dests 4 poslist;
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

    let robot col = 
      match col with
        R -> game_state.robots.(0)
      | G -> game_state.robots.(1)
      | V -> game_state.robots.(2)
      | B -> game_state.robots.(3)
    ;;

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

    let goal col = 
      match col with
        R -> game_state.dests.(0)
      | G -> game_state.dests.(1)
      | V -> game_state.dests.(2)
      | B -> game_state.dests.(3)
    ;;
     
    let move_robot col dir = 
      print_string "Placeholder move_robot"
    ;;
