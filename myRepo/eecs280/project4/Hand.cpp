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
/*
   switch (c.get_rank())
   {
      case (Card::TWO) : value += 2; break;
      case (Card::THREE) : value += 3; break;
      case (Card::FOUR) : value += 4; break;
      case (Card::FIVE) : value += 5; break;
      case (Card::SIX) : value += 6; break;
      case (Card::SEVEN) :value += 7; break;
      case (Card::EIGHT) : value += 8; break;
      case (Card::NINE) : value += 9; break;
      case (Card::TEN) : value += 10; break;
      case (Card::JACK) : value += 10; break;
      case (Card::QUEEN) : value += 10; break;
      case (Card::KING) : value += 10; break;
      case (Card::ACE) :
         if (value > 10){
            value += 1;
         }
         else {
            value += 11;
            soft = true;
         }
         break;
      default: assert(0);
   }
*/


int Hand::hand_value() const
{
   return value;
}

bool Hand::hand_is_soft() const
{
   return soft;
}
