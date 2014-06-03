#ifndef BOARD_H
#define BOARD_H
#include "player.h"
#define PLAYERS 2

struct board_t {
	struct player_t Player[PLAYERS];
	struct card_t   Cards_on_Board[5][2];

	int Card_Positions[5][2];
};

int bot(struct board_t *board, int *boart_num2);

int init_board(struct board_t *board);

int can_play_card(struct board_t *board, int first_pl, int card, int num_lane);

int play_card(struct board_t *board, int first_pl, int card, int num_lane);

void turn_end(struct board_t *board, int first_pl, int *board_num, int *board_num2);

int deck_from_file(struct board_t *boardd, char *file_name, int player );

#endif
