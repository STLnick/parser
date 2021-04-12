# Parser

## Compilers - P2

**Version Control**:
GitHub repo: https://github.com/STLnick/parser

Cloned from [scanner](https://github.com/STLnick/parser) to get all of that code to begin.

---

**To run the program**:
- Run `make` in the root of the project to build `frontEnd`
    - The executable `frontEnd` is built and placed in `/bin`.
- Execute `cd ./bin`
- Run `./frontEnd` with a file containing the `.fs` extension (example below)

**Run command structure**:

> `[file]` _must have the extension of_ `.fs` or no extension at all.
> - for example `test1.fs`, `text.fs`, `whatever.fs`, `filename`

`./frontEnd [file]` or `./frontEnd [file].fs`
    - **NOTE**: The files to be read from _MUST BE IN THE_ `/bin` directory with the executable

`./frontEnd -h`

- help


### Simple example of a valid, parsable program
`p2g1.fs` of provided test files

```
$$ p2g1 $$
main
begin
getter x ;
end
```

### Complex example of a valid, parsable program
`p2g6.fs` of provided test files

```
$$ p2g6 $$
data a := 5 ;
data b := 6 ;
data c := 7 ;
main
begin
    outter ( 2 * 3 / 5 + 7 - * 11 + ( 13 * * 17 ) ) ;
end
```


---

**What Works**:
- Parses file correctly
- Displays proper error if there is one in parsing
- Creates a tree from parsing
- Displays tree nodes with associated terminals and nonterminals

**What Doesn't Work**:
- Nothing that I'm aware of!

---
### Commit Log
