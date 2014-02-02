#include "Card.h"
#include "Player.h"
#include "Pack.h"
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void Player_init(Player *player_ptr, const char *name)
{
   if (static_cast<int>(strlen(name)) >= MAX_STR_LEN){
      for (int i = 0; i < MAX_STR_LEN; i++){
         *(player_ptr->name + i) = *(name + i);
      }
      *(player_ptr->name + MAX_STR_LEN - 1) = '\0';
   }
   else strcpy((player_ptr->name), name);
   player_ptr->hand_size = 0;
}

void Player_print(const Player *player_ptr)
{
   int i = 0;
   while (player_ptr->name[i])
   {
      cout << player_ptr->name[i];
      i++;
   }
   cout << endl;
   for (int k = player_ptr->hand_size; k > 0; k--)
   {
      cout << "    ";
      Card_print(&(player_ptr->hand[k - 1]));
      cout << endl;
   }   
}


void Player_add_card(Player *player_ptr, const Card *c)
{
   player_ptr->hand[player_ptr->hand_size] = *c;
   player_ptr->hand_size += 1;
}


Make_response Player_make_trump(const Player *player_ptr, const Card *upcard, Player *dealer, int round)
{
   Make_response resp;
   resp.orderup = false;
   resp.trump = upcard->suit;
   if (round == 1)
   {
      int trumpFaceCount = 0;
      for (int i = 0; i < MAX_HAND_SIZE; i++)
      {
         if (Card_is_trump(&player_ptr->hand[i], upcard->suit) && 
               Card_is_face(&player_ptr->hand[i])){
            trumpFaceCount++;
         }
      }
      if (trumpFaceCount >= 2)
      {
         resp.orderup = true;
         resp.trump = upcard->suit;
      }
      else 
      {
         resp.orderup = false;
         resp.trump = upcard->suit;
      }
      return resp;
   }
   if (round == 2)
   {
      if (player_ptr == dealer)
      {
         resp.orderup = true;
         resp.trump = Suit_next(upcard->suit);
         return resp;
      }
      Suit nextSuit = Suit_next(upcard->suit);
      for (int i = 0; i < MAX_HAND_SIZE; i++)
      {
         if (Card_is_trump(&player_ptr->hand[i], nextSuit)
               && Card_is_face(&player_ptr->hand[i]))
         {
            resp.orderup = true;
            resp.trump = nextSuit;
            return resp;
         } 
      }
      resp.orderup = false;
      resp.trump = upcard->suit;
      return resp;
   }
   else return resp;
}


void Player_add_and_discard(Player *player_ptr, const Card *upcard, Suit trump)
{
   Card lowCard = *upcard;
   Card * card_to_discard = player_ptr->hand;
   for (int i = 0; i < player_ptr->hand_size; i++)
   {
      if (Card_compare(&lowCard, &(player_ptr->hand[i]), trump) > 0)
      {
         lowCard = player_ptr->hand[i];
         card_to_discard = &(player_ptr->hand[i]); 
      }
   }
   if (Card_compare(&lowCard, upcard) == 0) return;
   else 
   {
      *card_to_discard = *upcard;
   }
}


//REQUIRES: Player has at least one card
//EFFECTS: Returns true if all the Players's cards are trump
static bool all_trump(Player *player_ptr, Suit trump)
{
   for (int i = 0; i < player_ptr->hand_size; i++)
   {
      if (!Card_is_trump(&(player_ptr->hand[i]), trump)) return false;
   }
   return true;
}

//REQUIRES: Hand has at least one card and no trump cards
//EFFECTS: Returns the highest card in hand
static Card find_high(const Card *hand, int handSize)
{
   Card highCard = *hand;
   for (int i = 0; i < handSize; i++)
   {
      if (Card_compare(&highCard, hand + i) < 0) highCard = *(hand + i);
   }
   return highCard;
}

/* MODIFIES: player_ptr
 * EFFECTS: removes the Card equal to card from player_ptr's hand
 */
static void Remove_card(const Card * card, Player * player_ptr)
{
    for (int i = 0; i < player_ptr->hand_size; i++)
    {
       if (card->suit == player_ptr->hand[i].suit &&
             card->rank == player_ptr->hand[i].rank){
          int k = i;
          while (k < player_ptr->hand_size - 1){
             player_ptr->hand[k] = player_ptr->hand[k + 1];
             k++;
          }
          player_ptr->hand_size--;
          return;
       }
    }
    assert(0); // couldn't find card to remove
}

Card Player_lead_card(Player *player_ptr, Suit trump)
{
   if (all_trump(player_ptr, trump))
   {
      Card * highCard = &(player_ptr->hand[0]);
      for (int i = 0; i < player_ptr->hand_size; i++)
      {
         if (Card_compare(highCard, &(player_ptr->hand[i]), trump) < 0)
         {
            highCard = &(player_ptr->hand[i]);
         } 
      }
      Card card = *highCard;
      Remove_card(highCard, player_ptr);
      return card;
   }
   else 
   {
      Card hand_without_trumps[MAX_HAND_SIZE];
      int hand_without_trumps_size = 0;
      for (int i = 0; i < player_ptr->hand_size; i++)
      {
         if (!Card_is_trump(&(player_ptr->hand[i]), trump))
         { 
            hand_without_trumps[hand_without_trumps_size] = player_ptr->hand[i];
            hand_without_trumps_size += 1;
         }
      }
      Card played = find_high(hand_without_trumps, hand_without_trumps_size);
      Remove_card(&played, player_ptr);
      return played;
   }
}

Card Player_play_card(Player *player_ptr, Suit led_suit, Suit trump)
{
   Card cards_of_ledSuit[MAX_HAND_SIZE];
   int num_cards_of_ledSuit = 0;
   for (int i = 0; i < player_ptr->hand_size; i++)
   {
      if (player_ptr->hand[i].suit == led_suit ||
          (led_suit == trump &&
           Card_is_left_bower(&player_ptr->hand[i], trump)))
      {
         cards_of_ledSuit[num_cards_of_ledSuit] = player_ptr->hand[i];
         num_cards_of_ledSuit += 1;
      }
   }
   if ((num_cards_of_ledSuit > 0))
   {
      Card * highCard = cards_of_ledSuit;
      for (int i = 0; i < num_cards_of_ledSuit; i++)
      {
         if (Card_compare(highCard, &cards_of_ledSuit[i], trump) < 0)
         {
            highCard = &cards_of_ledSuit[i];
         }
      }
      Card card = *highCard;
      Remove_card(highCard, player_ptr);
      return card;
   }
   else 
   {
      Card * lowCard = player_ptr->hand;
      for (int i = 0; i < player_ptr->hand_size; i++)
      {
         if (Card_compare(lowCard, &(player_ptr->hand[i]), trump) > 0)
         {
            lowCard = &(player_ptr->hand[i]);
         }
      }
      Card tempcard = *lowCard;
      Remove_card(&tempcard, player_ptr);
      return tempcard;
   }
}
