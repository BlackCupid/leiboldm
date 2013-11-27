#include <iostream>
#include "Card.h"
#include "Hand.h"

using namespace std;

Hand::Hand() : value(0), soft(false) {}

void Hand::discard_all()
{
   value = 0;
   soft = false;
}

void Hand::add_card(Card c)
{ 
   int r = static_cast<int>(c.get_rank());
   if (r < 9){ // if rank is a number
      if (soft && (r + 2 + value > 21)){
         value = r + 2 + value - 10;
         soft = false;
      }
      else value = value + r + 2;
   }
   else if (r > 8 && r < 12){ // if card is face
      if (soft && (10 + value > 21)){
         soft = false;
         // value remains unchanged because we add 10 and subtract 10
      }
      else {
         value = value + 10;
      }
   }
   else { // card is ace
      if (value + 11 > 21){
         value += 1;
      }
      else {
         value += 11;
         soft = true;
      }
   }
}

int Hand::hand_value() const
{
   return value;
}

bool Hand::hand_is_soft() const
{
   return soft;
}
