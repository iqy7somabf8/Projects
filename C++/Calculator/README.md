# Calculator

An app to calculate just about anything you need. Has semi-advanced functionality like square root and power of.

---
## Usage

**Menu:**
- `1` explains further how to format your problem.
- `2` toggled Debug. Debug shows you what calculation is picked and how the vector is handled.

**Keywords:**
- `^` is for power of calculation.
- `s` is for square root calculation
   
**sample input:**
```
213*5+23 (Also works with spaces)
```
**sample output:**
```
Result: 1088
```

## Compiling

*TODO: Add information for project compilation.*

---
## Patch Notes


**28/01/25|V1**
- Initial version. Allows for multiple operation inputs and simple operands (+, -, /, *)
---

**30/01/25|V1.1**
- Added support for power of calculation. (like squaring or cubing and higher)
- Updated Menu to make it look better.
- Added toggleable to calculate more complex stuff. (eg. power of and square root)
- Will soon add square root.
---

**03/02/25|V1.2**
- Added support for square root calculation (example: s144 | result: 12) with 's' being the keyword for it.
- Cleaned up some code to make it somewhat more optimised. There are way too many for-loops so it probably won't matter.
- Cleaned up the validateInput function in the for-loop section to stop it from making weird and unnecessary checks.
---

**28/05/25|V1.3**
- Started reworking the entire calculation pipeline to make it more optimised and easier to rework.
---

**17/02/26|V1.4**
- Completely reworked the calculation pipeline.
- Removed the 5+ different for-loops and replaced it with 1 central loop.
- Reworked evaluateInput and all calculation functions to accomodate this new pipeline design.
- Removed the complexCalculations bool setting in the menu, as this new design only calculates it if it is present.
- All mentions of complexCalculation have been archived and will mostlikely be removed later down the line.
- Added a Debug toggleable, which if enabled will output useful data to show how the program is handling our problem.

---
## Personal Note

I understand that the big time jump between 1.3 and 1.4 (almost a year, yikes) is strange, but life had just gotten to me and I was completely out of time to continue working on my personal Projects. I was also preoccupied with doing a Project for my IT class, which was to make an android app utilising an old app making framework (MIT App Inventor).
