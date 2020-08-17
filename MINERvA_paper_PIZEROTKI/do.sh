#!/bin/bash

echo README
echo run the following first
echo go to style and do.sh
echo source setup.sh first
echo
echo

which compile_exe.sh

mkdir -p outplot/final

for aa in  mcchi2
           #draw 
do

    compile_exe.sh ${aa} -lstyle -Istyle -Lstyle
    
    ./${aa} > see${aa}.log

done


