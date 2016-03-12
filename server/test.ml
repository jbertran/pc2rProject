open GameState

let main () =
  init_state "conf/basegame.conf";
  addWall 5 5 (make_dir "H");
  print_string ((wall_list ()) ^ "\n");;

main ();;
