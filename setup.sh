#!/bin/bash
if ! type clang++ &> /dev/null; then
  echo "clang++ was not found - Please install it, and then run this program again."
else
	clang++ -g -std=c++17 projectBuilder.cpp -o build.o -lstdc++fs

echo "Compiling ended - run ./build.o to build your project (after the build.o has been moved to the root of your project)"

fi
