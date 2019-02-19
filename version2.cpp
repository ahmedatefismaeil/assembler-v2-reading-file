// file description: reads file named "first assembly.txt" and removes full comment lines and any beginning blank spaces at the beginning

#include <stdio.h>
#include <stdlib.h>

int read_file(char***);

int main( void )
{
	char ***code_ptr;
	char **code = (char **)calloc(1,sizeof(char*));
	code_ptr = &code;
	int line = read_file(code_ptr);
	int i,j;
	for (i = 0; i <= line; i++)
	{
		for (j = 0;( (code[i][j] != '\n') && (code[i][j] != EOF)); j++)
		{
			putchar(code[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int read_file(char*** code)
{
	// open file
	int c;
	FILE *file;
	file = fopen("first assembly.txt","r");
	
	// make a 2d array
	**code = (char*)calloc(150,sizeof(char));
	char** code_new;
	
	//counters for line and characters and 
	int line = 0 , character = 0;
	
	//flag to show if line has code or not
	char flag = 1;
	
	if(file)//checks if file exists
	{
		while( (c = getc(file)) != EOF )//fetches characters from file  
		{
			if( (c != ' ') || (flag != 1))//ignores spaces at the beginning
			{
				if( (c == ';') && (flag == 1) )//ignores comments
				{
					while ( (c != '\n') && (c != EOF) )//stops at end of line or file
						c = getc(file);//removes comment characters
					character = 0;//reset character counter
					if ( c == EOF )
					{	
						break;//exit reading loop
					}
				}
				else 
				{
					flag = 0;
					*(*(*code+line)+character) = c; // store char in array
					character++;//goto next char
					//putchar(c);
					if(c == '\n')
					{
						line++;//go to next line
						flag = 1;//resets flag of start of line
						character = 0;//resets char counter
						*code = (char **)realloc( *code , ( sizeof(char*) * (line+1)) );//makes a new line
						if (*code)
							*(*code+line) = (char *)calloc(150,sizeof(char));//makes an array in new line
						else
							printf("no memory for extending array");
					}
				}	
			}			
		}
		*(*(*code+line)+character)=EOF;
	}
	else
		printf("problem openning file\n");
return line;	
}
