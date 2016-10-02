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
    LivenessHist() : BasicBlockPass(ID) {}
    bool runOnBasicBlock(BasicBlock &blk) override {
        for(BasicBlock::iterator inst_it = blk.begin(); inst_it != blk.end();
          inst_it++){
            cerr<<"Inst:"<<inst_it->getName().str()<<endl;
            User::op_iterator op;
            //CallInst *call_inst = dyn_cast<CallInst>(&(*inst_it));
            for(op = inst_it->op_begin(); op != inst_it->op_end(); op++){
                cerr<<"  op:"<<op->getName().str()<<endl;
            }
        }
        return false;
    }
};
}
char LivenessHist::ID = 0;
static RegisterPass<LivenessHist> X("livenessHist", "Displays liveness histogram for program", false, false);
