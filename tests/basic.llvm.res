WARNING: You're attempting to print out a bitcode file.
This is inadvisable as it may cause display problems. If
you REALLY want to taste LLVM bitcode first-hand, you
can force output with the `-f' option.

Alias sets for function 'main':
Alias Set Tracker: 6 alias sets for 7 pointer values.
  AliasSet[0x55c0dd3bb380, 1] must alias, Mod       Pointers: (i32* %retval, LocationSize::precise(4))
  AliasSet[0x55c0dd3bb420, 2] may alias, Mod/Ref   Pointers: (i32* %b, LocationSize::precise(4)), (i32* %3, LocationSize::precise(4))
  AliasSet[0x55c0dd3bb4c0, 1] must alias, Mod/Ref   Pointers: (i32* %f, LocationSize::precise(4))
  AliasSet[0x55c0dd3bb560, 1] must alias, Mod/Ref   Pointers: (i32** %a, LocationSize::precise(8))
  AliasSet[0x55c0dd3bb600, 1] must alias, Mod       Pointers: (i32* %c, LocationSize::precise(4))
  AliasSet[0x55c0dd3bb6a0, 1] must alias, Mod       Pointers: (i32** %d, LocationSize::precise(8))

===-------------------------------------------------------------------------===
                      ... Pass execution timing report ...
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0013 seconds (0.0075 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0005 ( 88.0%)   0.0007 ( 87.7%)   0.0012 ( 87.8%)   0.0073 ( 97.8%)  Alias Set Printer
   0.0000 (  6.9%)   0.0001 (  6.7%)   0.0001 (  6.8%)   0.0001 (  1.2%)  Module Verifier
   0.0000 (  1.7%)   0.0000 (  1.9%)   0.0000 (  1.8%)   0.0000 (  0.3%)  Basic Alias Analysis (stateless AA impl)
   0.0000 (  1.5%)   0.0000 (  1.6%)   0.0000 (  1.6%)   0.0000 (  0.3%)  Dominator Tree Construction
   0.0000 (  1.3%)   0.0000 (  1.4%)   0.0000 (  1.3%)   0.0000 (  0.3%)  Function Alias Analysis Results
   0.0000 (  0.6%)   0.0000 (  0.6%)   0.0000 (  0.6%)   0.0000 (  0.1%)  Assumption Cache Tracker
   0.0000 (  0.0%)   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.0%)  Target Library Information
   0.0005 (100.0%)   0.0008 (100.0%)   0.0013 (100.0%)   0.0075 (100.0%)  Total

===-------------------------------------------------------------------------===
                                LLVM IR Parsing
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0020 seconds (0.0077 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0020 (100.0%)   0.0020 (100.0%)   0.0077 (100.0%)  Parse IR
   0.0020 (100.0%)   0.0020 (100.0%)   0.0077 (100.0%)  Total

