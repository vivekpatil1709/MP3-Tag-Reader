/*
Name :- Vivek Bharat Patil
Date :- 09/10/2024
Description :- MP3 Tag Reader
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"view.h"
#include"edit.h"
#include"types.h"

int main(int argc, char *argv[])
{
    if(argc==2 && !strcmp(argv[1],"--help"))                   // checking if user want help menu
    {
        printf("---------------------------- HELP MENU -----------------------------\n\n");
        printf(" 1. -v -> to view mp3 file contents\n 2. -e -> to edit mp3 file contents\n \t2.1. -t -> to edit song title\n \t2.2. -a -> to edit artist name\n \t2.3. -A -> to edit album name\n \t2.4. -y -> to edit year\n \t2.5. -m -> to edit content\n \t2.6. -c -> to edit comment\n");
        printf("---------------------------------------------------------------------\n");
    }
    else if(argc==3 && ((!strcmp(argv[1],"-v"))||(!strcmp(argv[1],"-V")))) // checking to view the tags from the file
    {
        struct MP3_tag_ tags;
        char *ch=strchr(argv[2],'.');
        if(ch!=NULL && (!strcmp(ch,".mp3")))
        {
            strcpy(tags.f_name,argv[2]);
            if(view_details(&tags))
                printf("INFO : ## VIEW DONE ##\n");
            else
                printf("ERROR : VIEW FAILURE\n");
        }
        else
        {
            printf("ERROR : < .mp3 File Required >\n");
            return e_failure;
        }
    }
    else if(argc==5 && ((!strcmp(argv[1],"-e"))||(!strcmp(argv[1],"-E")))) // checking if user want to edit the specific tags
    {
        struct MP3_tag tag;
        char *ch=strchr(argv[4],'.');
        if(ch!=NULL && (!strcmp(ch,".mp3")))
        {
            if(!strcmp(argv[2],"-t"))
                strcpy(tag.str,"TIT2");
            else if(!strcmp(argv[2],"-a"))
                strcpy(tag.str,"TPE1");
            else if(!strcmp(argv[2],"-A"))
                strcpy(tag.str,"TALB");
            else if(!strcmp(argv[2],"-y"))
                strcpy(tag.str,"TYER");
            else if(!strcmp(argv[2],"-m"))
                strcpy(tag.str,"TCON");
            else if(!strcmp(argv[2],"-c"))
                strcpy(tag.str,"COMM");

            strcpy(tag.var,argv[3]);
            strcpy(tag.f_name,argv[4]);
            if(edit_details(&tag))
                printf("INFO : ## EDIT DONE ##\n");
            else
                printf("ERROR : EDIT FAILURE\n");
        }
        else
        {
            printf("ERROR : < .mp3 File Required >\n");
            return e_failure;
        }
    }
    else
    {
        printf("---------------------------------------------------------------------\n\n"); // error messgae
        printf("ERROR : ./a.out: INVALID ARGUMENTS\nUSAGE :\n");
        printf("To view please pass like: ./a.out -v mp3filename\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        printf("To get help pass like: ./a.out --help\n");
        printf("---------------------------------------------------------------------\n");
    }
}