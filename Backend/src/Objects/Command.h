#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <map>


struct Command {
    std::string name;
    std::map<std::string, std::string> params;
};

#endif