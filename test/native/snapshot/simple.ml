(* Shoudn't break other ppxs with similar APIs *)
module StateLenses = [%lenses
  type state = {
    email: string;
    age: int;
  }
]

module Component = [%styled ("display: block")]
module Component = [%styled.section ("display: block")]

module Component = [%styled fun ~color -> {j|
  color: $color; margin-left: -10px; display: block;
|j}]
