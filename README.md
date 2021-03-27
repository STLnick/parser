# Parser

## Compilers - P2

**Version Control**:
GitHub repo: https://github.com/STLnick/parser

Cloned from [scanner](https://github.com/STLnick/parser) to get all of that code to begin.

---

**To run the program**:
First run 'make' in the root of the project to build 'frontEnd'. The executable `frontEnd` is built and placed in `/bin`.

At the same location in the project folders you can just run `./bin/frontEnd`
Or you can execute `cd ./bin` and then run `./frontEnd`

**Run command structure**:

> In each case `[file]` will be read in 'word by word' (whitespaces separate what's read in).

> `[file]` _must have the extension of_ `.fs`.
> - for example `test1.fs`, `text.fs`, `whatever.fs`

`./frontEnd`

- read from the keyboard until simulated EOF (Command to type to simulate EOF -> *nix: ctrl+d, windows: ctrl+z)

`./frontEnd < [file]`

- redirect from `[file]` until EOF

`./frontEnd [file]` or `./frontEnd [file].fs`

- read from `[file].fs`
    - **NOTE**: The files to be read from _MUST BE IN THE_ `/bin` directory with the executable

`./frontEnd -h`

- help


---

**What Works**:

**What Doesn't Work**:

---
### Commit Log
