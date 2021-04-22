#ifndef __CONSTRAINT_COLLECTOR__
#define __CONSTRAINT_COLLECTOR__

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/IntrinsicInst.h"
#include "llvm/ADT/PostOrderIterator.h"

#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/LegacyPassManagers.h"

namespace llvm {

    typedef DenseSet<Instruction*> cSet;

    class constraintCollector : public ModulePass {

        public:

            static char ID;
            constraintCollector() : ModulePass(ID) {}

            void getAnalysisUsage(AnalysisUsage &AU) const;
            bool runOnModule(Module &M);

            // global constrains are only for addr_taken type or function type
            DenseSet<GlobalValue*> globalConstraints;

            // constraints
            DenseMap<Function*, cSet> base;
            DenseMap<Function*, cSet> simple;
            DenseMap<Function*, cSet> complex1;
            DenseMap<Function*, cSet> complex2;

            // eventhough these aren't constrains, we treat them as such for interprocedural analysis
            DenseMap<Function*, cSet> functionCalls;
            DenseMap<Function*, cSet> functionRet;

        private:

            // helpers to populate constraint instructions in specific sets
            void globalConstraintCollector(Module &M);
            void functionConstraintCollector(Function &F);

            bool hasPtrArgs(Function &F);

    };
}

#endif
