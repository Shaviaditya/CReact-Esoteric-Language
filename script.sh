#!/bin/bash

mingw32-make.exe
./Transpiler $1
gcc output.c -o output
./output