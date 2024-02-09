#include <iostream>

#include "include/CreateGuildFS.hpp"

int main(int argc, char *argv[])
{
    if (argc == 3 && std::string(argv[1]) == "init")
    {
        std::string projectName = argv[2];
        createGuildStructure(projectName);
        std::cout << "Initialization complete. Folder structure created for project: " << projectName << std::endl;
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " init [name]" << std::endl;
    }

    return 0;
}
