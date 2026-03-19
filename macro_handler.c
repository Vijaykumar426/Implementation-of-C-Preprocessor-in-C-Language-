// This function replaces macros defined using #define directives

#include<stdio.h>      // For file handling functions
#include<string.h>     // For string manipulation functions
#include<stdlib.h>     // For exit()
#include"macro_handler.h"  // User-defined header for macro handling

#define MAX_NAMES 50   // Maximum number of macros supported
#define LEN       100  // Maximum length of macro name/value

void replace_macros(const char *inputfile, const char *outputfile)
{
    int i;
    char str[300];   // Buffer to store each line from file

    // Arrays to store macro names and their corresponding values
    char macros_names[MAX_NAMES][LEN];
    char macros_values[MAX_NAMES][LEN];

    char name[50], value[20];  // Temporary variables for macro parsing
    int macro_count = 0;       // Counts total macros found

    FILE *fin = NULL, *fout = NULL;

    // Open input file in read mode and output file in write mode
    fin = fopen(inputfile, "r");
    fout = fopen(outputfile, "w");

    // Check for file opening errors
    if(fin == NULL || fout == NULL)
    {
        printf("File is unable to open\n");
        exit(0);
    }

    /* -------- PASS 1: READ AND STORE MACROS -------- */
    while(fgets(str, sizeof(str), fin) != NULL)
    {
        // Check if line contains macro definition
        if(strncmp(str, "#define", 7) == 0)
        {
            // Extract macro name and value
            sscanf(str, "#define %s %s", name, value);

            // Store macro details in arrays
            strcpy(macros_names[macro_count], name);
            strcpy(macros_values[macro_count], value);
            macro_count++;
        }
    }

    /* Move file pointer back to beginning for second pass */
    rewind(fin);

    /* -------- PASS 2: REPLACE MACROS IN CODE -------- */
    while(fgets(str, sizeof(str), fin) != NULL)
    {
        // Skip macro definition lines
        if(strncmp(str, "#define", 7) == 0)
        {
            continue;
        }

        // Search and replace each stored macro
        for(i = 0; i < macro_count; i++)
        {
            // Find occurrence of macro name in line
            char *ptr = strstr(str, macros_names[i]);

            if(ptr != NULL)
            {
                char temp[300] = "";
                int len = ptr - str;   // Length before macro occurrence

                /* Copy text before macro */
                strncat(temp, str, len);

                /* Insert macro replacement value */
                strcat(temp, macros_values[i]);

                /* Copy remaining text after macro */
                strcat(temp, ptr + strlen(macros_names[i]));

                /* Update original string with modified content */
                strcpy(str, temp);
            }
        }

        // Write processed line to output file
        fputs(str, fout);
    }

    // Close both files
    fclose(fin);
    fclose(fout);
}

