open Css_spec_parser;

let spec = read_line() |> value_of_string;

let render_combinator = fun
  | Static => "Static" /* a b */
  | And => "And" /* a && b */
  | Or => "Or" /* a || b */
  | Xor => "Xor" /* a | b */

let render_multiplier = fun
  | One => "One"
  | Zero_or_more => "Zero_or_more"
  | One_or_more => "One_or_more"
  | Optional => "Optional"
  | Repeat(i, None) => Format.sprintf("Repeat(%i, None)", i)
  | Repeat(i, Some(x)) => Format.sprintf("Repeat(%i, Some(%i))", i, x)
  | Repeat_by_comma(i, None) => Format.sprintf("Repeat_by_comma(%i, None)", i)
  | Repeat_by_comma(i, Some(x)) => Format.sprintf("Repeat_by_comma(%i, Some(%i))", i, x)
  | At_least_one  => "At_least_one";

let render_terminal = fun
    | Keyword(v) => Format.sprintf("Keyword(%s)", v)
    | Data_type(v) => Format.sprintf("Data_type(%s)", v)
    | Property_type(v) => Format.sprintf("Property_type(%s)", v);

let rec render_value = fun
    | Terminal(terminal, multiplier) => Format.sprintf("Terminal(%s, %s)", render_terminal(terminal), render_multiplier(multiplier))
    | Combinator(combinator, value_list) => Format.sprintf("Combinator(%s, (%s))", render_combinator(combinator), render_value_list(value_list))
    | Group(value, multiplier) =>  Format.sprintf("Group(%s, %s)", render_value(value), render_multiplier(multiplier))
    | Function_call(s, v) => Format.sprintf("Function_call(%s, %s)", s, render_value(v))

and render_value_list = (v) =>  v |> List.map(render_value) |> String.concat(", ")

let render_spec = fun
    | Some(x) => render_value(x)
    | None => assert false;

let () = print_endline(render_spec(spec));
