/*
  Joseph Reidell
  Project 5: /dev/pi
  CS 0449
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	
	FILE *f;
	int begin = 0;;
	int end = 0;
	int total = 0;
	char *output;

	/*
	   This checks for the correct amount of arguements 
	   on the command line
	*/
	if(argc != 3){
	  printf("Invalid number of arguments.\n");
	}

	/*
	   If the correct amount of arguements is there,
	   do the calculations and show the output.
	*/
	else{
	
	  /*
	     begin takes in the first integer from the command line
	     end takes in the second integer from the command line
	  */
	  begin = atoi(argv[1]);
	  end = atoi(argv[2]);
	
	  /*
	     If the first integer is larger than the second integer
	     Tell the user and exit the program
	  */
	  if(begin > end){
		printf("End value must be more than the begin value.\n");
		return 1;
	  }

	  /*
	     If either integer is less than 0, tell the user
	     and exit the program.
	  */
	  else if(begin < 0 || end < 0){
		printf("Neither value can be less than 0.\n");
		return 1;
	  }

	  // Find the total length of the output
	  total = end - begin + 1;

	  // Open the kernel device and read from it
	  f = fopen("/dev/pi", "r");

	  /*
	     This checks if the device exists. If it does not
	     tell the user and exit the program.
	  */
	  if(f == NULL){
		printf("/dev/pi does not exist or cannot be found\n");
		return 1;
	  }
	
	  /*
	     It will first set the character array to hold
	     the total length. It will then seek the starting position
	     for the file. Then it will read the data using pi_read from
	     the pi_driver. It will then close after it is read through.
	  */
	  output[total + 1]; 
	  fseek(f, begin, SEEK_SET);
	  fread(output, 1, total, f);
	  fclose(f);

	  // This will set the null terminating value.
	  output[total] = '\0';
	
	  // This will the final value from the integers
	  printf("%s\n", output);

	  return 0;
	}

}
