#include "Ops.h"
#include "Machine.h"
#include "Exceptions.h"

void Exit::Execute(Machine& machine)
{
    machine.setFlag("exit", true);
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
}

void MovI::Execute(Machine& machine)
{
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc" && (std::get<1>(mParameters) < 0 || std::get<1>(mParameters) > 7)){
        throw NonFatalException("Invalid color value", 14);
    }

    machine.setRegister(std::get<0>(mParameters), std::get<1>(mParameters));
}

void Add::Execute(Machine &machine) {

    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
    machine.setRegister(std::get<0>(mParameters), machine.getRegisterValue(std::get<1>(mParameters)) +
                                                  machine.getRegisterValue(std::get<2>(mParameters)));

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc"){
        int result = machine.getRegisterValue(std::get<1>(mParameters)) + machine.getRegisterValue(std::get<2>(mParameters));
        if(result < 0 || result > 7){
            throw NonFatalException("Invalid color value", 14);
        }
    }

    // check for overflow and underflow
    auto a = static_cast<int64_t>(machine.getRegisterValue(std::get<1>(mParameters)));
    auto b = static_cast<int64_t>(machine.getRegisterValue(std::get<2>(mParameters)));
    int64_t result = a + b;

    if(result > std::numeric_limits<int>::max()){
        throw NonFatalException("Overflow detected", 12);
    }
    else if(result < std::numeric_limits<int>::min()){
        throw NonFatalException("Underflow detected", 13);
    }


}

void Mov::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc" && (machine.getRegisterValue(std::get<1>(mParameters)) < 0 || machine.getRegisterValue(std::get<1>(mParameters)) > 7)){
        throw NonFatalException("Invalid color value", 14);
    }

    machine.setRegister(std::get<0>(mParameters), machine.getRegisterValue(std::get<1>(mParameters)));
}

void Sub::Execute(Machine &machine) {

    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
    machine.setRegister(std::get<0>(mParameters), machine.getRegisterValue(std::get<1>(mParameters)) -
                                                  machine.getRegisterValue(std::get<2>(mParameters)));

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc"){
        int result = machine.getRegisterValue(std::get<1>(mParameters)) - machine.getRegisterValue(std::get<2>(mParameters));
        if(result < 0 || result > 7){
            throw NonFatalException("Invalid color value", 14);
        }
    }

    // check for overflow and underflow
    auto a = static_cast<int64_t>(machine.getRegisterValue(std::get<1>(mParameters)));
    auto b = static_cast<int64_t>(machine.getRegisterValue(std::get<2>(mParameters)));
    int64_t result = a - b;

    if(result > std::numeric_limits<int>::max()){
        throw NonFatalException("Overflow detected", 12);
    }
    else if(result < std::numeric_limits<int>::min()){
        throw NonFatalException("Underflow detected", 13);
    }


}

void Mul::Execute(Machine &machine) {

    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
    machine.setRegister(std::get<0>(mParameters), machine.getRegisterValue(std::get<1>(mParameters)) *
                                                  machine.getRegisterValue(std::get<2>(mParameters)));

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc"){
        int result = machine.getRegisterValue(std::get<1>(mParameters)) * machine.getRegisterValue(std::get<2>(mParameters));
        if(result < 0 || result > 7){
            throw NonFatalException("Invalid color value", 14);
        }
    }

    // check for overflow and underflow
    auto a = static_cast<int64_t>(machine.getRegisterValue(std::get<1>(mParameters)));
    auto b = static_cast<int64_t>(machine.getRegisterValue(std::get<2>(mParameters)));

    int64_t result = a * b;

    if(result > std::numeric_limits<int>::max()){
        throw NonFatalException("Overflow detected", 12);
    }
    else if(result < std::numeric_limits<int>::min()){
        throw NonFatalException("Underflow detected", 13);
    }


}

void Div::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    if(machine.getRegisterValue(std::get<2>(mParameters)) == 0){
        throw FatalException("Division by zero", 102);
    }

    machine.setRegister(std::get<0>(mParameters), machine.getRegisterValue(std::get<1>(mParameters)) /
                                                  machine.getRegisterValue(std::get<2>(mParameters)));

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc"){
        int result = machine.getRegisterValue(std::get<1>(mParameters)) / machine.getRegisterValue(std::get<2>(mParameters));
        if(result < 0 || result > 7){
            throw NonFatalException("Invalid color value", 14);
        }
    }


}

void Inc::Execute(Machine &machine) {

    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
    machine.setRegister(std::get<0>(mParameters), machine.getRegisterValue(std::get<0>(mParameters)) + 1);


    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc"){
        int result = machine.getRegisterValue(std::get<0>(mParameters)) + 1;
        if(result < 0 || result > 7){
            throw NonFatalException("Invalid color value", 14);
        }
    }

    // check for overflow
    int64_t result = static_cast<int64_t>(machine.getRegisterValue(std::get<0>(mParameters))) + 1;
    if(result > std::numeric_limits<int>::max()){
        throw NonFatalException("Overflow detected", 12);
    }

}


void Dec::Execute(Machine &machine) {

    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
    machine.setRegister(std::get<0>(mParameters), machine.getRegisterValue(std::get<0>(mParameters)) - 1);

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc"){
        int result = machine.getRegisterValue(std::get<0>(mParameters)) - 1;
        if(result < 0 || result > 7){
            throw NonFatalException("Invalid color value", 14);
        }
    }

    // check for underflow
    int64_t result = static_cast<int64_t>(machine.getRegisterValue(std::get<0>(mParameters))) - 1;
    if(result < std::numeric_limits<int>::min()){
        throw NonFatalException("Underflow detected", 13);
    }

}

void Jmp::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue(std::get<0>(mParameters)));
}

void Cmpeq::Execute(Machine &machine) {
    bool value =
            machine.getRegisterValue(std::get<0>(mParameters)) == machine.getRegisterValue(std::get<1>(mParameters));
    machine.setFlag("test", value);
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
}

void Cmplt::Execute(Machine &machine) {
    bool value = machine.getRegisterValue(std::get<0>(mParameters)) < machine.getRegisterValue(std::get<1>(mParameters));
    machine.setFlag("test", value);
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
}

void Jt::Execute(Machine &machine) {
    if (machine.getFlag("test")) {
        machine.setRegister("pc", machine.getRegisterValue(std::get<0>(mParameters)));
    }
    else{
        machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
    }
}

void Jnt::Execute(Machine &machine) {
    if (!machine.getFlag("test")) {
        machine.setRegister("pc", machine.getRegisterValue(std::get<0>(mParameters)));
    }
    else{
        machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
    }
}

/* Stack operations */

void Push::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    if(machine.getStackSize() == 256){
        throw FatalException("Stack Overflow", 101);
    }

    machine.pushStack(machine.getRegisterValue(std::get<0>(mParameters)));
}

void Pop::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    if(machine.getStackSize() == 0){
        throw FatalException("Pop when Stack is empty", 103);
    }

    machine.setRegister(std::get<0>(mParameters), machine.popStack());
}

void Load::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    int stackIdx = machine.getRegisterValue(std::get<1>(mParameters));
    if(stackIdx < 0 || stackIdx >= machine.getRegisterValue("sc")){
        throw FatalException("Access Violation: Invalid stack index", 100);
    }

    int value = machine.getStackAt(stackIdx);

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc" && (value < 0 || value > 7)){
        throw NonFatalException("Invalid color value", 14);
    }

    machine.setRegister(std::get<0>(mParameters), machine.getStackAt(machine.getRegisterValue(std::get<1>(mParameters))));
}


void Store::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    int stackIdx = machine.getRegisterValue(std::get<0>(mParameters));
    if(stackIdx < 0 || stackIdx >= machine.getRegisterValue("sc")){
        throw FatalException("Access Violation: Invalid stack index", 100);
    }

    machine.setStackAt(machine.getRegisterValue(std::get<0>(mParameters)), machine.getRegisterValue(std::get<1>(mParameters)));
}


void LoadI::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    int stackIdx = std::get<1>(mParameters);
    if(stackIdx < 0 || stackIdx >= machine.getRegisterValue("sc")){
        throw FatalException("Access Violation: Invalid stack index", 100);
    }

    int value = machine.getStackAt(stackIdx);

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc" && (value < 0 || value > 7)){
        throw NonFatalException("Invalid color value", 14);
    }

    machine.setRegister(std::get<0>(mParameters), machine.getStackAt(std::get<1>(mParameters)));
}

void StoreI::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    int stackIdx = std::get<0>(mParameters);

    if(stackIdx < 0 || stackIdx >= machine.getRegisterValue("sc")){
        throw FatalException("Access Violation: Invalid stack index", 100);
    }

    machine.setStackAt(std::get<0>(mParameters), machine.getRegisterValue(std::get<1>(mParameters)));
}

void LoadSc::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    int stackIdx = machine.getRegisterValue(("sc")) - machine.getRegisterValue(std::get<1>(mParameters)) - 1;
    if(stackIdx < 0 || stackIdx >= machine.getRegisterValue("sc")){
        throw FatalException("Access Violation: Invalid stack index", 100);
    }

    int value = machine.getStackAt(stackIdx);

    if(std::get<0>(mParameters) == "sc"){
        throw NonFatalException("Cannot modify the stack counter", 10);
    }
    else if(std::get<0>(mParameters) == "r0"){
        throw NonFatalException("Cannot modify r0", 11);
    }
    else if(std::get<0>(mParameters) == "tc" && (value < 0 || value > 7)){
        throw NonFatalException("Invalid color value", 14);
    }

    machine.setRegister(std::get<0>(mParameters), machine.getStackAt(machine.getRegisterValue("sc") - machine.getRegisterValue(std::get<1>(mParameters)) - 1));
}

void StoreSc::Execute(Machine &machine) {
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);

    int stackIdx = machine.getRegisterValue("sc") - machine.getRegisterValue(std::get<0>(mParameters)) - 1;
    if(stackIdx < 0 || stackIdx >= machine.getRegisterValue("sc")){
        throw FatalException("Access Violation: Invalid stack index", 100);
    }

    machine.setStackAt(machine.getRegisterValue("sc") - machine.getRegisterValue(std::get<0>(mParameters)) - 1, machine.getRegisterValue(std::get<1>(mParameters)));
}

/* Turtle operations */

void PenDown::Execute(Machine &machine) {
    machine.setFlag("pen", true);
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
}

void PenUp::Execute(Machine &machine) {
    machine.setFlag("pen", false);
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
}


void Fwd::Execute(Machine &machine) {

    machine.forward(machine.getRegisterValue(std::get<0>(mParameters)));
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
}

void Back::Execute(Machine &machine) {
    machine.forward(-1 * machine.getRegisterValue(std::get<0>(mParameters)));
    machine.setRegister("pc", machine.getRegisterValue("pc") + 1);
}
