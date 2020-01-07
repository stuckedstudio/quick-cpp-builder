#!/bin/bash
if ! type g++ &> /dev/null; then
  echo "g++ was not found - Please install it, and run this program again after."
else
	g++ -std=c++17 projectBuilder.cpp -o build.o

echo "Compiling ended - run ./build.o to build your project (after the build.o has been moved to the root of your project)"

fi
