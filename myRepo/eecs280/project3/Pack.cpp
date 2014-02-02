#include "Pack.h"
#include "Card.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

void Pack_init(Pack *pack_ptr, const char* pack_filename)
{
   ifstream packfile;
   if (!packfile.is_open()) packfile.open(pack_filename);
   if (!packfile.is_open())
   {
      cout << "Error reading ";
      while (*pack_filename)
      {
         cout << *pack_filename;
         pack_filename++;
      }
      cout << endl;
      exit(EXIT_FAILURE);
   }
   for (int i = 0; i < 24; i++)
   {
      char r[10];
      char s[10];
      packfile.getline(r, 10, ' ');
      assert(r[0]);
      packfile.getline(s, 10, ' '); // takes in the "of" and throws it away
      packfile.getline(s, 10, '\n');
      Card_init(&(pack_ptr->cards[i]), r, s); 
   }
   pack_ptr->next = &(pack_ptr->cards[0]);

}

void Pack_print(const Pack *pack_ptr)
{
   for (int i = 0; i < 24; i++)
   {
      switch (pack_ptr->cards[i].rank)
      {
         case TWO: cout << "Two"; break;
         case THREE: cout << "Three"; break;
         case FOUR: cout << "Four"; break;
         case FIVE: cout << "Five"; break;
         case SIX: cout << "Six"; break;
         case SEVEN: cout << "Seven"; break;
         case EIGHT: cout << "Eight"; break;
         case NINE: cout << "Nine"; break;
         case TEN: cout << "Ten"; break;
         case JACK: cout << "Jack"; break;
         case QUEEN: cout << "Queen"; break;
         case KING: cout << "King"; break;
         case ACE: cout << "Ace"; break;
         default: assert(0);          
      }
      cout << " of ";
      switch (pack_ptr->cards[i].suit)
      {
         case CLUBS: cout << "Clubs"; break;
         case HEARTS: cout << "Hearts"; break;
         case SPADES: cout << "Spades"; break;
         case DIAMONDS: cout << "Diamonds"; break;
         default: assert(0);
      }
      if (&(pack_ptr->cards[i]) == pack_ptr->next) cout << " *next";
      cout << endl;
   }
}


Card Pack_deal_one(Pack *pack_ptr)
{
   int i = 0;
   while (&(pack_ptr->cards[i]) != pack_ptr->next)
   {
      if (i > 52) assert(0);
      i++;
   }
   pack_ptr->next = pack_ptr->next + 1;
   return pack_ptr->cards[i];
}


void Pack_reset(Pack *pack_ptr)
{
   pack_ptr->next = &(pack_ptr->cards[0]);
}


void Pack_shuffle(Pack *pack_ptr)
{
   for (int i = 0; i < 3; i++)
   {
      Card a[17];
      Card b[7];
      for (int i = 0; i < 24; i++)
      {
         if (i < 17) a[i] = pack_ptr->cards[i];
         else b[i - 17] = pack_ptr->cards[i];
      }
      for (int i = 0; i < 24; i++)
      {
         if (i < 7) pack_ptr->cards[i] = b[i];
         else pack_ptr->cards[i] = a[i - 7];
      }
   }
   pack_ptr->next = &pack_ptr->cards[0];
}

