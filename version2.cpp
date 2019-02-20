// file description: reads file named "first assembly.txt" and removes full comment lines and any beginning blank spaces at the beginning
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree_node
{
	char label[30];// name of label
	int line;// number of instruction
	struct tree_node* next_ptr;// pointer to next node
};
typedef struct tree_node treeNode;
typedef struct tree_node* treeNodePtr;

int read_file(char***);//reads assembly file
void locate_labels(treeNodePtr*,int,char**); // makes a tree of labels
void insert_node(treeNodePtr*,int,char [30]);
//void print_labels(treeNodePtr);
//was used to check that labels are collected
void dectobin(int);//uncompleted function************************

int main( void )
{
	char ***code_ptr;// pointer to 2d array
	char **code = (char **)calloc(1,sizeof(char*));// allocate 2d array of size 1
	code_ptr = &code;// store array address in code_ptr 
	int line = read_file(code_ptr);// read assembly file, return the number of lines
	int i,j;//used as counters
	
	treeNodePtr root_node = NULL;// forms a root node initialized to null
	locate_labels(&root_node,line,code);// forms tree of labels
	
	//print_labels(root_node);
	
/*	for (i = 0; i <= line; i++)
	{
		for (j = 0; (code[i][j] != '\n') ; j++)
		{
			putchar(code[i][j]);
		}
		printf("\n");
	}*/
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
		*(*(*code+line)+character)='\n';
		fclose(file);
	}
	else
		printf("problem openning file\n");
return line;	
}

void locate_labels(treeNodePtr* tree_ptr,int line,char** code)//forms a tree of labels
{
	int i,j;//counters
	char* label;//pointer to : if existed
	char name[30];//label name
	for(i = 0; i<=line; i++)// loops on all lines
	{
		label = strchr(*(code+i),':');//sees if there is label or not
		if (label)
		{
			for(j = 0; ((code[i][j] != ' ') && (code[i][j] != ':'));j++)
			{	
				name[j] = code[i][j];//copys label name
			}
			name[j] = 0;// add null terminator
			insert_node(tree_ptr,i,name);//makes a new node to enter label
		}
	}
}

void insert_node(treeNodePtr* treePtr,int line,char label[30])//makes a new node
{
	int i;
	if(*treePtr)//if root exists
	{
		insert_node(&( (*treePtr)-> next_ptr),line,label);//goes to next node
	}
	else
	{
		*treePtr = (treeNodePtr)malloc( sizeof( treeNode ) );//makes a root node
		if ( *treePtr ) //checks if there is memory
		{
			for( i = 0; i < 30 ; i++)
				( *treePtr )->label[i] = label[i];//copy label name to node
			( *treePtr )->line = line;// copy label line to node
			( *treePtr )->next_ptr = NULL;// set the node to leaf
		} 
		else 
		{
			printf( "%d not inserted. No memory available.\n", line );
		}
	}
}

/*void print_labels(treeNodePtr treePtr)
{
	if(treePtr)
	{
		printf("%s   %d",treePtr->label,treePtr->line);
		print_labels(treePtr->next_ptr);
	}
}*/

void dectobin(int value)// 26 bits for j instructions unsigned only
{
	unsigned c;
	unsigned displayMask = 1 << 25;
	for ( c = 1; c <= 26; c++ )
	{
		putchar( value & displayMask ? '1' : '0' );
		value <<=1;
	}
}
