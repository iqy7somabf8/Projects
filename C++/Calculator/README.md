# Calculator

An app to calculate just about anything you need. Has semi-advanced functionality like square root and power of. Now with paranthese evaluation!

---
## Usage

**Menu:**
- `1` explains further how to format your problem.
- `2` toggled Debug. Debug shows you what calculation is picked and how the vector is handled.

**Keywords:**
- `^` is for power of calculation.
- `s` is for square root calculation
- `()` is used to wrap problems that should be evaluated first.
- `sin` is for sine calculation (duh)
- `cos` is for cosine calculation (duh)

- `tip`: use `()` when dealing with `s, sin, and cos`.
- `tip`: the program will automatically add a `*` operator between `numbers` and `parantheses`.

**sample input:**
```
213*5+23 (Also works with spaces)
```
**sample output:**
```
Result: 1088
```

## Compiling

```bash
g++ Application.cpp Calculator.cpp Utils.cpp -o app
```

---
## Patch Notes

| Version | Changes |
|------|---------|
| `V1 > 28/01/25` | - Initial version. Allows for multiple operation inputs and simple operands `+, -, /, *` |
| `V1.1 > 30/01/25` | - Added support for power of calculation (like squaring or cubing and higher).<br>- Updated Menu to make it look better.<br>- Added toggleable to calculate more complex stuff (eg. power of and square root).<br>- Will soon add square root. |
| `V1.2 > 03/02/25` | - Added support for square root calculation `example: s144 > result: 12` with 's' being the keyword for it.<br>- Cleaned up some code to make it somewhat more optimised. There are way too many for-loops so it probably won't matter.<br>- Cleaned up the validateInput function in the for-loop section to stop it from making weird and unnecessary checks. |
| `V1.3 > 28/05/25` | - Started reworking the entire calculation pipeline to make it more optimised and easier to rework. |
| `V1.4 > 17/02/26` | - Completely reworked the calculation pipeline.<br>- Removed the 5+ different for-loops and replaced it with 1 central loop.<br>- Reworked `evaluateInput` and all calculation functions to accomodate this new pipeline design.<br>- Removed the `complexCalculations` bool setting in the menu, as this new design only calculates it if it is present.<br>- All mentions of `complexCalculation` have been archived and will mostlikely be removed later down the line.<br>- Added a Debug toggleable, which if enabled will output useful data to show how the program is handling our problem. |
| `V1.5 > 28/06/26`| - Restructured the whole codebase into multiple files: `Application, Calculator, Utils`.<br>- `Application`: The main "front-end" of the app. Gets the user prompt and sends it off to the "back-end".<br>- `Calculator`: The "back-end" of the app. Handles every problem.<br>- `Utils`: The debug and cleanup tool. Just some nice things to help in the back-end.<br>- Added support for handling parantheses in problems. `Example: 12(3+4)` the 3+4 inside the parantheses will be evaluated first.<br>- It will then also add a `*` (multiplication) operator infront of the opening pranthese.<br>- Added a new square root algorithm. First I tried one from my leetcode escapades, but it only returned integers. This new one was from a random website that like somewhat taught me how it worked.<br>- Reworked the old debug functions to finally use overloading. No idea why I didn't do this in the first place.<br>- `tokenise()` now also finally doesnt skip the last index of the input string :sob:. My dumb ahh actually had that oversight sitting there for so long.<br>- <em>I will at some point do proper testing of the parantheses and overall app. I will first wait until school starts up again and I actually require a calculator.</em> |

---

## Personal Note

I understand that the big time jump between 1.3 and 1.4 (almost a year, yikes) is strange, but life had just gotten to me and I was completely out of time to continue working on my personal Projects. I was also preoccupied with doing a Project for my IT class, which was to make an android app utilising an old app making framework (MIT App Inventor).
