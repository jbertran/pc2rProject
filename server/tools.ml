open Str;;

let read_walls_file filepath = 
  let reader = open_in filepath 
  and line = ref "" 
  and wall_list = ref [] in
  try 
    line := input_line reader;
    let h::w::[] = split (regexp "[ \t]+") !line in
    while (not (string_match (regexp "-1 -1") !line 0)); do
      let sp1::sp2::sp3::[] = split (regexp "[ \t]+") !line in
      let d = match sp3 with "H" -> GameState.H
                           | "B" -> GameState.B
                           | "G" -> GameState.G
                           | "D" -> GameState.D
                           | _ -> GameState.D
      in
      wall_list := ((int_of_string sp1), (int_of_string sp2), d)::(!wall_list);
      line := input_line reader
    done;
    (*
      while true; do
      let line = input_line reader in
      let line_noparen = String.sub line 1 ((String.length line) - 2) in
      let split = Str.split (Str.regexp ",") line_noparen in
      let sp1::sp2::sp3::[] = split in
      let d = match sp3 with "H" -> GameState.H
                           | "B" -> GameState.B
                           | "G" -> GameState.G
                           | "D" -> GameState.D
                           | _ -> GameState.D
      in
      wall_list := ((int_of_string sp1), (int_of_string sp2), d)::(!wall_list);
    done;
       *)
    !wall_list;
    close_in reader;
    !wall_list
  with End_of_file -> 
    close_in reader;
    !wall_list;;
  
