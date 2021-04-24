WARNING: You're attempting to print out a bitcode file.
This is inadvisable as it may cause display problems. If
you REALLY want to taste LLVM bitcode first-hand, you
can force output with the `-f' option.

Convergence: 2
Points to sets
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
Set for:   %d = alloca i32*, align 8
--------------------------
Node Type: 1
Node Ref:   %d = alloca i32*, align 8
--------------------------
Set for:   %b = alloca i32, align 4
--------------------------
Node Type: 1
Node Ref:   %b = alloca i32, align 4
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
Set for:   %1 = load i32*, i32** %a, align 8
--------------------------
Node Type: 0
Node Ref:   %a = alloca i32*, align 8
--------------------------
Set for:   %f = alloca i32, align 4
--------------------------
Node Type: 1
Node Ref:   %f = alloca i32, align 4
--------------------------
Set for:   %c = alloca i32, align 4
--------------------------
--------------------------
Set for:   %d = alloca i32*, align 8
--------------------------
Node Type: 0
Node Ref:   %a = alloca i32*, align 8
--------------------------
Set for:   %b = alloca i32, align 4
--------------------------
--------------------------
Set for:   %a = alloca i32*, align 8
--------------------------
Node Type: 1
Node Ref:   %b = alloca i32, align 4
--------------------------
Set for:   %retval = alloca i32, align 4
--------------------------
--------------------------
Set for:   %f = alloca i32, align 4
--------------------------
===-------------------------------------------------------------------------===
                      ... Pass execution timing report ...
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0021 seconds (0.0021 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0019 ( 92.3%)   0.0000 (  0.0%)   0.0019 ( 90.2%)   0.0019 ( 90.3%)  Andersen's Analysis
   0.0001 (  4.6%)   0.0000 (100.0%)   0.0001 (  6.8%)   0.0001 (  6.7%)  Constraint Collector for Andersen's Pointer Analysis
   0.0001 (  3.1%)   0.0000 (  0.0%)   0.0001 (  3.1%)   0.0001 (  3.0%)  Module Verifier
   0.0020 (100.0%)   0.0000 (100.0%)   0.0021 (100.0%)   0.0021 (100.0%)  Total

===-------------------------------------------------------------------------===
                                LLVM IR Parsing
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0009 seconds (0.0009 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0006 (100.0%)   0.0003 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Parse IR
   0.0006 (100.0%)   0.0003 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Total

