#!/bin/bash
cd ~/workspace/llvm
LLVM=`pwd`
PATH="$LLVM/build/bin:$PATH"
cd "$LLVM/build/lib/Analysis/lab1"
make
cd "$LLVM/lib/Analysis/lab1/test"
clang testcode.c -o testcode
clang testcode.c -S -emit-llvm
echo "---- testcode output follows ----"
./testcode
echo "---- cntPrintf Output follows ----"
opt -load "$LLVM/build/lib/LLVMCntPrintf.so" -cntPrintf < testcode.ll > /dev/null
