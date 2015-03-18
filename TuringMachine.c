/*
 * TuringMachine.c
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1000  
#define STR_LENGTH 100
#define LIMIT 5
#define FILENAME_LENGTH 20

void print_head();
void print_message();
void print_line();
void update_string(char, char);

char string[STR_LENGTH];
int head, string_length;

int main(int argc, char *argv[])
{
	int limit, i, flag;
	char current_state[MAX_LENGTH][LIMIT], new_state[MAX_LENGTH][LIMIT];
	char input_symbol[MAX_LENGTH], write_symbol[MAX_LENGTH], move[MAX_LENGTH];
	char state[LIMIT], file_name[FILENAME_LENGTH];
	FILE *fout, *fin;	
	
	printf("\nTURING MACHINE \n\n");
	
	if(argc > 1 && !strcmp(argv[1], "-help"))
	{
		printf("Usage\n");
		printf("1. turingmachine\n");
		printf("2. turingmachine <input file>\n"); 
		printf("3. turingmachine <input file> <input string>\n\n");
		exit(0);
	}
	
	/* Reading data from user */
	
	if(argc > 1) /* Checks if file input as commandline argument is present */
	{
		fin = fopen(argv[1], "r");
		if(fin == NULL)
		{
			printf("File not found: \'%s\'\n", argv[1]);
			exit(0);
		}
		for(limit = 0 ; limit < MAX_LENGTH ; limit++)
		{
			fscanf(fin, "%s", current_state[limit]);
			if(!strcmp(current_state[limit], "$"))
				break;
			fscanf(fin, " %c %c %c %s\n", &input_symbol[limit], &write_symbol[limit], &move[limit], new_state[limit]);
		}
	}
	else
	{	
		print_message();
		for(limit = 0 ; limit < MAX_LENGTH ; limit++)
		{
			__fpurge(stdin);
			scanf("%s", current_state[limit]);
			if(!strcmp(current_state[limit], "$"))
				break;
			scanf(" %c %c %c %s", &input_symbol[limit], &write_symbol[limit], &move[limit], new_state[limit]);
		}
		printf("\n");
	}
	
	if(argc > 2) /* Checks if string input as commandline argument is present */
	{
		strcpy(string, argv[2]);
	}
	else
	{
		printf("Enter input string : "); 
		scanf("%s", string);
	}
	string_length = strlen(string);
	printf("\n");
	
	/* Start program execution */
	if(argc > 1)
	{
		strcpy(file_name, argv[1]);
		file_name[strlen(file_name)] = '\0';
		strcat(file_name, "-output");
	}
	else
		strcpy(file_name, "output");
		
	fout = fopen(file_name, "w");
	
	/* Write initial data and transitions to file */
	fprintf(fout, "TURING MACHINE \n\n");
	fprintf(fout, "Transition functions:-\n\n");
	for(i = 0 ; i < limit ; i++)
		fprintf(fout, "(%s, %c, %c) = (%c, %s)\n", current_state[i], input_symbol[i], write_symbol[i], move[i], new_state[i]);
	fprintf(fout, "\nTuring machine operation:-\n\n");
	
	/* Start trasition operations */
	head = 0;
	strcpy(state, current_state[0]);
	while(1)
	{
		flag = 0;
		for(i = 0 ; i < limit ; i++)
		{
			if(!strcmp(state, current_state[i]) && string[head] == input_symbol[i])
			{
				update_string(write_symbol[i], move[i]);
				strcpy(state, new_state[i]);
				printf("%-10s\t|  state = %s\n", string, new_state[i]);
				fprintf(fout, "%s\t|  state = %s\n", string, new_state[i]);
				if(!strcmp(state, "#"))
					flag = 2;
				else
					flag = 1;
				break;
			}
		}
		if(flag == 0)
		{
			printf("No production found for input symbol \'%c\' at state \'%s\'. Turing Machine halted!\n", string[head], state);
			fprintf(fout, "\nNo production found for input symbol \'%c\' at state \'%s\'. Turing Machine halted!\n", string[head], state);
			break;
		}
		else if(flag == 2)
		{
			printf("Accepted! Turing Machine halted!\n");
			fprintf(fout, "\nAccepted! Turing Machine halted!\n");
			break;
		}
	}
	fclose(fout);
	printf("\n");
	printf("Output is stored as \'%s\' in the folder\n", file_name);
	return 0;
}

void update_string(char symbol, char move)
{
	int i;	
	string[head] = symbol;
	if(move == 'r')
		head++;
	else if(move == 'l')
		head--;
	if(head == -1)
	{
		for(i = string_length ; i > 0 ; i--)
			string[i] = string[i - 1];
		string[0] = '_';
		string_length++;
		string[string_length] = '\0';
		head = 0;
	}
	else if(head == string_length)
	{
		string[string_length] = '_';
		string_length++;
		string[string_length] = '\0';
	} 
}

void print_message()
{
	printf("Enter the Turing Machine input code\n");
	printf("Input format:\n");
	printf("<current state> <input symbol> <new symbol> <movement> <new state>\n");
	printf("A single transition should occupy a single line\n");
	printf("input symbol, new symbol and movement are single characters.\n");
	printf("current state and new state can be any combination of characters within a limit of 5\n");
	printf("First current state will be considered as your initial state\n");
	printf("Use \'_\' for blank, \'#\' for halting state\n");
	printf("Use \'$\' as current state to stop.\n\n");
}

