// removes both single-line and multi-line comments
#include<stdio.h>
#include<stdlib.h>
#include"comment_removal.h"
void remove_comments(const char *inputfile,const char *outputfile)
{
    char ch, next;
    FILE *fin=NULL;
    FILE *fout=NULL;
    // opening input file in read mode and output file in write mode
    fin = fopen(inputfile, "r");
    fout = fopen(outputfile, "w");
    if(fin == NULL || fout == NULL)
    {
        printf("failed to open\n");
        exit(0);
    }
    //reading line by line and searching for single line comment /
    while((ch = fgetc(fin)) != EOF)
    {
        if(ch == '/')
        {
            next = fgetc(fin);
            // single line comment
            if(next == '/')
            {
		// skip characters until newline is found
                while((ch = fgetc(fin)) != '\n' && ch != EOF);
                fputc('\n', fout);// write newline in output
                continue;
            }
             // checking for multi-line comment 
            else if(next == '*')
            {
		// keep reading until closing comment
                while(1)
                {
                    ch = fgetc(fin);
                    if(ch == EOF)
		    {
                        break;
		    }
                    if(ch == '*')
                    {
                        next = fgetc(fin);
                        if(next == '/')
                            break;
                    }
                }
                continue;// skip writing comment part
            }
            // if it is not comment, write both characters
            else
            {
                fputc(ch, fout);
                fputc(next, fout);
                continue;
            }
        }
	// normal characters are directly written to output
        else
        {
            fputc(ch, fout);
        }
    }
    fclose(fin);
    fclose(fout);
}

