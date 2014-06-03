#include "manapool.h"

void init_manapool(struct manapool_t *manapool)
{
    manapool->left = INITAL_MANA;
}

void add_mana(struct manapool_t *manapool, int mana)
{

    if(manapool->left < MAX_MANA)
    {
        manapool->left += mana;

    }
}

void remove_mana(struct manapool_t *manapool, int mana)
{

    if(manapool->left >= INITAL_MANA)
    {
        manapool->left -=mana;
    }
}

int can_put_card(struct card_t card_to_put, struct manapool_t pool)
{
    int difference = pool.left - card_to_put.magic_cost;
    if(difference >= 0)
    {
        return 1;
    }
    return 0;
}

