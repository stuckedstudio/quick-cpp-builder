//Created because I didn't want to learn to make makefiles... Sorry
#include <iostream>
#include <unistd.h>
#include <filesystem>
//Defining our search area for cpp files
std::string root;
std::string source;
bool includeEngine = false;
namespace fs = std::filesystem;
int windows = 0;
int clang = 0;
int clean = 1;
int main(int argc, char** argv)
{
    std::string extraCommands = "";
    std::string extraEndCommands = "";
    for(int i = 1; i < argc;i++)
    {   
        if(std::string(argv[i]) == "--no-clean")
        {
                std::cout << "Not cleaning"<<std::endl;
                clean = 0;     
        }
        else if(std::string(argv[i]) == "--debug")
        {
                std::cout << "Debugging enabled"<<std::endl;
                extraCommands += "-g ";
        }
        else if(std::string(argv[i]) == "--windows")
        {
                std::cout << "Building Windows Version 64bit"<<std::endl;
                windows = 1;
        }
        else if(std::string(argv[i]) == "--clang")
        {
                std::cout << "Using Clang"<<std::endl;
                clang = 1;
                //extraEndCommands += "-lc++abi ";
                extraEndCommands += "-lstdc++fs ";
        }
        else if(std::string(argv[i]) == "--Engine")
        {
                std::cout << "Searching Engine folder"<<std::endl;
                includeEngine = true;     
        }
        else if(std::string(argv[i]).find("--end-args=") != std::string::npos)
        {
            extraEndCommands += std::string(argv[i]).substr(std::string(argv[i]).find("=")+1,std::string(argv[i]).size()-(std::string(argv[i]).find("=")+1));
            extraEndCommands += " ";
        }
        
        else
        {
            extraCommands += argv[i];
            extraCommands += " ";
        }
        
       
    }
    std::string CXX = "";
    if(getenv("CXX") != NULL)
    {
        CXX = std::string(getenv("CXX"));
        if(windows == 1)
        {
            CXX = "x86_64-w64-mingw32-g++";
        }
    }
    else
    {
        
        if(windows == 1)
        {
            CXX = "x86_64-w64-mingw32-g++";
        }
        else
        {
            CXX = "Unknown";
        }
        
    }
    
    if((CXX.find("clang++") != std::string::npos && clang == 0) || CXX.find("x86_64-w64-mingw32-g++") != std::string::npos)
    {    
                clang = 1;
                //extraEndCommands += "-lc++abi ";
                extraEndCommands += "-lstdc++fs ";
    }
    std::cout << "Extra Commands: " << extraCommands << std::endl;
    //Getting the current directory and our Source directory
    root = fs::current_path().generic_string();
    std::cout << "Root set as: " << root << std::endl;
    std::string bin = "";
    std::string userbin = "";
    std::string engine = ""; 
    /*TEMPORARY!!*/
    userbin = "/Bin";
    engine = "/Engine";
    if(!includeEngine)
    {
        source = root + "/Source";
        std::cout << "Setting Source folder to " << source << std::endl;
        bin = root + userbin;
        std::cout << "Setting bin folder to " << source << std::endl;
    }
    else
    {
        source = root + engine + "/Source";
        bin = root + engine + userbin;
    }
    
    
    
    
    bool binExist;
    //Compiling all cpp files...
    for (const auto & entry : fs::directory_iterator(source))
    {
        std::string command = "";
        if(entry.path().generic_string().find(".cpp") != std::string::npos)
        {
        if(clang)
        {
           command = std::string(getenv("CXX")) + " -std=c++17 -c " + extraCommands + " " + entry.path().generic_string() + " " + extraEndCommands;
        }
        else
        {
            command = "g++ -std=c++17 -c " + extraCommands + " " + entry.path().generic_string() + " " + extraEndCommands;
        }
        std::cout << "Executing : " << command << std::endl;
        system(command.c_str());
        }
    }
    if(includeEngine)
    {
        std::string engineMainCompile = "";
        if(clang)
        {
           engineMainCompile = std::string(getenv("CXX")) + " -std=c++17 -c " + extraCommands + " " + "main.cpp" + " " + extraEndCommands;

        }
        else
        {
            engineMainCompile = "g++ -std=c++17 -c " + extraCommands + " " + "main.cpp" + " " + extraEndCommands;
        }
        std::cout << "Engine Included - Executing root main.cpp compile... " << engineMainCompile << std::endl;
        system(engineMainCompile.c_str());
    }
    //Preparing for the final compile
    
    std::string compileCommand = "";
    if(clang)
    {
        compileCommand = std::string(getenv("CXX")) + " -std=c++17 ";   
    }
    else
    {
        compileCommand = "g++ -std=c++17 ";
    }
    compileCommand += extraCommands;
    compileCommand += "-o ";
    compileCommand += bin;
    compileCommand += "/application ";
    for (const auto & entry : fs::directory_iterator(root))
    {
        //Check if the Bin folder exists.
            if(entry.path().generic_string().find(bin) != std::string::npos)
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
    for (const auto & entry : fs::directory_iterator(bin))
    {
     if(entry.path().generic_string().find(".o") != std::string::npos)
     {
         system("rm *.o");
     }
    }
    //Adding end-args (Due to the fact that g++ cares about argument placement...)
    compileCommand += extraEndCommands;
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
    bool complete = false;
    for (const auto & entry : fs::directory_iterator(bin))
    {
     if(entry.path().generic_string().find("application") != std::string::npos)
     {
         complete = true;
     }
    }
    if(complete)
    {
    std::cout << "Excecutable can be found at: " << bin << "/application" << std::endl;
    return 0;
    }
    else
    {
     return 1;   
    }
}
