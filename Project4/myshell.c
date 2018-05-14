/*
  Joseph Reidell
  Project 4: A Shell
  CS 0449
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Global variables that are used throughout the program:
  'internal_shell' represents the first of two command categories
  'delimiters' represents the delimiter set
  'executable_programs' represents the second of two command categories 
*/
char* internal_shell[500];
char* delimiters = " \t\n()<>|&;";
int executable_programs = 0;

/*
  This method checks if the directory does not exist
  If the directory does not exist, notify the user
  If the directory does exist, change to that directory 
*/
void change_directory(){
	char* directory = internal_shell[1];
	int valid;	

	if(directory == NULL){
	   printf("-bash: No such file or directory exists\n");
	}

	else{
	   valid = chdir(directory);

	   if(valid == -1){
		printf("-bash: No such file or directory exists\n");
	   }
	}
}

/*
  This is a simple method that checks if the command can be used
  It uses execvp to check for a valid command and replicate it.
*/
int check_command(){
	int execute = execvp(internal_shell[0], internal_shell);

	if(execute == -1){
	   printf("-bash: command not found\n");
	   exit(1);
	}
}

/*
  This method is used for using a redirect, append, or write command. 
  It looks for which command is entered in using the delimiter variable. 
  After that it will try to open a file. If it does not, notify the user.
  It will move into the method 'check_command' above to check and execute 
  the command. 
*/
int move_output(char* argue){
	FILE* f = NULL;
	char* append = strstr(argue, ">>");
	char* redirect = strstr(argue, ">");
	char* write = strstr(argue, "<");

	// This if statement checks if the append operator is used
	if(append != NULL){
	   char* next = strtok(append, delimiters);
	   f = freopen(next, "a", stdout);

	   if(f == NULL){
		printf("-bash: No such file exists\n");
		exit(1);
	   }

	   internal_shell[executable_programs-- - 1] = NULL;	 
	}

	// This else if statement checks if the redirect operator is used
	else if(redirect != NULL){
	   char* next = strtok(redirect, delimiters);
	   f = freopen(next, "r", stdin);

	   if(f == NULL){
		printf("-bash: No such file exists\n");
	   }

	   internal_shell[executable_programs - 1] = NULL;
	}

	// This else if statement checks if the write operator is used
	else if(write != NULL){
	   char* next = strtok(write, delimiters);
	   f = freopen(next, "w", stdout);

	   if(f == NULL){
		printf("-bash: No such file exists\n");
		exit(1);
	   }

	   internal_shell[executable_programs-- - 1] = NULL;
	}

	// execvp used in this method
	check_command();
}

/*
  This method uses the method 'fork' to look for a command and run it.
  While nothing is entered in, the shell will wait until a command is 
  entered in. Basic linux commands are ran using the fork method. Using 
  arguement movement like 'append', 'redirect', or 'write' are used in 
  'move_output' above.
*/
int shell_arguments(char* output){
	int status = 0;
	int child_process = fork();

	if(child_process != 0){
	   wait(&status);
	}

	else{
	   move_output(output);
	   exit(0);
	}
	return 0;
}

/*
  This method will tokenize the input by using the library function
  'strtok'. 
*/
void tokenize(char* input){
	char* token = strtok(input, delimiters);

	internal_shell[executable_programs++] = token;

	while(token != NULL){
	   token = strtok(NULL, delimiters);
	   internal_shell[executable_programs++] = token;
	}

	executable_programs--;
}

/*
  This method is the inner workings of the shell. This will check if 
  an arguement is valid. If the arguement is valid, it will look at the 
  length of the arguement then tokenize the input used. Once the input is 
  tokenized, it wiil check whether 'exit', 'cd', or a different unix 
  command was entered. 
*/
void inner_shell(){
	char arguments[500];
	int arg_length;

	while(1){
	   printf("myshell $ ");

	   fgets(arguments, sizeof(arguments), stdin);

	   if(arguments == NULL || strlen(arguments) == 1){
		printf("");
		continue;
	   }
	   arg_length = strlen(arguments);
	   arguments[arg_length - 1] = 0;

	   char token_copy[strlen(arguments)];
	
	   strcpy(token_copy, arguments);
	   tokenize(token_copy);
	
	   if(!strcmp(internal_shell[0], "exit")){
		exit(0);
	   }

	   else if(!strcmp(internal_shell[0], "cd")){
		change_directory();
	    }

	   else{
		shell_arguments(arguments);
	   }
	   
	   // Reset number of executed programs
	   executable_programs = 0;
	}
}

/* 
  This method runs the shell itself. It uses an improper exit at the end
  just in case something tends to go of course.
*/
void shell(){
	inner_shell();
	exit(1);
}

// Main method that runs the shell program
int main(){
	shell();
	return 0;	
}
