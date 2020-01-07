//Created because I didn't want to learn to make make files... Sorry
#include <iostream>
#include <unistd.h>
#include <filesystem>
//Defining our search area for cpp files
std::string root;
std::string source;
namespace fs = std::filesystem;
int main(int argc, char** argv)
{
    int clean = 1;
    for(int i = 0; i <= argc;i++)
    {
        if(argv[i] == "no-clean")
        {
            clean = 0;
        }
    }

    //Getting the current directory and our Source directory

    char strDir[129] = {0};
    puts(getcwd(strDir, 128));
    puts(strDir);
    root = strDir;
    std::cout << root << std::endl;
    source = root + "/Source";
    std::string bin;
    bin = root + "/Bin";
    bool binExist;
    //Compiling all cpp files...
    for (const auto & entry : fs::directory_iterator(source))
    {
        std::string command = "g++ -std=c++17 -c " + entry.path().generic_string();
        system(command.c_str());
    }
    //Preparing for the final compile
    std::string compileCommand = "g++ -std=c++17 -o ";
    compileCommand += bin;
    compileCommand += "/exec.o ";
    for (const auto & entry : fs::directory_iterator(root))
    {
        //Check if the Bin folder exists.
        if(entry.path().generic_string().find("/Bin") != std::string::npos)
        {
            binExist = true;
        }
        //Making sure that we are not trying to implement our project builder into the final release
        if(entry.path().generic_string().find("build.o") == std::string::npos && entry.path().generic_string().find("projectBuilder") == std::string::npos)
        {
            //Making sure that we are not adding other junk files in the directory into the compiling process
            if(entry.path().generic_string().find(".o") != std::string::npos)
            {
                //Removing the rest of the path, that we don't need.
                int tmpIndex = entry.path().generic_string().find_last_of('/');
                tmpIndex++;
                std::string tmp = entry.path().generic_string().substr(tmpIndex,entry.path().generic_string().size()-tmpIndex);
                //Verbose feature to see what we picked up, in case it does something wrong, it will be easier to find out what happened.
                std::cout << "Found File: " << tmp << std::endl;
                tmp += " ";
                //Finalizing the build command
                compileCommand += tmp;
            }
        }
    }
    //Creates bin if not exist
    if(!binExist)
    {
        fs::create_directory(bin);
    }
    //Showing the build command to make sure that we got the command we needed
    std::cout << "Full compile command: " << compileCommand << std::endl;
    //Running the build.
    system(compileCommand.c_str());
    //Checking if we asked the program to cleanup (Default enabled: Can be turned off with a -no-clean argument)
    if(clean == 1)
    {
        std::cout << "Cleaning up..." << std::endl;
        std::string removeCommand = "rm ";
        for (const auto & entry : fs::directory_iterator(root))
        {
            //Checks to make sure that we are not in the middle of deleting the Builder program.
            if(entry.path().generic_string().find(".o") != std::string::npos && entry.path().generic_string().find("build.o") == std::string::npos)
            {
                //Removing the rest of the path, that we don't need.
                int tmpIndex = entry.path().generic_string().find_last_of('/');
                tmpIndex++;
                std::string tmp = entry.path().generic_string().substr(tmpIndex,entry.path().generic_string().size()-tmpIndex);
                //Verbose feature to see what we picked up, in case it does something wrong, it will be easier to find out what happened.
                std::cout << "File : " << tmp << " Marked for removal."<< std::endl;
                tmp += " ";
                removeCommand += tmp;
            }
        }
        system(removeCommand.c_str());
    }
    return 0;
}
