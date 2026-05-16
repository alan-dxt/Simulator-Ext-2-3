#include <iostream>

#include "./ControllerDisk.h"
#include "../Objects/MBR.h"
#include "../Objects/Partition.h"
#include <fstream>
#include <cstdlib> 

using namespace std;

void ControllerDisk::writeMBR(string& path, MBR& mbr){
    fstream file(path, ios::in | ios::out | ios::binary);
    file.seekp(0);
    file.write((char*)&mbr, sizeof(MBR));
    file.close();
}

MBR ControllerDisk::readMBR(string& path){
    fstream file(path, ios::in | ios::out | ios::binary);
    MBR mbr;
    file.seekg(0);
    file.read((char*)&mbr, sizeof(MBR));
    file.close();
    return mbr;
}

bool ControllerDisk::disksExists(string& path){
    ifstream file(path, std::ios::binary);
    return file.good();
}

CommandResult ControllerDisk::createDisk(string& path, string& fit, int& size){
    if(disksExists(path)) return {false, "Mkdisk: The disk already exists"};
    //Creating the disk
    fstream file(path, ios:: out | ios::binary);
    file.seekp(size - 1);
    file.put('\0');
    file.close();
    
    MBR mbr{};
    
    mbr.mbr_size = size;
    mbr.mbr_date = time(nullptr);
    mbr.mbr_dsk_signature = rand();
    mbr.dsk_fit = fit[0];

    for(int i = 0; i < 4; i++){
        Partition& currentPartition = mbr.partitions[i];
        currentPartition.part_status = 'f';
        currentPartition.part_type = '-';
        currentPartition.part_fit = '-';
        currentPartition.part_start = -1;
        currentPartition.part_s = -1;
        currentPartition.part_correlatice = -1;
        currentPartition.part_name[0] = '-';
        currentPartition.part_id[0] = '-';
    }

    writeMBR(path, mbr);
    return {true, "Mkdisk: The disk was created succesfully"};
}

