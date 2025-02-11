(* let () = Seq.of_dispenser (fun () -> try Some (read_line ()) with End_of_file -> None)
  |> Seq.map int_of_string
  |> List.of_seq
  |> List.sort compare
  |> List.iter (Printf.printf "%d\n") *)

let rec merge l x y = match (x,y) with 
  | ([],_) -> y
  | (_,[]) -> x
  | (h1::t1, h2::t2) -> 
  if l h1 h2 
      then h1::(merge l t1 y)
      else h2::(merge l x t2);;

let rec split x y z = match x with
   | [] -> (List.rev y, List.rev z)
   | x::resto -> split resto z (x::y);;

let rec mergesort l x = match x with
  | ([] | _::[]) -> x
  | _ -> let (pri,seg) = split x [] [] 
  in merge l (mergesort l pri) (mergesort l seg);;

let () = Seq.of_dispenser (fun () -> try Some (read_line ()) with End_of_file -> None)
|> Seq.map int_of_string
|> List.of_seq
|> mergesort (fun x y -> compare x y < 0)
|> List.iter (Printf.printf "%d\n")

(* mergesort (>) [2;6;1;8];;
- : int list = [8; 6; 2; 1] *)