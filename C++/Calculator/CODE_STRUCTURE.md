# Code Structure

A little insight into how the code is structured and what every file does.

Many things aren't covered very well right now, as I made this file in like 1 hour with just what I remember.

Absolutely 0 `AI` was used to create any of the code seen here. At one point a couple tidbits were, but that was around a year ago and I've long since then refactored that broken code.

I personally absolutely despise using `AI` for creating code and believe it teaches you nothing. I'd rather have this ugly codebase made by my hands and brain than a broken and ugly codebase made by an AI.

---

## Application.cpp

This is the `frontend` of the calculator. Handles user input and sends it off to the backend. It then awaits a response and prints it to the console."

---

## Calculator.cpp

This is the actual `backend` of the calculator. It handles input validation (very, and I mean very, badly made. I will soon actually make it better) and tokenisation. It also handles parentheses.

- ## validateInput():

Checks for a couple edge-cases I ran into during development. Would love a suggestion for more.
It also stores how many parantheses it sees inside a hashmap called `const std::unordered_map<char, int> parantheseCounts`. This is used in `evaluateParantheses()`

It also has an overloaded version that takes in a vector. This version just checks if you're trying to calculate a negative square root.

- ##  tokenise():

Tokenise reads the input string, after it has passed validation, and tokenises it into a vector.

- ## evaluateInput():

This is the main handler of the problem. It calls every other function like `tokenise()` and `validateInput()`

- ##  evaluateParantheses():

An incredibly hacky design to handle parantheses. You might think I was drunk whilst making it. I sadly was fully conscious whilst making it.

It first starts reading through the vector and finds the deepest paranthese.
After finding it, it creates a second vector that consists of the body of the parantheses and sends that off into `loopProblem()`.
It then calls `cleanupParanthese()`, which, like the name suggests, cleans up the parantheses and the problem.

After all that it resets the index `i` to `-1` (this restarts the loop)
It also resets the `seenParantheses` to `0` and lowers the paranthese counts in the hashmap.

- ## loopProblem():

Loops through the problem searching for valid operators and calling their respective calculation functions. 

It first checks for the single number operators (e.g: square root, sine, cosine) and power-of.
Next, it checks for multiplication and division.
Lastly, it sends it off to `addAndSubtract()`.

## Calculation functions:

Very small and easy to understand calculation functions like:

- `multiply()`
- `divide()`
- `calculatePower()`
- `etc`

These won't be documented for now, as they are very easy to understand.

---

## Utils.cpp

Utils is a class that holds some tools to help me debug the code and clean the problem vector.

`debugOutput()` and `debugVectorOutput()` also have support for indentation. For every level of indentation, one "\t" string gets printed before the actual output.

- ## debugOutput() and its overloads:

Just takes in a message and prints it if debug is on.

Overloads take in an extra input (e.g: an index or result) and print it right after the normal msg.

- ## debugVectorOutput():

Takes in a vector and prints out its elements if debug is on.

Has a version that takes in a `VECTOR_OUTPUT_STATES` state. The states can be either `PRE_CLEANUP` or `POST_CLEANUP`.
if you input `PRE_CLEANUP`, then it prints `"Pre cleanup:\n"` before the vector.
This overload is only used in the `cleanup()` and `cleanupParantheses()` functions.

- ## changeIndentation():

Takes in a `DEBUG_INDENTATION` INDENT, which can be either `INCREASE_INDENT` or `DECREASE_INDENT`.
It literally just decreases or increases the class variable `indentation` by 1

- ## cleanup():

Cleans up the inputted array.

It first places the result at index `index - 1` if it isn't a square root calculation or `index` if it is (index is the index of the operator). Then it goes ahead and deletes the unnecessary extra bits.


- ## cleanupParantheses():

Very simmilar to the `cleanup()` function. It takes in some extra variables though.


- ## clearCin():

An absolute relic from the first ever version of this project. I have no clue if it even does anything useful, but when I came back to this project it was already used a couple so I just left it there. It doesn't seem to break anything so why not 🤷
