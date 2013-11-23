#include <iostream>
#include <cassert>
#include "Deck.h"
#include "Card.h"

Deck::Deck(){ 
   reset();
}

void Deck::reset(){
   const int NUMSUITS = 4;
   const int NUMRANKS = 13;
   for (int i = 0; i < NUMSUITS; i++)
   {
      for (int j = 0; j < NUMRANKS; j++)
      {
         Card::Rank ranks[NUMRANKS] = {Card::TWO, Card::THREE, Card::FOUR,
            Card::FIVE, Card::SIX, Card::SEVEN, Card::EIGHT, Card::NINE, 
            Card::TEN, Card:: JACK, Card::QUEEN, Card::KING, Card::ACE};
         if (i == 0) deck[NUMRANKS*i + j] = Card(ranks[j], Card::SPADES);
         if (i == 1) deck[NUMRANKS*i + j] = Card(ranks[j], Card::HEARTS); 
         if (i == 2) deck[NUMRANKS*i + j] = Card(ranks[j], Card::CLUBS);
         if (i == 3) deck[NUMRANKS*i + j] = Card(ranks[j], Card::DIAMONDS);
      }
   }
   next = deck;
}

void Deck::shuffle(int n){
   Card::Card left[DECK_SIZE];
   Card::Card right[DECK_SIZE];
   for (int i = 0; i < DECK_SIZE; i++)
   {
      if (i < n) left[i] = deck[i];
      else right[i - n] = deck[i];
   }
   int rightSize = DECK_SIZE - n;
   int rightIndex = 0, leftIndex = 0;
   for (int i = 0; i < DECK_SIZE; i++)
   {
      if (rightIndex < rightSize && !(i % 2)){
         deck[i] = right[rightIndex++];
      }
      else if (leftIndex < n && (i % 2)){
         deck[i] = left[leftIndex++];
      }
      else if (rightIndex >= rightSize){
         deck[i] = left[leftIndex++];
      }
      else if (leftIndex >= n){
         deck[i] = right[rightIndex++];
      }
      else assert(0);
   }
   next = deck;
}

Card::Card Deck::deal()
{
   assert(next);
   Card::Card* dealt = next;
   if (next == &deck[51]) next = 0;
   //next is NULL pointer if all cards have been dealt
 
   else next++;
   return *dealt;
}

int Deck::cards_remaining() const
{
   if (next == 0) return 0;

   int cardsRemaining = 1;
   for (Card::Card* i = next; i != &deck[51]; i++)
   {
      cardsRemaining++;
   }
   return cardsRemaining;
}



