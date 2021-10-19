#!/bin/bash

mingw32-make.exe
./transpiler1 $1
gcc output.c -o output
./output