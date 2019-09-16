#include <stdio.h>
#include "game_functions.h"
#include <stdbool.h>
#include <stdlib.h>
#include<sys/types.h>
#include <time.h>
int main() {
	time_t t;
	srand((unsigned) time(&t));

	// Set number of bombs to be used
	int _of_bombs = 2;

	
	struct locations *   bombs = (struct locations *) malloc(sizeof(struct locations) * 2);


	// IF GENERATE RANDOM BOMBS DOES NOT WORK THIS CAN SUBSTITUTE
	/*
	bombs[0].x = 1;
	bombs[0].y = 1;
	bombs[0].found =false;
	bombs[1].x = 2;
	bombs[1].y = 3;
	bombs[1].found =false;*/

		int bomb_location_info[4][4] = { 1,1,1,0,
										 1,0,2,1,
										 1,1,2,0,
										 0,0,1,1 };

		int known_location_info[4][4] = { UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
										  UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
										  UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
										  UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN };


		// GENERATE RANDOM BOMBS
			for (int i = 0; i < _of_bombs; i++) {
				bool found = true;
				while (found != false) {
					int a = rand() % DIM;
					int b = rand() % DIM;
					found = false;
					check_found( a,  b, bombs, DIM,  found, _of_bombs);
					if (found = false) {
						bombs[i].x = a;
						bombs[i].y = b;
						bombs[i].found = false;
						
					}
				}
				//printf(	"%d ", bombs[i]);

			}

		int size = 4;

		start_game(bombs, bomb_location_info, size, known_location_info, _of_bombs);
		return 0;

		free(bombs);

}