#include<stdio.h>
#include<string.h>
#include"board.h"

int main()
{
    struct board_t boardd;
    int player = 0;

    init_board(&boardd);



    init_deck(&boardd.Player[player].deck);
    deck_from_file(&boardd, "ggop.txt", player);
    init_player(&boardd.Player[player]);
    init_manapool(&boardd.Player[player].manapool);


    init_deck(&boardd.Player[player + 1].deck);
    deck_from_file(&boardd, "ggopme.txt", player + 1);
    init_player(&boardd.Player[player +1]);
    init_manapool(&boardd.Player[player + 1].manapool);

    int i;
    for(i = 0; i < 5; i++){
        turn_begin( &boardd.Player[player]);
        turn_begin( &boardd.Player[player + 1]);
    }

    int card;
    int board_num = 0;
    int board_num2 = 0;
    int choice;
    player++;

    do{
  

    if ( bot(&boardd,&board_num2) == 1 ) board_num2++; 

    PrintBoard(boardd);

   


    scanf("%d",&choice);
    if (choice > 0 && choice <= 5 ){
        card = choice - 1;
        if (play_card(&boardd, player, card, board_num) == 1 ) {
                boardd.Card_Positions[board_num][player] = 0;
                board_num++;
		boardd.Player[player].manapool.left -= boardd.Player[player].cards_in_hand[card].magic_cost;
		
		/*struct card_t card_to_use;
		draw_card(&boardd.Player[player].deck, &card_to_use);
		boardd.Player[player].cards_in_hand[card] = card_to_use;*/
		
        }
    }
	
    PrintBoard(boardd);

    turn_end(&boardd, player, &board_num, &board_num2);

    PrintBoard(boardd);
	
    char a; scanf("%s",&a);

    //system("cls");
    printf("\033[2J\033[1;1H");

	if(board_num >= 5) board_num = 0;
	if(board_num2 >= 5) board_num2 = 0;

    }while(boardd.Player[player].health > 0 && boardd.Player[1 - player].health > 0);

    if(boardd.Player[player].health > 0) printf("Ti pechelish ;) \n");
        else printf("Ti gubish\n");

    return 0;
}
