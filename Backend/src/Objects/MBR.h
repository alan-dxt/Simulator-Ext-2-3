#ifndef MBR_H_INCLUDED
#define MBR_H_INCLUDED

#include <ctime>
#include "./Partition.h"

#pragma pack(push, 1)
struct MBR {
    int     mbr_size;           //disk size in bytes
    time_t  mbr_date;           //date of creation
    int     mbr_dsk_signature;  //number that identifies the disk(random)
    char    dsk_fit;            //Type of fit in the disk
    Partition partitions[4];
};
#pragma pack(pop)

#endif