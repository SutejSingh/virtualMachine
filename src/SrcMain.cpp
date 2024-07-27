#include "SrcMain.h"
#include <iostream>
#include "Machine.h"

void ProcessCommandArgs(int argc, const char* argv[])
{
    Machine machine;
    machine.readFile(argv[1]);
    machine.Execute();

}
