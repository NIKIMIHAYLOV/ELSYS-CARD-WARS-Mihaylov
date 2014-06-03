#include "player.h"

void init_player(struct player_t *player){
    player ->health = 30;
}

void turn_begin(struct player_t *player) {
	struct card_t card_to_use;
    int i;
	for (i = 0; i < 5; i++) {
		if (player -> spots_hand[i] == -1) {
			draw_card(&player -> deck, &card_to_use);
			player -> cards_in_hand[i] = card_to_use;
			player -> spots_hand[i] = 0;
			break;
		}
	}


}

void change_hp(struct player_t *player,int change) {
	player -> health += change;
	if (player -> health > MAX_HEALTH) player -> health = MAX_HEALTH;
}

