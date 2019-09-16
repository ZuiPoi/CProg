#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game_functions.h"

void display(int known_location_info[][DIM], int size) {
	int str[4] = { "a","b","c","d" };
	int f = 0;
	int g = 0;
	printf(" abcd \n");
	for (f = 0; f < size; f++) {
		g = 0;
		printf(str[f]);

		for (g = 0; g < size; g++) {
			

			if (g < size) {
				if (known_location_info[g][f] == UNKNOWN) {
					printf("*");
				}
				else {
					printf("%d", known_location_info[g][f]);
				}
			}
		}
		printf("\n");

	}
}
void update_known_info(int	row, int col, int bomb_info[][DIM], int known[][DIM]) {
	col = col - 1;
	row = row - 1;
	known[row][col] = bomb_info[row][col];
}
void check_found(int row, int col, struct	locations bombs[], int size, bool* found, int no_of_bombs) {

	for (int i = 0; i < no_of_bombs; i++) {
		if (bombs[i].x == row) {
			if (bombs[i].y == col) {
				bombs[i].found = true;
				*found = true;
			}
		}
	}
	
}
void  get_user_char(int* a ) {
	scanf("%d", a);

}


void start_game(struct locations *   bombs, int bomb_location_info[][DIM], int size_of_grid, int players_info[][DIM], int no_of_bombs)
{
	enum game_status { STILL_ALIVE, GAME_OVER };
	enum game_status status = STILL_ALIVE;
	int guesses = 5;
	
	printf("Would you like 2 randomly assigned clues (these will use 2 guesses!) ? \n 1=Yes \n 2= No \n:");
	int choice = 0;
	get_user_char(&choice);

	// ensures value is within correct range
	while (choice < 1 || choice>2) {
		printf("only 1 and 2 are valid choices! \n");
		printf("please Enter 1 or 2:");
		get_user_char(&choice);
	}
	//if player does want hints
	if (choice == 1) {
		guesses = 3;
		for (int i = 0; i < 2; i++) {
			int a = 0;
			int b = 0;
			// make sure no bomb at the selected location
			bool found = true;
			while (found != false) {
				 a = rand() %DIM+1;
				 b = rand() %DIM+1;
				 printf("%d %d", a, b);
				found = false;
				check_found(a, b, bombs, size_of_grid, &found, no_of_bombs);
				// add the clue 
				if (found == false) {
					update_known_info(a, b, bomb_location_info, players_info);
					break;
				}
			}
		}
	}
	//display the hints
	display(players_info, size_of_grid);

	// player makes guesses
	for (int i = guesses; i > 0; i--) {
		printf(" Number of Guesses = %d \n", i);
		if (status == STILL_ALIVE) {

			int chosenX = 0;
			int chosenY = 0;
			printf("Enter  X coordinate:");
			get_user_char(&chosenX);
			// ensure x is within correct range
			while (chosenX < 1 || chosenX>4) {
				printf("only value from 1 to 4 are valid choices! \n");
				printf("please Enter value from 1 to 4 :");
				get_user_char(&chosenX);
			}
			printf("Enter  Y coordinate:");
			get_user_char(&chosenY);
			// ensure Y is within range
			while (chosenY < 1 || chosenY>4) {
				printf("only value from 1 to 4 are valid choices! \n");
				printf("please Enter value from 1 to 4 :");
				get_user_char(&chosenY);
			}

			bool found = false;
			check_found(chosenX, chosenY, bombs, size_of_grid, &found, no_of_bombs);
			//if a bomb was found
			if (found == true) {
				printf(" You hit a bomb! Game over!");
				status = GAME_OVER;
				break;
			}
			//otherwise update the grid
			else {
				update_known_info(chosenX, chosenY, bomb_location_info, players_info);
				display(players_info, size_of_grid);
			}


		}
	}
	//Check if we are alive
	if (status == STILL_ALIVE) {
		printf(" You got the clues! Now time to identify the bomb locations! \n");
		int n = no_of_bombs;
		while (n >= 0) {
			printf(" Number of bombs left = %d \n", n);

			if (status == STILL_ALIVE) {
				// if player has found all bombs
				if (n == 0) {
					printf("You Won, congratulations!");
					break;
				}
				int chosenX = 0;
				int chosenY = 0;
				printf("Enter  X coordinate:");
				get_user_char(&chosenX);
				printf("Enter  Y coordinate:");
				get_user_char(&chosenY);

				bool found = false;
				check_found(chosenX, chosenY, bombs, size_of_grid, &found, no_of_bombs);
				//if they find a bomb
				if (found == true) {
					players_info[chosenX-1][chosenY-1] = 99;
					display(players_info, size_of_grid);
					n = n - 1;
				}
				// if player misses a bomb
				else {
					printf(" You missed a bomb! Game over!");
					status = GAME_OVER;
					break;
				}

			}

		}

	}
}


