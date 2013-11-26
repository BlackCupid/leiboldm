#include "Deck.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Deck d;
    d.deal(); d.deal();
    d.reset();
    Card c = d.deal();
    assert (c.get_rank() == Card::TWO);
    c = d.deal();
    assert (c.get_rank() == Card::THREE);
    c = d.deal();
    assert (c.get_rank() == Card::FOUR);
    c = d.deal();
    assert (c.get_rank() == Card::FIVE);
    c = d.deal();
    assert (c.get_rank() == Card::SIX);
    c = d.deal();
    assert (c.get_rank() == Card::SEVEN);
    c = d.deal();
    assert (c.get_rank() == Card::EIGHT);
    c = d.deal();
    assert (c.get_rank() == Card::NINE);
    c = d.deal();
    assert (c.get_rank() == Card::TEN);
    c = d.deal();
    assert (c.get_rank() == Card::JACK);
    c = d.deal();
    assert (c.get_rank() == Card::QUEEN);
    c = d.deal();
    assert (c.get_rank() == Card::KING);
    c = d.deal();
    assert (c.get_rank() == Card::ACE);
    return 0;
}
