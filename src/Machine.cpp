#include "Machine.h"
#include "../tests/catch.hpp"
#include "Exceptions.h"
#include <iostream>
Machine::Machine()
        : image(320,240)
        , drawer(image)
{
    /* Init Ops map */
    opMap.emplace("movi", &CreateOp<MovI>);
    opMap.emplace("exit", &CreateOp<Exit>);
    opMap.emplace("add", &CreateOp<Add>);
    opMap.emplace("mov", &CreateOp<Mov>);
    opMap.emplace("sub", &CreateOp<Sub>);
    opMap.emplace("mul", &CreateOp<Mul>);
    opMap.emplace("div", &CreateOp<Div>);
    opMap.emplace("inc", &CreateOp<Inc>);
    opMap.emplace("dec", &CreateOp<Dec>);
    opMap.emplace("jmp", &CreateOp<Jmp>);
    opMap.emplace("cmpeq", &CreateOp<Cmpeq>);
    opMap.emplace("cmplt", &CreateOp<Cmplt>);
    opMap.emplace("jt", &CreateOp<Jt>);
    opMap.emplace("jnt", &CreateOp<Jnt>);
    /* Stack Ops */
    opMap.emplace("push", &CreateOp<Push>);
    opMap.emplace("pop", &CreateOp<Pop>);
    opMap.emplace("load", &CreateOp<Load>);
    opMap.emplace("store", &CreateOp<Store>);
    opMap.emplace("loadi", &CreateOp<LoadI>);
    opMap.emplace("storei", &CreateOp<StoreI>);
    opMap.emplace("loadsc", &CreateOp<LoadSc>);
    opMap.emplace("storesc", &CreateOp<StoreSc>);
    /* Turle Ops */
    opMap.emplace("penup", &CreateOp<PenUp>);
    opMap.emplace("pendown", &CreateOp<PenDown>);
    opMap.emplace("fwd", &CreateOp<Fwd>);
    opMap.emplace("back", &CreateOp<Back>);

    /* Init Registers */
    mRegisters["r0"] = 0; // Always 0
    mRegisters["r1"] = 0; // General purpose
    mRegisters["r2"] = 0; // General purpose
    mRegisters["r3"] = 0; // General purpose
    mRegisters["r4"] = 0; // General purpose
    mRegisters["r5"] = 0; // General purpose
    mRegisters["r6"] = 0; // General purpose
    mRegisters["r7"] = 0; // General purpose

    mRegisters["pc"] = 0; // Program counter
    mRegisters["sc"] = 0; // Stack counter
    mRegisters["ex"] = 0; // Exception code
    mRegisters["tx"] = 0; // Turtle's x position
    mRegisters["ty"] = 0; // Turtle's y position
    mRegisters["tr"] = 0; // Turtle's rotation in degrees
    mRegisters["tc"] = 0; // Turtle's color

    /* Init Flags */
    mFlags["exit"] = false; // If true, exit the program
    mFlags["test"] = false; // Used for conditional jumps
    mFlags["pen"] = false; // If true, turtle draws

    logFile.open(filename);
    stackLogFile.open(stackLogFileName);

    image.set_all_channels(0,0,0);
    drawer.pen_width(1);
    drawer.pen_color(255,255,255);

}

void Machine::readFile(const std::string& filename) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        log("ERROR File not found: " + filename);
        throw std::runtime_error("ERROR File not found: " + filename);
    }
    std::string line;

    while (std::getline(file, line)) {

        std::string opName = line.substr(0, line.find(' '));
        std::string params = line.substr(line.find(' ') + 1);

        std::shared_ptr<Op> op = opMap.at(opName)();

        op->Parse(params);
        mOps.push_back(op);

    }
}

void Machine::Execute()
{
    while (!mFlags["exit"])
    {
        log(mOps[mRegisters["pc"]]->GetName());
        try{
            mOps[mRegisters["pc"]]->Execute(*this);
        }
        catch(NonFatalException& e){
            mRegisters["ex"] = e.getErrorCode();
        }
        catch(FatalException& e){
            mRegisters["ex"] = e.getErrorCode();
            mFlags["exit"] = true;
            break;
        }

    }

    log("");
    logFile.close();
    stackLogFile.close();
    image.save_image("output.bmp");

}


void Machine::setFlag(const std::string& flag, bool value)
{
    mFlags[flag] = value;
}

bool Machine::getFlag(const std::string& flag) const
{
    return mFlags.at(flag);
}

void Machine::setRegister(const std::string& reg, int value)
{
    mRegisters[reg] = value;
}

int Machine::getRegisterValue(const std::string& reg) const
{
    return mRegisters.at(reg);
}

void Machine::log(const std::string& executingOpName){

    if(executingOpName.find("ERROR") != std::string::npos){
        logFile << executingOpName << "\n";
        return;
    }

    logFile << "********************\n";

    /* Print Register Values */
    logFile << "r0=" << mRegisters["r0"] << "\n";
    logFile << "r1=" << mRegisters["r1"] << "\n";
    logFile << "r2=" << mRegisters["r2"] << "\n";
    logFile << "r3=" << mRegisters["r3"] << "\n";
    logFile << "r4=" << mRegisters["r4"] << "\n";
    logFile << "r5=" << mRegisters["r5"] << "\n";
    logFile << "r6=" << mRegisters["r6"] << "\n";
    logFile << "r7=" << mRegisters["r7"] << "\n";


    logFile << "pc=" << mRegisters["pc"] << "\n";
    logFile << "sc=" << mRegisters["sc"] << "\n";
    logFile << "ex=" << mRegisters["ex"] << "\n";
    logFile << "tx=" << mRegisters["tx"] << "\n";
    logFile << "ty=" << mRegisters["ty"] << "\n";
    logFile << "tr=" << mRegisters["tr"] << "\n";
    logFile << "tc=" << mRegisters["tc"] << "\n";

    /* Print Flags */
    logFile << "exit=" << mFlags["exit"] << "\n";
    logFile << "test=" << mFlags["test"] << "\n";
    logFile << "pen=" << mFlags["pen"] << "\n";

    if(!executingOpName.empty()){
        logFile << "Executing: " << executingOpName << "\n";
    }

    stackLogFile << "pc: " << mRegisters["pc"] << " Stack: ";
    for (int i = 0; i < mRegisters["sc"]; i++) {
        stackLogFile << mStack[i] << " ";
    }
    stackLogFile << "\n";


}

void Machine::pushStack(int value) {
    mStack.push_back(value);
    mRegisters["sc"]++;
}

int Machine::popStack() {
    int value = mStack.back();
    mStack.pop_back();
    mRegisters["sc"]--;
    return value;
}

int Machine::getStackAt(int index) {
    return mStack[index];
}

void Machine::setStackAt(int index, int value) {
    mStack[index] = value;
}

/* Turtle Ops*/

void Machine::forward(const int& value){
    int x = mRegisters["tx"];
    int y = mRegisters["ty"];

    float angleRads = static_cast<float>(mRegisters["tr"]) * 0.0174533f;
    int endx = x + static_cast<int>(std::cos(angleRads) * value);
    int endy = y + static_cast<int>(std::sin(angleRads) * value);

    if(mFlags["pen"]){
        switch (mRegisters["tc"])
        {
            case 0:
                drawer.pen_color(255, 255, 255);
                break;

            case 1:
                drawer.pen_color(255, 255, 0);
                break;

            case 2:
                drawer.pen_color(255, 0, 255);
                break;

            case 3:
                drawer.pen_color(255, 0, 0);
                break;

            case 4:
                drawer.pen_color(0, 255, 255);
                break;

            case 5:
                drawer.pen_color(0, 255, 0);
                break;

            case 6:
                drawer.pen_color(0, 0, 255);
                break;

            case 7:
                drawer.pen_color(0, 0, 0);
                break;
        }

        drawer.line_segment(x, y, endx, endy);
    }

    mRegisters["tx"] = endx;
    mRegisters["ty"] = endy;

}

int Machine::getStackSize() const {
    return static_cast<int>(mStack.size());
}



