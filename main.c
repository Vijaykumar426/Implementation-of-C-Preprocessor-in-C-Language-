#include<stdio.h>          // Standard input-output functions
#include<stdlib.h>         // Standard library functions (exit, memory allocation etc.)

// User-defined header files for preprocessor modules
#include"comment_removal.h"   // Contains functions to remove comments from source file
#include"file_inclusion.h"    // Contains functions to handle header file inclusion
#include"macro_handler.h"     // Contains functions to process macro replacement

int main(int argc,char *argv[])
{
    // Check if correct number of command-line arguments are provided
    if(argc!=2)
    {
        printf("Incorrect input\n");
        printf("Usage: ./mypreprocessor <filename>\n");
        exit(0);   // Terminate program if input is invalid
    }

    // Store input file name provided by user
    char *input = argv[1];

    // Step 1: Remove comments from the input file
    // Output is stored in temporary file temp_file1.txt
    remove_comments(input, "temp_file1.txt");

    // Step 2: Process header file inclusion directives
    // Reads temp_file1.txt and writes updated content into temp_file2.txt
    header_file_inclusion("temp_file1.txt", "temp_file2.txt");

    // Step 3: Replace macros with their defined values
    // Final processed C file is generated as output.c
    replace_macros("temp_file2.txt", "output.c");

    // Indicate successful preprocessing
    printf("Pure C file is created successfully\n");

    return 0;   // Successful program termination
}

