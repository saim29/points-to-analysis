WARNING: You're attempting to print out a bitcode file.
This is inadvisable as it may cause display problems. If
you REALLY want to taste LLVM bitcode first-hand, you
can force output with the `-f' option.

Alias sets for function 'main':
Alias Set Tracker: 6 alias sets for 7 pointer values.
  AliasSet[0x5566f1928380, 1] must alias, Mod       Pointers: (i32* %retval, LocationSize::precise(4))
  AliasSet[0x5566f1928420, 2] may alias, Mod/Ref   Pointers: (i32* %b, LocationSize::precise(4)), (i32* %3, LocationSize::precise(4))
  AliasSet[0x5566f19284c0, 1] must alias, Mod/Ref   Pointers: (i32* %f, LocationSize::precise(4))
  AliasSet[0x5566f1928560, 1] must alias, Mod/Ref   Pointers: (i32** %a, LocationSize::precise(8))
  AliasSet[0x5566f1928600, 1] must alias, Mod       Pointers: (i32* %c, LocationSize::precise(4))
  AliasSet[0x5566f19286a0, 1] must alias, Mod       Pointers: (i32** %d, LocationSize::precise(8))

===-------------------------------------------------------------------------===
                      ... Pass execution timing report ...
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0008 seconds (0.0008 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0006 ( 78.9%)   0.0006 ( 78.9%)   0.0006 ( 78.8%)  Alias Set Printer
   0.0001 (  8.2%)   0.0001 (  8.2%)   0.0001 (  8.1%)  Module Verifier
   0.0001 (  7.5%)   0.0001 (  7.5%)   0.0001 (  7.6%)  Dominator Tree Construction
   0.0000 (  2.9%)   0.0000 (  2.9%)   0.0000 (  2.9%)  Basic Alias Analysis (stateless AA impl)
   0.0000 (  1.5%)   0.0000 (  1.5%)   0.0000 (  1.7%)  Function Alias Analysis Results
   0.0000 (  0.9%)   0.0000 (  0.9%)   0.0000 (  0.9%)  Assumption Cache Tracker
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Target Library Information
   0.0008 (100.0%)   0.0008 (100.0%)   0.0008 (100.0%)  Total

===-------------------------------------------------------------------------===
                                LLVM IR Parsing
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0009 seconds (0.0009 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.0006 (100.0%)   0.0003 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Parse IR
   0.0006 (100.0%)   0.0003 (100.0%)   0.0009 (100.0%)   0.0009 (100.0%)  Total

