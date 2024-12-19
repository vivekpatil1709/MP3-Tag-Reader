#ifndef VIEW_H
#define VIEW_H

#include"types.h"

struct MP3_tag_
{
    int size;
    char f_name[30];
    FILE * fptr_v; 
};

status view_details(struct MP3_tag_ *tags);

status vopen_file(struct MP3_tag_ *tags);

status print_details(struct MP3_tag_ *tags);

status Display(char *arr[]);

#endif