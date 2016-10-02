#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include <iostream>

using namespace llvm;
using namespace std;
namespace {

struct LivenessHist : public BasicBlockPass{
    static char ID;
    LivenessHist() : FunctionPass(ID) {}
    bool runOnBasicBlock(BasicBlock &blk) override {
        for(BasicBlock::iterator inst_it = blk_it->begin(); inst_it != blk_it->end();
          inst_it++){
            CallInst *call_inst = dyn_cast<CallInst>(&(*inst_it));
            if(call_inst != NULL){
                Function *func = call_inst->getCalledFunction();
                if(func->getName().equals("printf"))
                    num_calls++;
            }
        }
        return false;
    }
};
}
char LivenessHist::ID = 0;
static RegisterPass<LivenessHist> X("livenessHist", "Displays liveness histogram for program", false, false);
