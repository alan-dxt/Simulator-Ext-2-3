#include <iostream>

#include <map>
#include "./RoutesDisk.h"
#include "../Controllers/ControllerDisk.h"

using namespace std;

CommandResult RoutesDisk::mkdisk(map<std::string, std::string> params){
    if(params.find("size") == params.end()) return {false, "Mkdisk: Missing parameter -size"};
    if(params.find("path") == params.end()) return {false, "Mkdisk: Missing parameter -path"};

    std::string path = "src/Disks/" + params["path"];
    int size;
    try{ size = stoi(params["size"]); }
    catch(...) {return {false, ""};}

    string fit = "ff";
    if(params.find("fit") != params.end()) fit = params["fit"];
    if(fit != "bf" && fit != "ff" && fit != "wf") return {false, "Mkdisk: Invelid type of fit"};

    string unit = "m";
    if(params.find("unit") != params.end()) unit = params["unit"];
    if(unit != "m" && unit != "k") return {false, "Mkdisk: Invelid type of unit"};
    if(unit == "k") size *= 1024;
    else if(unit == "m") size *= 1024 * 1024;

    return ControllerDisk::createDisk(path, fit, size);
}
