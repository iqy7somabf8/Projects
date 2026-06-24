# Projects:

## What's the purpose of this Repository?

This Repository is made to feature most of my currently either finished or work-in-progress projects.

---
## Cloning the repo

```bash
mkdir <foldername>
git clone https://github.com/iqy7somabf8/Projects <foldername>
```

Change `foldername` to anything.

*Note: The target folder for the repo clone has to be empty, that's why I added the `mkdir` command at the start.*

---
## Compiling most projects

Compiling most of my current projects is incredibly easy:

*Note: You do require a C++ compiler. I would recommend [GCC](https://gcc.gnu.org)*

*[Instructions for downloading GCC](https://phoenixnap.com/kb/install-gcc-windows)*

```bash
g++ <filename.cpp> -o <filename>
```

Obviously changing `filename` to the name of the file you are compiling.


The only project currently not able to be compiled using the previously shown method is `Bankr`.

```bash
g++ Bankr.cpp account/account.cpp logger/logger.cpp -o Bankr
```

---
## All projects

**C++:**
* `BetterList` is my own personal idea of a TO-DO app. Obviously my first project, duh.
* `Calculator` is a decent calculator able to do some slightly advanced mathematics.
* `Bankr` is a banking app with data saving to files (.txt) and also a logger. My current most advanced project.

---
## How many languages are there?

Currently its only C++. I do have projects in other languages, however they're not really well made and lack proper code structure.
  
I am planning on making and releasing projects in other languages in the near future, but for now it will be just C++.
  
---
## What's your experience with programming?

I started programming in early 2025. 

It was a fun free-time activity / hobby with mostly badly made python projects. 

In late 2025 I started really enjoying it and I started cosidering a carreer in it. 

Now, im fully committed to a carreer in software development.
