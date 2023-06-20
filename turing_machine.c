/*
 * TuringMachine.c
 */

#include <stdio.h>
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

enum {
	RUN,
	HALT,
	ACCEPT
};

int main(int argc, char *argv[])
{
  int limit, i, execution_flag;
  char current_state[MAX_LENGTH][LIMIT], new_state[MAX_LENGTH][LIMIT];
  char input_symbol[MAX_LENGTH], write_symbol[MAX_LENGTH], move[MAX_LENGTH];
  char state[LIMIT], file_name[FILENAME_LENGTH];
  FILE *fout, *fin;

  puts("\nTURING MACHINE \n\n");

  if(argc > 1 && !strcmp(argv[1], "-help"))
  {
    printf("Usage\n"
    	"1. %s\n"
    	"2. %s <input file>\n"
    	"3. %s <input file> <input string>\n",
		argv[0], argv[0], argv[0]
	);
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
      scanf("%s%s", current_state[limit], current_state[limit]);
      if(!strcmp(current_state[limit], "$"))
        break;
      scanf(" %c %c %c %s", &input_symbol[limit], &write_symbol[limit], &move[limit], new_state[limit]);
    }
    puts("");
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
  puts("");

  /* Start trasition operations */
  head = 0;
  strcpy(state, current_state[0]);
  while(1)
  {
    execution_flag = HALT;
    for(i = 0 ; i < limit ; i++)
    {
      if(!strcmp(state, current_state[i]) && string[head] == input_symbol[i])
      {
        update_string(write_symbol[i], move[i]);
        strcpy(state, new_state[i]);
        printf("%-10s\t|  state = %s\n", string, new_state[i]);
        if(!strcmp(state, "#"))
          execution_flag = ACCEPT;
        else
          execution_flag = RUN;
        break;
      }
    }
    if(execution_flag == HALT)
    {
      printf("No production found for input symbol \'%c\' at state \'%s\'. Turing Machine halted!\n", string[head], state);
      break;
    }
    else if(execution_flag == ACCEPT)
    {
      puts("Accepted! Turing Machine halted!");
      break;
    }
  }
  puts("");
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
  puts("Enter the Turing Machine input code\n"
  		"Input format:\n"
  		"<current state> <input symbol> <new symbol> <movement> <new state>\n"
  		"A single transition should occupy a single line\n"
  		"input symbol, new symbol and movement are single characters.\n"
  		"current state and new state can be any combination of characters within a limit of 5\n"
  		"First current state will be considered as your initial state\n"
  		"Use \'_\' for blank, \'#\' for halting state\n"
  		"Use \'$\' as current state to stop.\n"
	);
}

