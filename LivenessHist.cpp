#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"

#include <iostream>
#include <set>
using namespace llvm;
using namespace std;

namespace {
struct LivenessHist : public BasicBlockPass{
    static char ID;
    LivenessHist() : BasicBlockPass(ID) {}

    set<Instruction*>* GEN(BasicBlock* bb){
      set<Instruction*> *gen = new set<Instruction*>();
      set<Instruction*> *defined = new set<Instruction*>();

      for(BasicBlock::iterator it_blk = bb->begin(); it_blk != bb->end(); it_blk++){
        Instruction *inst = &*it_blk;
        for(User::op_iterator it_op = inst->op_begin(); it_op != inst->op_end(); it_op++){
          Value *val = it_op->get();
          if(isa<Instruction>(val) || isa<Argument>(val)){
            if(defined->find((Instruction*)val) == defined->end()){
              gen->insert((Instruction*)val);
            }
          }
        }
        defined->insert(inst);
      }
      delete defined;
      return gen;
    }

    set<Instruction*>* KILL(BasicBlock* bb){
      set<Instruction*> *kill = new set<Instruction*>();
      for(BasicBlock::iterator it_blk = bb->begin(); it_blk != bb->end(); it_blk++){
        Instruction *inst = &*it_blk;
        kill->insert(inst);
      }
      return kill;
    }

    bool runOnBasicBlock(BasicBlock &blk) override{
        set<Instruction*> *gen = GEN(&blk);
        for(set<Instruction*>::iterator it = gen->begin(); it!=gen->end(); it++){
          cerr<<(*it)->getName().str()<<endl;
        }
        set<Instruction*> *kill = KILL(&blk);
        for(set<Instruction*>::iterator it = kill->begin(); it!=kill->end(); it++){
          cerr<<(*it)->getName().str()<<endl;
        }

        // for(BasicBlock::iterator inst_it = blk.begin(); inst_it != blk.end(); inst_it++){
        //     cerr<<"Inst:"<<inst_it->getOpcodeName()<<endl;
        //     User::op_iterator op;
        //     //CallInst *call_inst = dyn_cast<CallInst>(&(*inst_it));
        //     for(op = inst_it->op_begin(); op != inst_it->op_end(); op++)
        //     {
        //         Value *val = *op;
        //         if(isa<Instruction>(val))
        //             cerr<<" def:";
        //         if(isa<Argument>(val))
        //             cerr<<" arg:";
        //         cerr<<(*op)->getName().str()<<endl;
        //     }
        // }
        return false;
    }
};
}
char LivenessHist::ID = 0;
static RegisterPass<LivenessHist> X("livenessHist", "Displays liveness histogram for program", false, false);
