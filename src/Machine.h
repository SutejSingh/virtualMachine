#pragma once
#include "Ops.h"
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <fstream>  // For std::ifstream
#include <string>   // For std::string
#include "../img/bitmap_image.hpp"


class Machine
{
public:
    Machine();

    void readFile(const std::string& filename);

    void Execute();

    void setFlag(const std::string& flag, bool value);
    bool getFlag(const std::string& flag) const;
    void setRegister(const std::string& reg, int value);
    int getRegisterValue(const std::string& reg) const;

    void pushStack(int value);
    int popStack();
    int getStackAt(int index);
    void setStackAt(int index, int value);
    int getStackSize() const;

    void forward(const int& value);

private:
    std::vector<std::shared_ptr<Op>> mOps;
    std::map<std::string, std::function<std::shared_ptr<Op>()>> opMap;
    std::unordered_map<std::string, int> mRegisters;
    std::unordered_map<std::string, bool> mFlags;
    std::vector<int> mStack;

    void log(const std::string& executingOpName);

    std::string filename = "log.txt";
    std::ofstream logFile;

    std::string stackLogFileName = "stack.txt";
    std::ofstream stackLogFile;

    bitmap_image image;
    image_drawer drawer;
};


template <typename T>
static std::shared_ptr<T> CreateOp(){
    return std::make_shared<T>();
}