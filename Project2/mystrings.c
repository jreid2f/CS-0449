/* 
    Joseph Reidell
    CS 0449
    Project 2: mystrings
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    The main method takes in a file argument from the command line
    It is made to take arbitraily long strings and display them, 
    if possible, from any file that is entered into the command line    
*/

int main(int argc, char *argv[])
{
	
	FILE *f; // File variable
	unsigned char character; // unsigned char variable used to read from file
	
	// char pointer variable used to help collect string characters
	char *str = malloc(100); 

	/*
           This checks if a file argument is entered in at the command line
           If one is not entered in, it prints out a message and terminates
	*/
	if(argc != 2)
	{
           printf("A command line argument is needed to run the program!\n");
	   return 0;
	}

	f = fopen(argv[1], "rb");

    	/* 
           This checks if the file that is entered in actually exists 
           If it does not exist, it prints a message and terminates the program
    	*/
	if(f == NULL)
	{
	   printf("The file does not exist!\n");
	   return 0;
	}

    	/*
           This loop goes through the file stream that is opened up and 
           checks if the last character is at the end of the file.
           The characters are checked as "unsigned char"
    	*/
	while(fgetc(f) != EOF)
	{
	   fseek(f, -1, SEEK_CUR);
	   character = fgetc(f);

          /*
             The if/else if statement checks whether if the unsigned char 
             character is an ASCII character between a 32 and 126 decimal
             or if the string does not have a non printable character 
          */
	  if(character > 32 && character < 126)
	  {
	    if(*str == '\0')
            {
                *str = character;
            }
            else
            {
                strncat(str, &character, 1);
            }    	
	  }

	  else if(*str != '\0')
	  {
            /*
                If the string contains 4 printable characters then it will 
                print out the string that is found. 
            */
            if(strlen(str) >= 4)
            {
                printf("%s\n", str);
            }

            /* 
                This copies 0 unsigned character from the first 100 characters
                from the string that is pointed to from the char pointer
                argument str
            */
            memset(str, 0, 100);
          }	
        } 	

	// Close File
	fclose(f);

	// Free's the malloc in str
	free(str);

	return 0;
	
}

