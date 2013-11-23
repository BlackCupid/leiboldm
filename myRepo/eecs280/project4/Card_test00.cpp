#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;


int main() {
  Card c1;
  assert(c1.get_rank() == Card::TWO);
  assert(c1.get_suit() == Card::SPADES);
  cout << c1 << endl;
  
  Card c2(Card::FIVE, Card::HEARTS);
  assert(c2.get_rank() == Card::FIVE);
  assert(c2.get_suit() == Card::HEARTS);
  cout << c2 << endl;
}
