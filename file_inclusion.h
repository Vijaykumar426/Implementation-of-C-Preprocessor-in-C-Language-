// Function to process header file inclusion directives
// Parameters:
// 1) const char *input_file  -> Source file containing #include directives
// 2) const char *output_file -> File where expanded content is written
// Description:
// This function reads a C source file, detects user-defined header files,
// inserts their contents into the main file, and produces an expanded output file.
void header_file_inclusion(const char *input_file, const char *output_file);
