#ifndef PARTITION_H_INCLUDED
#define PARTITION_H_INCLUDED

#pragma pack(push, 1)
struct Partition {
    char    part_status;        //indicates wheter the partition is mounted
    char    part_type;          //Primary, extended or Logic(p/e/l)
    char    part_fit;           //b/f/w
    int     part_start;         //Byte where the partition starts
    char    part_name[16];      //Partition name
    int     part_correlatice;   //Correlative in the disk
    char    part_id[5];         //Id generated whent mounting the partition
};

#pragma pack(pop)

#endif