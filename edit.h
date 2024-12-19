#ifndef EDIT_H
#define EDIT_H

#include "types.h"

struct MP3_tag
{
    char var[40];
    char str[5];
    int size;
    char f_name[30];
    FILE *fptr;
    FILE *fptr1; 
};

status edit_details(struct MP3_tag *tag);

status eopen_file(struct MP3_tag *tag);

status details(struct MP3_tag *tag);

status copy(struct MP3_tag *tag);

#endif