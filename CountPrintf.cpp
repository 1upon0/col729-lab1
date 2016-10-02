#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include <iostream>

using namespace llvm;
using namespace std;
namespace {

struct CntPrintf : public FunctionPass{
    static char ID;
    CntPrintf() : FunctionPass(ID) {}
    bool runOnFunction(Function &F) override {
        cerr << "i iz not error!"<<endl;
        errs() << "Hello: ";
        errs().write_escaped(F.getName()) << '\n';
        return false;
    }
};
}
char CntPrintf::ID = 0;
static RegisterPass<CntPrintf> X("cntPrintf", "Counts printf() calls for each fn", false, false);
