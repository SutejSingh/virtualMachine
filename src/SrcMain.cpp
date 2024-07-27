#include "SrcMain.h"
#include <iostream>
#include "Machine.h"
#include "../tests/catch.hpp"

void ProcessCommandArgs(int argc, const char* argv[])
{
    if (argc < 2){
        std::cout << "No file specified\n";
        return;
    }

    Machine machine;
    try {
        machine.readFile(argv[1]);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }
    machine.Execute();

}
