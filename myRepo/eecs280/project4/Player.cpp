#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Hand.h"
#include <cstring>
#include <cassert>

using namespace std;

/////////////////////////// SIMPLE PLAYER ///////////////////////////////////
class Simple_player : public Player {
   public:
      virtual int bet(unsigned int bankroll, unsigned int minimum);
      bool draw (Card dealer, const Hand &player);
      virtual void expose(Card c);
      virtual void shuffled();
      ~Simple_player();
};

int Simple_player::bet(unsigned int bankroll, unsigned int minimum)
{
   assert(bankroll > minimum);
   return minimum;
}

bool Simple_player::draw(Card dealer, const Hand &player)
{
   int handValue = player.hand_value();
   if (player.hand_is_soft()){
      if (handValue <= 17) return true;
      else if (handValue == 18){
         if (dealer.get_rank() == Card::TWO ||
             dealer.get_rank() == Card::SEVEN ||
             dealer.get_rank() == Card::EIGHT) return false;
         else return true;
      }
      else return false;
   }
   else {
      if (handValue <= 11) return true;
      else if (handValue == 12){
         if (dealer.get_rank() == Card::FOUR ||
             dealer.get_rank() == Card::FIVE ||
             dealer.get_rank() == Card::SIX) return false;
         else return true;
      }
      else if (handValue >= 13 && handValue <= 16){
         if (static_cast<int>(dealer.get_rank()) <= 4) return false;
         else return true;
      }
      else return false;
   }
}

void Simple_player::expose(Card c){}
void Simple_player::shuffled(){}
Simple_player::~Simple_player(){}


//////////////////////// COUNTING PLAYER //////////////////////////////////
class Counting_player : public Simple_player {
      int count;
   public:
      Counting_player();
      int bet(unsigned int bankroll, unsigned int minimum);
      void expose(Card c);
      void shuffled();
      ~Counting_player();
};

Counting_player::Counting_player() : count(0) {}

int Counting_player::bet(unsigned int bankroll, unsigned int minimum)
{
   assert(bankroll >= minimum);
   if (count >= 2) {
      if (bankroll >= minimum * 2) return minimum * 2;
      else return bankroll;
   }
   else return minimum;
}

void Counting_player::expose(Card c)
{
   int r = static_cast<int>(c.get_rank());
   if (r < 5) count += 1;
   else if (r > 7) count -= 1; 
}

void Counting_player::shuffled()
{
   count = 0;
}

Counting_player::~Counting_player(){}


/////////////////////////////// COMPETITOR ///////////////////////////////////
class Competitor : public Player {
     int count;
   public:
      Competitor();
      int bet(unsigned int bankroll, unsigned int minimum);
      bool draw (Card dealer, const Hand &player);
      void expose(Card c);
      void shuffled();
      ~Competitor();
};

Competitor::Competitor() : count(0) {}

int Competitor::bet(unsigned int bankroll, unsigned int minimum)
{
   assert(bankroll >= minimum);
   if (count < 0) return minimum;
   if (count == 0 || count == 1){
      if (bankroll - minimum * 2 < minimum && bankroll >= minimum * 2){
         return bankroll - minimum;
      } // he leaves enough in the bank to bet again next turn if he loses
      else if (bankroll > minimum * 2) return minimum * 2;
      else return bankroll;
   }
   else if (count == 2 || count == 3){
      if (bankroll >= minimum * 3) return minimum * 3;
      else return bankroll;
   }
   else{
      if (bankroll >= (minimum * 4 + count)) return minimum * 4 + count;
      else return bankroll;
   }
}

bool Competitor::draw(Card dealer, const Hand &player)
{
   if (player.hand_value() < 12) return true;
   else return false;
}

void Competitor::expose(Card c)
{
   int r = static_cast<int>(c.get_rank());
   if (r < 5) count += 1;
   else if (r > 7) count -= 1; 
}

void Competitor::shuffled()
{
   count = 0;
}

Competitor::~Competitor(){}


////////////////////////// PLAYER FACTORY ///////////////////////////////////
static Simple_player simple;
static Counting_player counting;
static Competitor competitor;

Player * player_factory(const char * s)
{
   if (strcmp(s, "simple") == 0) return &simple;
   if (strcmp(s, "counting") == 0) return &counting;
   if (strcmp(s, "competitor") == 0) return &competitor;
   assert(0);
}


