WARNING: You're attempting to print out a bitcode file.
This is inadvisable as it may cause display problems. If
you REALLY want to taste LLVM bitcode first-hand, you
can force output with the `-f' option.

Convergence: 2
Points to sets
--------------------------
Set for:   %f = alloca i32, align 4
--------------------------
Node Type: 1
Node Ref:   %f = alloca i32, align 4
--------------------------
Set for:   %a = alloca i32*, align 8
--------------------------
Node Type: 1
Node Ref:   %a = alloca i32*, align 8
--------------------------
Set for:   %retval = alloca i32, align 4
--------------------------
Node Type: 1
Node Ref:   %retval = alloca i32, align 4
--------------------------
Set for:   %b = alloca i32, align 4
--------------------------
Node Type: 1
Node Ref:   %b = alloca i32, align 4
--------------------------
Set for:   %1 = load i32*, i32** %a, align 8
--------------------------
Node Type: 0
Node Ref:   %a = alloca i32*, align 8
--------------------------
Set for:   %d = alloca i32*, align 8
--------------------------
Node Type: 1
Node Ref:   %d = alloca i32*, align 8
--------------------------
Set for:   %3 = load i32*, i32** %a, align 8
--------------------------
Node Type: 0
Node Ref:   %a = alloca i32*, align 8
--------------------------
Set for:   %c = alloca i32, align 4
--------------------------
Node Type: 1
Node Ref:   %c = alloca i32, align 4
--------------------------
Set for:   %f = alloca i32, align 4
--------------------------
--------------------------
Set for:   %a = alloca i32*, align 8
--------------------------
Node Type: 0
Node Ref:   %b = alloca i32, align 4
--------------------------
Set for:   %retval = alloca i32, align 4
--------------------------
--------------------------
Set for:   %b = alloca i32, align 4
--------------------------
--------------------------
Set for:   %d = alloca i32*, align 8
--------------------------
Node Type: 0
Node Ref:   %1 = load i32*, i32** %a, align 8
--------------------------
Set for:   %c = alloca i32, align 4
--------------------------
===-------------------------------------------------------------------------===
                      ... Pass execution timing report ...
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0029 seconds (0.0090 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0024 ( 82.2%)   0.0024 ( 82.2%)   0.0064 ( 71.0%)  Andersen's Analysis
   0.0004 ( 14.8%)   0.0004 ( 14.8%)   0.0025 ( 28.0%)  Constraint Collector for Andersen's Pointer Analysis
   0.0001 (  3.1%)   0.0001 (  3.1%)   0.0001 (  1.0%)  Module Verifier
   0.0029 (100.0%)   0.0029 (100.0%)   0.0090 (100.0%)  Total

===-------------------------------------------------------------------------===
                                LLVM IR Parsing
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0009 seconds (0.0009 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0009 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Parse IR
   0.0009 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Total

