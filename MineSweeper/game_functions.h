#include <stdio.h>
#include <stdbool.h>
#define DIM 4
#define UNKNOWN -1
#define BOMB -2

struct locations {
int x; 
int y; 
bool found;
};


void  get_user_char(int* a);
void display(int known_location_info[][DIM], int size);
void update_known_info(int	row, int	col, int bomb_info[][DIM], int known[][DIM]);
void check_found(int row, int col, struct	locations bombs[], int size, bool* found, int no_of_bombs);
void start_game(struct locations *   bombs, int bomb_location_info[][DIM], int size_of_grid, int players_info[][DIM], int no_of_bombs);
