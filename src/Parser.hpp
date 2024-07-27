#pragma once
#include <string>
#include <vector>
#include <tuple>

inline std::vector<std::string> Split(const std::string& str)
{
    char constexpr delim = ',';
    std::vector<std::string> retVal;

    size_t start = 0;
    size_t delimLoc = str.find_first_of(delim, start);
    while (delimLoc != std::string::npos)
    {
        retVal.emplace_back(str.substr(start, delimLoc - start));

        start = delimLoc + 1;
        delimLoc = str.find_first_of(delim, start);
    }

    retVal.emplace_back(str.substr(start));
    return retVal;
}

// Generic version of ParseElem
// If this generic version is instantiated, it won't compile
template <typename T>
std::tuple<T> ParseElem(const std::string& elem){}

// Specialization ParseElem<int>
// Converts elem to a tuple{int}
template <>
inline std::tuple<int> ParseElem<int>(const std::string& elem)
{
    return std::make_tuple(std::stoi(elem));
}

// Specialization ParseElem<std::string>
// Just makes a tuple{str} from elem
template <>
inline std::tuple<std::string> ParseElem<std::string>(const std::string& elem)
{
    return std::make_tuple(elem);
}

// Template for ParseStr for:
//– Has 0 or more template parameter types
//– Returns a tuple corresponding to the 0 or more template types
//– Takes in a vector of strings (the different parameter strings)

template <typename... Args>
std::tuple<Args...> ParseStr(std::vector<std::string>& paramV);

// specialization for where there are no types passed to the template:
// base case
template <>
inline std::tuple<> ParseStr<>(std::vector<std::string>& paramV)
{
    return std::make_tuple();
}

//Declare ParseStrHelper, which has these template params:
//– A single type T
//– Zero or more additional types Args

template <typename T, typename... Args>
std::tuple<T, Args...> ParseStrHelper(std::vector<std::string>& paramV);

// Implementation
template <typename T, typename... Args>
std::tuple<T, Args...> ParseStrHelper(std::vector<std::string>& paramV)
{
    // Get the last element of the vector
    // This assumes paramV is in reverse
    std::string elem = paramV.back();
    paramV.pop_back();

    return std::tuple_cat(ParseElem<T>(elem), ParseStr<Args...>(paramV));
}

template <typename... Args>
std::tuple<Args...> ParseStr(std::vector<std::string>& paramV)
{
    return ParseStrHelper<Args...>(paramV);
}


