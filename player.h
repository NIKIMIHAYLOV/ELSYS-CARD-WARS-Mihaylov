#ifndef PLAYER_H
#define PLAYER_H
#include "manapool.h"
#define MAX_HEALTH 100
struct player_t {
    char pl_name;
	int health;
	struct deck_t deck;
	struct manapool_t manapool;
	struct card_t cards_in_hand[5];
	int spots_hand[5];
};
void init_player(struct player_t *player);
void change_hp(struct player_t *player,int change);
void turn_begin(struct player_t *player);

#endif
