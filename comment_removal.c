// This function removes both single-line (//) and multi-line (/* */) comments
// from a C source file and generates a clean output file.

#include<stdio.h>      // File handling functions
#include<stdlib.h>     // exit()
#include"comment_removal.h"   // User-defined header

void remove_comments(const char *inputfile,const char *outputfile)
{
    char ch, next;     // Variables to store characters from file
    FILE *fin = NULL;  // Pointer for input file
    FILE *fout = NULL; // Pointer for output file

    // Open input file in read mode and output file in write mode
    fin = fopen(inputfile, "r");
    fout = fopen(outputfile, "w");

    // Check for file opening errors
    if(fin == NULL || fout == NULL)
    {
        printf("Failed to open file\n");
        exit(0);
    }

    // Read file character-by-character
    while((ch = fgetc(fin)) != EOF)
    {
        // Detect start of a possible comment
        if(ch == '/')
        {
            next = fgetc(fin);

            // -------- SINGLE-LINE COMMENT --------
            // If '//' is detected, skip until end of line
            if(next == '/')
            {
                while((ch = fgetc(fin)) != '\n' && ch != EOF);
                fputc('\n', fout);  // Preserve line structure
                continue;
            }

            // -------- MULTI-LINE COMMENT --------
            // If '/*' is detected, skip until '*/'
            else if(next == '*')
            {
                while(1)
                {
                    ch = fgetc(fin);

                    if(ch == EOF)   // End if file ends unexpectedly
                        break;

                    if(ch == '*')
                    {
                        next = fgetc(fin);
                        if(next == '/')
                            break;  // End of multi-line comment
                    }
                }
                continue;   // Skip comment content
            }

            // -------- NOT A COMMENT --------
            // If '/' is normal character, write both characters
            else
            {
                fputc(ch, fout);
                fputc(next, fout);
                continue;
            }
        }

        // -------- NORMAL CHARACTER --------
        // Write normal program characters directly to output
        else
        {
            fputc(ch, fout);
        }
    }

    // Close both files
    fclose(fin);
    fclose(fout);
}
