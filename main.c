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
    deck_from_file(&boardd, "ggop.txt", player + 1);
    init_player(&boardd.Player[player +1]);
    init_manapool(&boardd.Player[player + 1].manapool);

    int i;
    for(i = 0; i < 5; i++){
        turn_begin( &boardd.Player[player]);
        turn_begin( &boardd.Player[player + 1]);
    }

    PrintBoard(boardd);

    do{

    int card;
    int board_num = 0;
    int board_num2 = 0;
    int choice;

    bot(&boardd,&board_num2); //greshkata e tuk

    PrintBoard(boardd);

    player++;


    scanf("%d",&choice);
    if (choice > 0 && choice <= 5 ){
        card = choice - 1;
        if (play_card(&boardd, player, card, board_num) == 1 ) {
                boardd.Card_Positions[board_num][player] = 0;
                board_num++;
        }
    }

    turn_end(&boardd, player, &board_num, &board_num2);
    PrintBoard(boardd);

    }while(boardd.Player[player].health > 0 && boardd.Player[1 - player].health > 0);

    if(boardd.Player[player].health > 0) printf("Pobeditel si ti ;) \n");
        else printf("Pobeditel e bota\n");

    return 0;
}
