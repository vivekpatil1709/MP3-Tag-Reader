#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "edit.h"


status edit_details(struct MP3_tag *tag)
{
    if(!eopen_file(tag))                             // checking the mp3 file is open or not
        return e_failure;

    details(tag);
    copy(tag);

    return e_success; 
}

status eopen_file(struct MP3_tag *tag)
{
    char ch[4];
    tag -> fptr = fopen(tag -> f_name,"r");                   // read the data from the mp3 file
    tag->fptr1 =fopen("temp.mp3","w");                         // write into the temperory mp3 file
    fread(ch,3,1,tag -> fptr);
    ch[3]='\0';
    fwrite(ch,3,1,tag -> fptr1);
    if(!strcmp(ch,"ID3"))                         // checking the ID3 Tag
    {
        char buff[7];
        fread(buff,7,1,tag -> fptr);
        fwrite(buff,7,1,tag -> fptr1);                
        return e_success;
    }
    else
        return e_failure;
}

status details(struct MP3_tag *tag)
{
    char buf[5];
    char buf1[4];
    for(int i=0;i<6;i++)
    {
        fread(buf,4,1,tag->fptr);
        buf[5]='\0';
        fwrite(buf,4,1,tag -> fptr1);
        if(!(strcmp(buf,tag->str)))                   // checking which tag want to edit
        {
            char null[4];
            fread(null,4,1,tag->fptr);
            fwrite(null,3,1,tag->fptr1);
            tag->size=strlen(tag->var)+1;            // storing the size of which information want to edit from the CLA
            fwrite(&tag->size,1,1,tag->fptr1);
            // value stored

            int s=null[3];
            char u[3];
            fread(u,3,1,tag->fptr);
            fwrite(u,3,1,tag->fptr1);

            char buffer[s-1];
            fread(buffer,(s-1),1,tag->fptr);
            fwrite(tag->var,tag->size-1,1,tag->fptr1);
            break;
        }
        fread(buf1,4,1,tag->fptr);
        fwrite(buf1,4,1,tag->fptr1);
        tag->size = buf1[3]+2;

        char ch[tag->size];
        fread(ch,tag->size,1,tag->fptr);
        fwrite(ch,tag->size,1,tag->fptr1);
    }     
    
    char get; 
    get=getc(tag->fptr);
    while(get!=EOF)
    {
        putc(get,tag->fptr1);                        // coping the data from the mp3 file to the temporoary file
        get=getc(tag->fptr);
    }
    
    fclose(tag->fptr);
    fclose(tag->fptr1);
}

status copy(struct MP3_tag *tag)
{
    tag->fptr = fopen(tag->f_name,"r+");                    // opening the data of the MP3 File int r+ mode because want to copy the audio file also
    tag->fptr1 = fopen("temp.mp3","r");                        // opening the temporary file in the read moder
    char get; 
    get=getc(tag->fptr1);
    while(get!=EOF)
    {
        putc(get,tag->fptr);                // coping the data from the temporary mp3 file to the MP3 file
        get=getc(tag->fptr1);
    }
    fclose(tag->fptr);
    fclose(tag->fptr1);
}