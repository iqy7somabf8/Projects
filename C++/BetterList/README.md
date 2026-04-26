# BetterList

An app to easily track your TO-DOs. Very simple to use.

---
## Usage

**Menu:**
- 1 Create Task.
- 2 Edit Task.
- 3 Delete Task.
- 4 Display Tasks.
- 5 Complete Task.
- 6 Exit.

**Explanation:**
- `1` Prompts you to enter in a name, description and due date for your Task.
- `2` Lists out all tasks and allows you to pick one to edit.
- `3` Lists out all tasks and allows you to pick one to remove forever (irreversible).
- `4` Lists out all saved tasks and wether or not they're completed.
- `5` Lists out all tasks and allows you to pick one to mark as completed.
- `6` Closes The program.

**Sample input:**

```
1
Wash the dishes
Wash the dishes by 5 P.M or else mom will be mad!
17.02.26
```
**Sample output:**
```
Task added!
```

---
## Compiling

This project is only one file, so the compilation is insanely easy:

```bash
g++ BetterList.cpp -o BetterList
```

