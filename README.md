# quick-cpp-builder
A small program doing the work of a make file (or something)

Working on adding settings through a .json file

Right now, its using the g++ compiler with -std=c++17, this will become easy to change once the Json settings are implemented.

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
 - copy the **build.o** file into the root directory of your project. (Before the program is configurateable, it needs to have the source code in a folder called *Source*
 
#### step 4
- Run the build.o file from the root of your project
```bash
 ./build.o
 ```

#### step 5
- The finished build should be in the **Bin** folder.
### Warning
This program is testing for its own existence in form of "build.o" and "projectBuilder.cpp" if you rename the compiled program from "build.o" to anything else, it will most likely fail (or delete itself), unless changes are made to the projectBuilder.cpp file at line: 49 and 83 (of this build)

### Args
- As of this build it only supports the arg **no-clean** which tells the program to not remove the temporary .o files from the root of your project.
