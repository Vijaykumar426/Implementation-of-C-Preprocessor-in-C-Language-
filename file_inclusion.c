// This function takes user-defined header file content
// and copies it into the output file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"file_inclusion.h"
void header_file_inclusion(const char *inputfile,const char *outputfile)
{
        int i,j;
        char str[100],header[100];
        FILE *fin=NULL;
        FILE *fout=NULL;
        FILE *fheader=NULL;
        fin=fopen(inputfile,"r");
        fout=fopen(outputfile,"w");
        if(fin==NULL||fout==NULL)
        {
                printf("failed to open\n");
                exit(0);
        }
        // reading input file line by line
        while((fgets(str,sizeof(str),fin))!=NULL)
        {
                // checking if line contains #include "file"
                if(strstr(str,"#include\"")!=NULL)
                {
                        // finding starting quote
                        i=0;
                        while(str[i]!='"')
                        {
                                i++;
                        }
                        if(str[i]=='"')
                        {
                                i++;// move to first character of filename
                        }
                        j=0;
                        //extracting the header file name
			while(str[i]!='"')
                        {
                                header[j]=str[i];
                                i++;
                                j++;
                        }
                        header[j]='\0';
                        //opening the header file
                        //copying the header file content to output file
                        fheader=fopen(header,"r");
                        if(fheader==NULL)
                        {
                                printf("failed to open\n");
                                exit(0);
                        }
                        else
                        {
                                while((fgets(str,sizeof(str),fheader))!=NULL)
                                {
                                        fputs(str,fout);
                                }
                                fclose(fheader);
                        }
                }
		else if(strstr(str,"#include<")!=NULL)
                {
                  char path[300]="/usr/include/stdio.h";
                  fheader=fopen(path,"r");
                        if(fheader==NULL)
                        {
                                printf("Error:header file is not found\n");
                                exit(0);
                        }
                        else
                        {
                                while((fgets(str,sizeof(str),fheader))!=NULL)
                                {
                                        fputs(str,fout);
                                }
                                fclose(fheader);
                        }
                }
                //remaining normal lines are copied as it is
                else
                {
                        fputs(str,fout);
                }
        }
        //closing the both files
        fclose(fin);
        fclose(fout);
}
