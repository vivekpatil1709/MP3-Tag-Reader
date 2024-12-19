#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"view.h"

status view_details(struct MP3_tag_ *tags)
{
    if(!vopen_file(tags))                    // checking the file is open or not
        return e_failure;

    if(!print_details(tags))
        return e_failure;

    fclose(tags->fptr_v);
    return e_success;
}

status vopen_file(struct MP3_tag_ *tags)
{
    char ch[3];
    tags -> fptr_v = fopen(tags -> f_name,"r");             // read the data from the MP3 file
    fread(ch,3,1,tags -> fptr_v);
    if(!strcmp(ch,"ID3"))                                  // checking the MP3 tag
    {
        fseek(tags -> fptr_v,7,SEEK_CUR);
        return e_success;
    }
    else
        return e_failure;
}

status print_details(struct MP3_tag_ *tags)
{
    char *TAG[6]= {"TIT2","TPE1","TALB","TYER","TCON","COMM"};//  This is a Tag array so we want to search all these tags
    char *arr[6];
    char buf[4];
    char buf1[4];
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            fread(buf,4,1,tags->fptr_v);
            fread(buf1,4,1,tags->fptr_v);
            tags->size = buf1[3];
            if(!(strcmp(buf,TAG[i])))                  // checking each Tag
            {
                fseek(tags->fptr_v,3,SEEK_CUR);
                arr[i]=malloc(tags->size);
                fread(arr[i],(tags->size)-1,1,tags->fptr_v);         //reading the data of the each tags and storing in the  arr[] 
                fseek(tags->fptr_v,10,SEEK_SET);
                break;
            }
             fseek(tags->fptr_v,2+(tags->size),SEEK_CUR);
        }
    }

    Display(arr);            // calling the display function
    return e_success;   
}

status Display(char *arr[])                      
{
    printf("-------------------- SELECTED VIEW DETAILS --------------------------\n");        //printing all the details of the songs
    printf("---------------------------------------------------------------------\n");
    printf("\t\tMP3 TAG READER AND EDITOR FOR ID3v2\n");
    printf("---------------------------------------------------------------------\n");
    printf("TITLE\t\t:\t%s\nARTIST\t\t:\t%s\nALBUM\t\t:\t%s\nYEAR\t\t:\t%s\nMUSIC\t\t:\t%s\nCOMMENT\t\t:\t%s\n",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
    printf("---------------------------------------------------------------------\n");
    printf("---------------- DETAILS DISPLAYED SUCCESSFULLY ---------------------\n");

    return e_success;
}