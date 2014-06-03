#ifndef _MANAPOOL_H_
#define _MANAPOOL_H_
#include "deck.h"
#define MAX_MANA 10
#define INITAL_MANA 1

struct manapool_t {
    int left;

};

void init_manapool(struct manapool_t *manapool);

void add_mana(struct manapool_t *manapool, int mana);

void remove_mana(struct manapool_t *manapool, int mana);

int can_put_card(struct card_t card_to_put, struct manapool_t pool);

#endif
