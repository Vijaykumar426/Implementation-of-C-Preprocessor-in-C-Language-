#include<stdio.h>
#include<stdlib.h>
#include"comment_removal.h"
#include"file_inclusion.h"
#include"macro_handler.h"
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("incorrect input\n");
		printf("provide:./mypreprocessor filename\n");
		exit(0);
	}
	char *input=argv[1];
	remove_comments(input,"temp_file1.txt");
	header_file_inclusion("temp_file1.txt","temp_file2.txt");
	replace_macros("temp_file2.txt","output.c");
	printf("pure c file is created\n");
	return 0;
}

