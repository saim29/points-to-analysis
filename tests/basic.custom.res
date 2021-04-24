WARNING: You're attempting to print out a bitcode file.
This is inadvisable as it may cause display problems. If
you REALLY want to taste LLVM bitcode first-hand, you
can force output with the `-f' option.

Convergence: 2
Points to sets


--------------------------
Set for: 0  %3 = load i32*, i32** %a, align 8
--------------------------
Node Ref: 1  %b = alloca i32, align 4


--------------------------
Set for: 0  %c = alloca i32, align 4
--------------------------
Node Ref: 1  %c = alloca i32, align 4


--------------------------
Set for: 0  %d = alloca i32*, align 8
--------------------------
Node Ref: 1  %d = alloca i32*, align 8


--------------------------
Set for: 0  %b = alloca i32, align 4
--------------------------
Node Ref: 1  %b = alloca i32, align 4


--------------------------
Set for: 0  %a = alloca i32*, align 8
--------------------------
Node Ref: 1  %a = alloca i32*, align 8


--------------------------
Set for: 0  %retval = alloca i32, align 4
--------------------------
Node Ref: 1  %retval = alloca i32, align 4


--------------------------
Set for: 0  %1 = load i32*, i32** %a, align 8
--------------------------
Node Ref: 1  %b = alloca i32, align 4


--------------------------
Set for: 0  %f = alloca i32, align 4
--------------------------
Node Ref: 1  %f = alloca i32, align 4


--------------------------
Set for: 1  %c = alloca i32, align 4
--------------------------


--------------------------
Set for: 1  %d = alloca i32*, align 8
--------------------------
Node Ref: 1  %b = alloca i32, align 4


--------------------------
Set for: 1  %b = alloca i32, align 4
--------------------------


--------------------------
Set for: 1  %a = alloca i32*, align 8
--------------------------
Node Ref: 1  %b = alloca i32, align 4


--------------------------
Set for: 1  %retval = alloca i32, align 4
--------------------------


--------------------------
Set for: 1  %f = alloca i32, align 4
--------------------------
===-------------------------------------------------------------------------===
                      ... Pass execution timing report ...
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0024 seconds (0.0024 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0017 ( 79.8%)   0.0002 ( 92.7%)   0.0019 ( 81.2%)   0.0019 ( 81.2%)  Andersen's Analysis
   0.0003 ( 14.0%)   0.0000 (  0.0%)   0.0003 ( 12.5%)   0.0003 ( 12.5%)  Module Verifier
   0.0001 (  6.2%)   0.0000 (  7.3%)   0.0002 (  6.4%)   0.0002 (  6.4%)  Constraint Collector for Andersen's Pointer Analysis
   0.0021 (100.0%)   0.0003 (100.0%)   0.0024 (100.0%)   0.0024 (100.0%)  Total

===-------------------------------------------------------------------------===
                                LLVM IR Parsing
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0009 seconds (0.0009 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0008 (100.0%)   0.0001 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Parse IR
   0.0008 (100.0%)   0.0001 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Total

