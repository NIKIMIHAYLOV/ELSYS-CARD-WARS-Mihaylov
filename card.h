#ifndef _CARD_
#define _CARD_

struct card_t {
    char name[20];
    int life;
    int power;
    int magic_cost;
};

int attack(struct card_t *attacker,struct card_t *defender);

void print_card_b(struct card_t card);
void print_card_h(struct card_t card);

#endif
