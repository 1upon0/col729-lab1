#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include <iostream>

using namespace llvm;
using namespace std;
namespace {

struct CntPrintf : public FunctionPass{
    static char ID;
    CntPrintf() : FunctionPass(ID) {}
    bool runOnFunction(Function &F) override {
        int num_calls = 0;
        for(Function::iterator blk_it = F.begin(); blk_it != F.end(); blk_it++){
            for(BasicBlock::iterator inst_it = blk_it->begin(); inst_it != blk_it->end();
              inst_it++){
                CallInst *call_inst = dyn_cast<CallInst>(&(*inst_it));
                if(call_inst != NULL){
                    Function *func = call_inst->getCalledFunction();
                    if(func->getName().equals("printf"))
                        num_calls++;
                }
            }
        }
        errs().write_escaped(F.getName()) << ":\nprintf(): "<<num_calls<<" calls\n";
        return false;
    }
};
}
char CntPrintf::ID = 0;
static RegisterPass<CntPrintf> X("cntPrintf", "Counts printf() calls for each fn", false, false);
