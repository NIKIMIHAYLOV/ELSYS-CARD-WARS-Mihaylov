#include <stdio.h>
#include "card.h"
int attack( struct card_t *attacker, struct card_t *defender ){

    attacker->life = attacker->life - defender->power;

    defender->life = defender->life - attacker->power;

    if (attacker->life <= 0 && defender->life <= 0) return 0;

    if (attacker->life > 0 && defender->life > 0) return 3;

    if (attacker->life <= 0 && defender->life > 0) return 2;

    if (attacker->life > 0 && defender->life <= 0) return 1;
}

void print_card_b(struct card_t card){
    printf("%d/%d", card.power , card.life);

}

void print_card_h(struct card_t card){
    printf("%d/%d(%d) ", card.power , card.life, card.magic_cost);
}

