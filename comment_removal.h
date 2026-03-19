// Function to remove comments from a C source file
// Parameters:
// 1) const char *input_file  -> Name of the source file containing comments
// 2) const char *output_file -> Name of the file where comment-free code is written
// Description:
// This function reads a C source file, removes single-line (//) and
// multi-line (/* */) comments, and generates a clean output file.
void remove_comments(const char *input_file, const char *output_file);
