#!/bin/bash
cd ~/workspace
WORKSPACE=`pwd`
PATH="$WORKSPACE/build/bin:$PATH"
cd "$WORKSPACE/build/lib/Analysis/lab1"
make
cd "$WORKSPACE/llvm/lib/Analysis/lab1/test"
clang -O0 testcode.c -o testcode
clang -O0 testcode.c -S -emit-llvm
echo "---- testcode output follows ----"
./testcode
echo "---- cntPrintf Output follows ----"
opt -load "$WORKSPACE/build/lib/LLVMLab1.so" -cntPrintf < testcode.ll > /dev/null
echo "---- livenessHist Output follows ----"
opt -mem2reg < testcode.ll > testcode.bc
llvm-dis < testcode.bc > testcode.ll
opt -load "$WORKSPACE/build/lib/LLVMLab1.so" -livenessHist < testcode.ll > /dev/null

