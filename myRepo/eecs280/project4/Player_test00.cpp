#include <iostream>
#include <cassert>
#include "Player.h"

using namespace std;
int main() {
   const int MINIMUM = 5;
   int bankroll = 20;
   Player * p =  player_factory("counting");
   //count is 0
   assert(p->bet(bankroll, MINIMUM) == MINIMUM);
   Card low = Card(Card::TWO, Card::SPADES);
   Card high = Card(Card::JACK, Card::SPADES);
   for (int i = 0; i < 1000; i++)
   {
       p->expose(high);
       assert(p->bet(bankroll, MINIMUM) == MINIMUM);
   }
   for (int i = 0; i < 1001; i++)
   {
       p->expose(low);
       assert(p->bet(bankroll, MINIMUM) == MINIMUM);
   }
   for (int i = 0; i < 1000; i++)
   {
       p->expose(low);
       assert(p->bet(bankroll, MINIMUM) == MINIMUM*2);
   }
  return 0;
}
