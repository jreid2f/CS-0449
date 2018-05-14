/* 
   Joseph Reidell
   CS 0449
   Project 1: Rock, Paper, Scissors 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//These are global variables that are used throughout the program
int num_round = 1;
int user = 0;
int com = 0;
char object[10];
char loop[4];

/*
    This method asks for the users choice and randomizes the number the computer uses
    It will then checks who won the round and then figure out the score 
    It will display the current score after someone wins a round
    After the score is decided, it will add on to the number of rounds
*/
int rps_decision(){
    
    printf("\nWhat is your choice? ");
	      scanf("%s", object);
	      int com_pick = rand() % 3 +1;
    
    if(com_pick == 1 && strcmp(object, "paper") == 0){
        printf("The computer chooses rock. You win this one!\n");
        user++;
        printf("\nThe score is now you: %d", user);
        printf(" computer: %d\n", com);
        num_round++;
    }
    
    else if(com_pick == 1 && strcmp(object, "rock") == 0){
        printf("The computer chooses rock. It's a draw. Try again!\n");
    }
    
    else if(com_pick == 1 && strcmp(object, "scissors") == 0){
		printf("The computer chooses rock. You lose this game!\n");
		com++;
		printf("\nThe score is now you: %d", user);
		printf(" computer: %d\n", com);
		num_round++;
    }
    
    else if(com_pick == 2 && strcmp(object, "rock") == 0){
        printf("The computer chooses paper. You lose this game!\n");
        com++;
        printf("\nThe score is now you: %d", user);
        printf(" computer: %d\n", com);
        num_round++;
    }
    
    else if(com_pick == 2 && strcmp(object, "paper") == 0){
        printf("The computer chooses paper. It's a draw. Try Again!\n");
    }
    
    else if(com_pick == 2 && strcmp(object, "scissors") == 0){
        printf("The computer chooses paper. You win this one!\n");
        user++;
        printf("\nThe score is now you: %d", user);
        printf(" computer: %d\n", com);
        num_round++;
    }
    
    else if(com_pick == 3 && strcmp(object, "rock") == 0){
        printf("The computer chooses scissors. You win this one!\n");
        user++;		
        printf("\nThe score is now you: %d", user);
        printf(" computer: %d\n", com);
        num_round++;
    }
    
    else if(com_pick == 3 && strcmp(object, "scissors") == 0){
        printf("The computer chooses scissors. It's a draw. Try Again!\n");
    }
    
    else if(com_pick == 3 && strcmp(object, "paper") == 0){
        printf("The computer chooses scissors. You lose this game!\n");
        com++;
        printf("\nThe score is now you: %d", user);
        printf(" computer: %d\n", com);
        num_round++;
    }

    else{
        printf("\nPlease either enter in \"rock\", \"paper\", or \"scissors\" \n");
    }
    
    return 0;
}

/*
    This will check if the the user or computer has won 3 rounds
    It will display whether you have won the game or you lost the game
    A prompt will come up to ask if you want to play again
    If you do, it will reset the game and continue 
*/
int reset(){
    if(user == 3 || com == 3){
        if(user > com){
            printf("You win!\n");
        }
        else if(com > user){
	    printf("You lose!\n");
        }
        
        printf("Would you like to play again? ");
        scanf("%s", loop);
        
        if(strcmp(loop, "yes") == 0 || strcmp(loop, "Yes") == 0){
	   user = 0;
	   com = 0;
	   num_round = 1;
        }
    }
    
    return 0;
}

int main(){
	    
    	srand((unsigned int)time(NULL));
	
	printf("\nWelcome to Rock, Paper, Scissors \n");

	printf("\nWould you like to play? ");
	scanf("%s", loop);

	if(strcmp(loop, "yes") == 0 || strcmp(loop, "Yes") == 0){
    
            do{
            	rps_decision();
            	reset();    
        
    	    }while(!strcmp(loop, "yes") || !strcmp(loop, "Yes") && num_round <= 5);

	}

        printf("\nBye!\n");
  
  	return 0;
}
