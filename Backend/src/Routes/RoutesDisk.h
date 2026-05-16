#ifndef ROUTESDISK_H_INCLUDED
#define ROUTESDISK_H_INCLUDED

#include <string>
#include <map>
#include "../Objects/CommandResult.h"

class RoutesDisk{
    public:
        static CommandResult mkdisk(std::map<std::string, std::string> params);
        static CommandResult rmdisk(std::map<std::string, std::string> params);
        static CommandResult fdisk(std::map<std::string, std::string> params);
};

#endif