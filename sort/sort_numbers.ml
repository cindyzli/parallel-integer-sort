(*

GIVEN CODE
let () = Seq.of_dispenser (fun () -> try Some (read_line ()) with End_of_file -> None)
  |> Seq.map int_of_string
  |> List.of_seq
  |> List.sort compare
  |> List.iter (Printf.printf "%d\n") *)

  
  (* SERIAL CODE *)
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
 




(* 
PARALLEL ATTEMPT
open Domainslib

let rec parallel_mergesort pool arr =
  let len = Array.length arr in
  if len <= 1 then arr
  else
    let mid = len / 2 in
    let left = Array.sub arr 0 mid in
    let right = Array.sub arr mid (len - mid) in
    let lsort = Task.async pool (fun () -> parallel_mergesort pool left) in
    let rsort = parallel_mergesort pool right in
    let left_sorted = Task.await pool lsort in
    merge left_sorted rsort

and merge a b =
  let rec merge_aux i j acc =
    match (i, j) with
    | [], ys -> List.rev_append acc ys
    | xs, [] -> List.rev_append acc xs
    | x::xs', y::ys' ->
        if x <= y then merge_aux xs' j (x::acc)
        else merge_aux i ys' (y::acc)
  in
  Array.of_list (merge_aux (Array.to_list a) (Array.to_list b) [])

let () =
  let pool = Task.setup_pool ~num_domains:4 () in
  let input = [|5; 2; 9; 1; 3; 8; 7; 6; 4|] in
  let sorted = parallel_mergesort pool input in
  Array.iter (Printf.printf "%d ") sorted;
  print_newline ();
  Task.teardown_pool pool
(* mergesort (>) [2;6;1;8];;
- : int list = [8; 6; 2; 1] *) *)