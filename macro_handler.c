// This function replaces macros defined using #define
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"macro_handler.h"
#define MAX_NAMES 50
#define LEN       100
void replace_macros(const char *inputfile, const char *outputfile)
{
	int i;
	char str[300];
	char macros_names[MAX_NAMES][LEN];
	char macros_values[MAX_NAMES][LEN];
	char name[50],value[20];
	int macro_count=0;
	FILE *fin=NULL,*fout=NULL;
	fin=fopen(inputfile,"r");
	fout=fopen(outputfile,"w");
	if(fin==NULL||fout==NULL)
	{
		printf("file is unable to open\n");
		exit(0);
	}
	/* Read and store all macros */
	while(fgets(str,sizeof(str),fin)!=NULL)
	{
		if(strncmp(str,"#define",7)==0)
		{
			sscanf(str,"#define %s %s",name,value);
			strcpy(macros_names[macro_count],name);
			strcpy(macros_values[macro_count],value);
			macro_count++;
		}
	}
	/* Go back to start of file */
	rewind(fin);
	/* Replace macros */
	while(fgets(str,sizeof(str),fin)!=NULL)
	{
		/* ignore macro lines */
		if(strncmp(str,"#define",7)==0)
		{
			continue;
		}
		//replace the macros after the mcaro defined
		for(i=0;i<macro_count;i++)
		{
			char *ptr=strstr(str,macros_names[i]);
			if(ptr!=NULL)
			{
				char temp[300]="";
				int len=ptr-str;
				/* copy text before macro */
				strncat(temp,str,len);
				 /* insert macro value */
				strcat(temp,macros_values[i]);
				/* copy remaining part */
				strcat(temp,ptr+strlen(macros_names[i]));
				strcpy(str,temp);
			}
		}
		//write the final line to output file after replacing the macro
		fputs(str,fout);
	}
	fclose(fin);
	fclose(fout);
}


