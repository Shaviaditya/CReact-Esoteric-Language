#!/bin/bash

make
./Transpiler $1
gcc output.c -o output
./output