# ECE 5984 Final Project -  Pointer analysis

An implementation of andersen's pointer analysis in LLVM 11. 

## Team Members - Saim Ahmad, Tanmaya Mishra

## Directory Layout
<pre>
.
├── bld
│   └── Makefile
├── include
│   ├── andersen.h
│   ├── constraintCollector.h
│   └── constraintGraph.h
├── Makefile
├── README.md
├── src
│   ├── andersen.cpp
│   ├── constraintCollector.cpp
│   └── constraintGraph.cpp
└── tests
    ├── array.c
    ├── basic.c
    ├── funccall.c
    ├── funcptr.c
    ├── global.c
    ├── local.c
    └── Makefile

4 directories, 16 files
</pre>

## Directory definitions

- `bld` - Build directory. Running `make` in this directory builds the andersen analysis shared object file.
- `src` - Source code for the constraint collector that reads the `.bc` file for the constraints required for the analysis, the graph generation code, and the analysis code. 
- `tests` - Some code to test different aspects of our implementation. Tests range from basic pointers to arrays and even function pointers. Running `make` (please see below for exact syntax) here builds the specific test code. Please add custom tests to this directory. 

## To build and run:

- `cd` to `bld` and run `make`
    - Generates `andersen.so`
- `cd` to `tests`
- Example test file: `basic.c`
    - Possible `make` commands
        - `make basic.ll` - Generates the human-readable `.ll` file 
        - `make basic.llvm.res` - Performs LLVM's builtin  `-basic-aa` pass on the `basic.c` and stores output to `basic.llvm.res`
        - `make basic.custom.res` - Performs our custom andersen's pass (intra-procedural only) and stores output to `basic.custom.res`
        - `make basic.custom.inter.res` - Performs our **complete** custom andersen's pass (with inter-procedural support) and stores output to `basic.custom.inter.res`



## Example output 

- Build command - `make basic.custom.res`
- Contents of `basic.custom.res`

<pre>
WARNING: You're attempting to print out a bitcode file.
This is inadvisable as it may cause display problems. If
you REALLY want to taste LLVM bitcode first-hand, you
can force output with the `-f' option.


Initializing Graph ... Initialized!!!
Solving Graph ... 
Convergence: 2
 Solved!!!


Points to sets:

--------------------------
Set for: 0 main
--------------------------
Node Ref: 1 main


--------------------------
Set for: 0   %retval = alloca i32, align 4
--------------------------
Node Ref: 1   %retval = alloca i32, align 4


--------------------------
Set for: 0   %b = alloca i32, align 4
--------------------------
Node Ref: 1   %b = alloca i32, align 4


--------------------------
Set for: 1   %d = alloca i32*, align 8
--------------------------
Node Ref: 1   %a = alloca i32*, align 8


--------------------------
Set for: 0   %f = alloca i32, align 4
--------------------------
Node Ref: 1   %f = alloca i32, align 4


--------------------------
Set for: 0   %d = alloca i32*, align 8
--------------------------
Node Ref: 1   %d = alloca i32*, align 8


--------------------------
Set for: 0   %c = alloca i32, align 4
--------------------------
Node Ref: 1   %c = alloca i32, align 4


--------------------------
Set for: 0   %1 = load i32*, i32** %a, align 8
--------------------------
Node Ref: 1   %a = alloca i32*, align 8


--------------------------
Set for: 0   %3 = load i32*, i32** %a, align 8
--------------------------
Node Ref: 1   %a = alloca i32*, align 8


--------------------------
Set for: 0   %a = alloca i32*, align 8
--------------------------
Node Ref: 1   %a = alloca i32*, align 8


--------------------------
Set for: 1   %a = alloca i32*, align 8
--------------------------
Node Ref: 1   %b = alloca i32, align 4
===-------------------------------------------------------------------------===
                      ... Pass execution timing report ...
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0024 seconds (0.0031 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0019 ( 88.6%)   0.0002 ( 89.0%)   0.0021 ( 88.7%)   0.0028 ( 91.3%)  Andersen's Analysis
   0.0002 (  8.6%)   0.0000 (  0.0%)   0.0002 (  7.7%)   0.0002 (  5.9%)  Constraint Collector for Andersen's Pointer Analysis
   0.0001 (  2.7%)   0.0000 ( 11.0%)   0.0001 (  3.6%)   0.0001 (  2.8%)  Module Verifier
   0.0021 (100.0%)   0.0003 (100.0%)   0.0024 (100.0%)   0.0031 (100.0%)  Total

===-------------------------------------------------------------------------===
                                LLVM IR Parsing
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0009 seconds (0.0009 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0005 (100.0%)   0.0004 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Parse IR
   0.0005 (100.0%)   0.0004 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Total

</pre>