// This function processes header file inclusion directives
// It copies user-defined and standard header file contents into the output file

#include<stdio.h>      // File handling functions
#include<stdlib.h>     // exit()
#include<string.h>     // String handling functions
#include"file_inclusion.h"   // User-defined header

void header_file_inclusion(const char *inputfile,const char *outputfile)
{
        int i,j;
        char str[100], header[100];   // Buffers for reading lines and header names

        FILE *fin = NULL;      // Input source file pointer
        FILE *fout = NULL;     // Output file pointer
        FILE *fheader = NULL;  // Header file pointer

        // Open input and output files
        fin = fopen(inputfile,"r");
        fout = fopen(outputfile,"w");

        // Check for file opening errors
        if(fin == NULL || fout == NULL)
        {
                printf("Failed to open file\n");
                exit(0);
        }

        // Read input file line by line
        while((fgets(str,sizeof(str),fin)) != NULL)
        {
                // -------- USER-DEFINED HEADER FILE --------
                // Check if line contains: #include "filename.h"
                if(strstr(str,"#include\"") != NULL)
                {
                        // Find the starting quote of header file name
                        i = 0;
                        while(str[i] != '\"')
                        {
                                i++;
                        }

                        // Move to first character of filename
                        if(str[i] == '\"')
                        {
                                i++;
                        }

                        j = 0;

                        // Extract header file name between quotes
                        while(str[i] != '\"')
                        {
                                header[j] = str[i];
                                i++;
                                j++;
                        }
                        header[j] = '\0';   // Null-terminate the string

                        // Open the header file
                        fheader = fopen(header,"r");

                        if(fheader == NULL)
                        {
                                printf("Failed to open header file\n");
                                exit(0);
                        }
                        else
                        {
                                // Copy header file contents to output file
                                while((fgets(str,sizeof(str),fheader)) != NULL)
                                {
                                        fputs(str,fout);
                                }
                                fclose(fheader);
                        }
                }

                // -------- STANDARD HEADER FILE --------
                // Check if line contains: #include <...>
                else if(strstr(str,"#include<") != NULL)
                {
                        // Example path for standard header (simplified handling)
                        char path[300]="/usr/include/stdio.h";

                        fheader = fopen(path,"r");

                        if(fheader == NULL)
                        {
                                printf("Error: Standard header file not found\n");
                                exit(0);
                        }
                        else
                        {
                                // Copy standard header content to output file
                                while((fgets(str,sizeof(str),fheader)) != NULL)
                                {
                                        fputs(str,fout);
                                }
                                fclose(fheader);
                        }
                }

                // -------- NORMAL CODE --------
                // Copy remaining lines as it is
                else
                {
                        fputs(str,fout);
                }
        }

        // Close both input and output files
        fclose(fin);
        fclose(fout);
}
