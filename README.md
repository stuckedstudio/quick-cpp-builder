# quick-cpp-builder
[![Build Status](https://travis-ci.com/stuckedstudio/quick-cpp-builder.svg?branch=master)](https://travis-ci.com/stuckedstudio/quick-cpp-builder)

A small program doing the work of a makefile (or something)

Working on adding settings through a .json file

Right now, it's using either the g++ or clang++ compiler with -std=c++17, this will become easy to change once the Json settings are implemented. Clang will be selected with the --clang argument or by having the enviroment variable CXX set to clang++-8

This program cannot yet be used globally on the system.
### Setup

#### step 1:
 - Allow the setup.sh file to be executed. This can be done in the terminal with:
 ```bash
 chmod +x ./setup.sh
 ```
#### step 2
- Run the setup.sh
```bash
 ./setup.sh
 ```
#### step 3
 - copy the **build.o** file into the root directory of your project. (Before the program becomes configurateable, it needs to have the source code in a folder called *Source*)
 
#### step 4
- Run the build.o file from the root of your project
```bash
 ./build.o
 ```

#### step 5
- The finished build should be in the **Bin** folder.
### Warning
This program is testing for its own existence in form of "build.o" and "projectBuilder.cpp" if you rename the compiled program from "build.o" to anything else, it will most likely fail (or delete itself), unless changes are made to the projectBuilder.cpp file!!!This issue will be adressed with the Json update!!!

### Args
- You can specify extra g++ arguments with:
```bash
./build.o [g++ arg1] [g++ arg2] [g++ arg N]...
```
- Some programs require using arguments at the end of the g++ command, for this you can use:
```bash
./build.o [g++ arg1] [g++ arg2] [g++ arg N]... --end-arg=[g++ end arg1] --end-arg=[g++ end argN]...
```
#### ~~The **no-clean** arg does not work, for reasons that I'm too lazy to work out atm.~~ This has been fixed :)


##### The point of this program, was originally to compile a small other project located at [Here](https://github.com/stuckedstudio/Isthatit)
