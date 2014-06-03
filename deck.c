#include "deck.h"

void init_deck (struct deck_t *deck)
{
        deck->top = 0;
}

int push_card(struct card_t card, struct deck_t *deck)
{
    if(deck->top >= MAX_CARD_IN_DECK)
    {
        return -1;
    }

    deck->cards[deck->top++] = card;
    return 0;
}

int draw_card(struct deck_t *deck, struct card_t *card)
{
    if(deck->top <= 0)
    {
        return -1;
    }

    *card = deck->cards[--deck->top];
    return 0;
}

int look_card (struct deck_t *deck, struct card_t *card)
{
    if(deck->top <=0)
    {
        return -1;
    }

    *card = deck->cards[deck->top];
    return 0;
}
