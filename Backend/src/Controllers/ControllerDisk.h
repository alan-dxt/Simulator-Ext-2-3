#ifndef CONTROLLERDISK_H_INCLUDED
#define CONTROLLERDISK_H_INCLUDED

#include <string>
#include "../Objects/MBR.h"
#include "../Objects/CommandResult.h"

class ControllerDisk{
    public:
        static MBR readMBR(std::string& path);
        static void writeMBR(std::string& path, MBR& mbr);
        static bool disksExists(std::string& path);
        static CommandResult createDisk(std::string&path, std::string& fit, int& size);
        static CommandResult deleteDisk(std::string& path);
};

#endif