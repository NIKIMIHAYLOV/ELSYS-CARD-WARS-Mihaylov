#include "board.h"
#include <string.h>
#include <stdio.h>

void PrintBoard(struct board_t board) {

	printf("\n\n\n\n\nPLAYER:BOT (%d),MANA %d",board.Player[0].health,board.Player[0].manapool.left );
	printf("\n____________________________________\n|");
	int i;

	for (i = 0; i < 5; i++) {
		if( board.Player[0].spots_hand[i] == -1 ) printf("      |");
		else print_card_h(board.Player[0].cards_in_hand[i]);
	}

	printf("\n####################################\n#");

	for (i = 0; i < 5; i++) {
		if (board.Card_Positions[i][0] == -1) printf("      #");
		else print_card_b(board.Cards_on_Board[i][0]);
	}

	printf("\n#");
	for (i = 0; i < 5; i++) {
		if (board.Card_Positions[i][1] == -1) printf("      #");
		else print_card_b(board.Cards_on_Board[i][1]);
	}
	printf("\n####################################\n|");
	for (i = 0; i < 5; i++) {
		if( board.Player[1].spots_hand[i] == -1 ) printf("      |");
		else print_card_h(board.Player[1].cards_in_hand[i]);
	}
	printf("\n____________________________________\n");
	printf("PLAYER:ZERO (%d),MANA %d\n",board.Player[1].health, board.Player[1].manapool.left);

}




int deck_from_file(struct board_t *boardd, char *file_name, int player ){

    FILE *fp;
    int i ;
    char buffer[255];
    char *nam;
    fp = fopen(file_name,"r");

    if ( fp == NULL ) return 0;

    while(fgets(buffer, 1800, fp)){


        nam = strtok(buffer, ",");
        sscanf(nam,"%s", boardd -> Player[player].deck.cards[boardd -> Player[player].deck.top].name );


        nam = strtok(NULL, ",");
        sscanf(nam,"%d", &boardd -> Player[player].deck.cards[boardd -> Player[player].deck.top].life );


        nam = strtok(NULL, ",");
        sscanf(nam,"%d", &boardd -> Player[player].deck.cards[boardd -> Player[player].deck.top].power );

        nam = strtok(NULL, ",");
        sscanf(nam,"%d", &boardd -> Player[player].deck.cards[boardd -> Player[player].deck.top].magic_cost );

        boardd -> Player[player].deck.top++;


    }



    fclose(fp);

    return 1;
}



int init_board(struct board_t *board)
{
	int i;
	for (i = 0; i < 5; i++) {
		board -> Card_Positions[i][0] = -1;
		board -> Card_Positions[i][1] = -1;
        board -> Player[0].spots_hand[i] = -1;
        board -> Player[1].spots_hand[i] = -1;
	}

	return 1;
}

int can_play_card(struct board_t board, int player, int card, int num_lane) {

	if(board.Card_Positions[num_lane][player] == -1) {
		if (can_put_card( board.Player[player].cards_in_hand[card], board.Player[player].manapool) == 1 ) {
			return 1;
		} else {
			return 2;
		}
	}
	return 0;

}

int play_card(struct board_t *board, int player, int card, int num_lane){
	int result = can_play_card(*board, player, card, num_lane);
	if (result == 1) {

		struct card_t card_to_board = board->Player[player].cards_in_hand[card];
		board -> Card_Positions[num_lane][player] = 0;
		board -> Cards_on_Board[num_lane][player] = card_to_board;
		//board -> Player[player].spots_hand[card] = -1;
	}
	return result;

}
void turn_end(struct board_t *board, int player, int *board_num, int *board_num2) {
	int i;
	int other_pl = 1 - player;
	for (i = 0; i < 5; i++) {
		if (board -> Card_Positions[i][player] != -1)
        {

			if (board -> Card_Positions[i][other_pl] != -1)
			{
				int winner = attack( &board -> Cards_on_Board[i][player] , &board -> Cards_on_Board[i][other_pl]);
				switch (winner) {
					case 1: board -> Card_Positions[i][other_pl] = -1;
                                               // *board_num2--;
                                                break;

					case 2: board -> Card_Positions[i][player] = -1;
                                               // *board_num--;
                                                break;

                                        case 0: board -> Card_Positions[i][other_pl] = -1;
                                                board -> Card_Positions[i][player] = -1;
                                               // *board_num--;
                                               // *board_num2--;
                                                break;

					default: break;
				}
			} else {
			    int damage = board -> Cards_on_Board[i][player].power * (-1);
				change_hp(&board -> Player[other_pl], damage );
			}
        }else if(board -> Card_Positions[i][other_pl] != -1)
                {
                    int damage = (board -> Cards_on_Board[i][other_pl].power) * (-1);
                    change_hp(&board -> Player[player], damage );
                }
	}
	board -> Player[player].manapool.left++;
	board -> Player[other_pl].manapool.left++;
}

int bot(struct board_t *boardd , int *board_num2){
    int loop;
    struct card_t minimum;
    int card;
    int player = 0;
    for(loop = 0;loop < 5; loop++){
        if (loop  == 0){
        minimum.power = boardd -> Player[0].cards_in_hand[loop].power;
        minimum.life = boardd -> Player[0].cards_in_hand[loop].life;
        minimum.magic_cost = boardd -> Player[0].cards_in_hand[loop].magic_cost;
        card = loop;
        }

        if (boardd -> Player[0].cards_in_hand[loop].magic_cost < minimum.magic_cost){
        minimum.power = boardd -> Player[0].cards_in_hand[loop].power;
        minimum.life = boardd -> Player[0].cards_in_hand[loop].life;
        minimum.magic_cost = boardd -> Player[0].cards_in_hand[loop].magic_cost;
        card = loop;
        }

    }
    int result = play_card( boardd, player, card, *board_num2);
    if (result == 1 ) {
            boardd -> Card_Positions[*board_num2][player] = 0;
            board_num2++;
	    boardd -> Player[0].manapool.left -= minimum.magic_cost ;

	    /*struct card_t card_to_use;
	    draw_card(&boardd ->Player[0].deck, &card_to_use);
	    boardd ->Player[0].cards_in_hand[card] = card_to_use;*/

    }

	return result;

}
