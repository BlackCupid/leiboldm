#include <iostream>
#include "Game.h"
#include "Pack.h"
#include "Card.h"
#include "Player.h"
#include <cstring>
#include <cstdlib>

using namespace std;

void Game_init(Game *game_ptr, const char *pack_filename,
               bool shuffle, int points_to_win, const char *player_names[])
{
   Pack_init(&game_ptr->pack, pack_filename);
   game_ptr->shuffle = shuffle;
   game_ptr->score[0] = 0;
   game_ptr->score[1] = 0;
   game_ptr->points_to_win = points_to_win;
   for (int i = 0; i < NUM_PLAYERS; i++)
   {
      Player_init(&game_ptr->players[i], player_names[i]);
   } 
}

// Function prototypes for function used in Game_play()
// RMEs located with function implementation
static int Next_player(int player);
static void Game_deal(Game *game_ptr, int dealer);
static Suit Game_make_trump(Game *game_ptr, int dealer, int * maker);
static void Game_play_trick(Game *game_ptr, int * lead_player, Suit trump,
                            int * hand_score);
static int Find_winning_card(Card *lead, Card *c1, Card *c2, Card *c3,
                             Suit trump, const int * whose_card);
static void Game_update_score(Game *game_ptr, const int * hand_score,
                               int maker);

/* MODIFIES: stdout
 * EFFECTS: prints each players hand, used for debugging
 *
static void print_hands(Game * game_ptr)
{
    for (int j = 0; j < NUM_PLAYERS; j++)
    {
        cout << "\t";
        Player_print(&game_ptr->players[j]);
    }
}
*/

void Game_play(Game *game_ptr)
{
    int dealer = 0;
    int hand = 0;

    // Play hands until one team reaches score to win
    while (game_ptr->score[0] < game_ptr->points_to_win
           && game_ptr->score[1] < game_ptr->points_to_win)
    {
        if (game_ptr->shuffle) Pack_shuffle(&game_ptr->pack);
        else Pack_reset(&game_ptr->pack);
        Game_deal(game_ptr, dealer);
        cout << "Hand " << hand << endl;
        cout << game_ptr->players[dealer].name << " deals\n";

        int maker = 0; // player who makes trump
        Suit trump = Game_make_trump(game_ptr, dealer, &maker);

        // Play all tricks
        int hand_score[2] = {0, 0};
        int leader = Next_player(dealer);
        for (int i = 0; i < MAX_HAND_SIZE; i++)
        {
            Game_play_trick(game_ptr, &leader, trump, hand_score);
        }

        Game_update_score(game_ptr, hand_score, maker);
        dealer = Next_player(dealer);
        hand++;
    }

    // Game is over, print score
    if (game_ptr->score[0] > game_ptr->score[1]){
       cout << game_ptr->players[0].name << " and " << game_ptr->players[2].name
            << " win!\n";
    }
    else {
       cout << game_ptr->players[1].name << " and " << game_ptr->players[3].name
            << " win!\n";
    }
}

/* REQUIRES: player is between 0 and 3 inclusive
 * EFFECTS: returns the number of the player to the left of player
 */
static int Next_player(int player)
{
   int next = 0;
   if (player < 3) next = player + 1;
   else next = 0;
   return next;
}

/* REQUIRES: dealer is between 0 and 3 inclusive
 * MODIFIES: game_ptr
 * EFFECTS: deals 5 cards to each player in game_ptr
 */
static void Game_deal(Game *game_ptr, int dealer)
{
    int player = Next_player(dealer);
    int round = 1;
    for (int i = 0; i < NUM_PLAYERS * 2; i++)
    {
        if (((i % 2) == 0 && round == 1) || ((i % 2) == 1 && round == 2)) {
            for (int j = 0; j < 3; j++){
               Card c1 = Pack_deal_one(&game_ptr->pack);
               Player_add_card(&game_ptr->players[player], &c1);
            }
        }
        else {
           for (int j = 0; j < 2; j++){
              Card c1 = Pack_deal_one(&game_ptr->pack);
              Player_add_card(&game_ptr->players[player], &c1);
           }
        }
        if (i == 3) round = 2;
        player = Next_player(player);
    }    
}

/* REQUIRES: dealer is between 0 and 3 inclusive
 * MODIFIES: game_ptr, stdout, maker
 * EFFECTS: Makes trump, returns it, and prints out all moves
 */
static Suit Game_make_trump(Game *game_ptr, int dealer, int * maker)
{
    Card turned_up = Pack_deal_one(&game_ptr->pack);
    Card_print (&turned_up);
    cout << " turned up\n";

    int player = Next_player(dealer);
    bool ordered_up = false;
    int round  = 1;
    while (!ordered_up)
    {
        Make_response resp;
        resp = Player_make_trump(&game_ptr->players[player], &turned_up,
                      &game_ptr->players[dealer], round);
        if (resp.orderup == false)
        {
            cout << game_ptr->players[player].name << " passes\n";
        }
        else if (resp.orderup == true)
        {
           ordered_up = true;
           cout << game_ptr->players[player].name << " orders up ";
           Suit_print(resp.trump);
           cout << "\n\n";
           *maker = player;
           if (round == 1){
              Player_add_and_discard(&game_ptr->players[dealer],
                    &turned_up, resp.trump);
           }
           return resp.trump;
        }
        if (player == dealer) round = 2;
        player = Next_player(player);
    }
    exit(EXIT_FAILURE);
    return HEARTS;      // this statement will never be executed
                        // it's just here to appease the compiler
}

/* REQUIRES: lead_player is between 0 and 3 inclusive
 * MODIFIES: game_ptr, stdout, hand_score, lead_player
 * EFFECTS: Plays one trick, updates hand score, prints all moves,
 *          updates lead_player to be winner of the trick
 */
static void Game_play_trick(Game *game_ptr, int * lead_player, Suit trump,
                             int * hand_score)
{
   int player = *lead_player;
   int whose_card[4];
   // whose_card[i] contains the number of the player who played the ith card
   // i.e: whose_card[0] is the number of player who led

   Card lead = Player_lead_card(&game_ptr->players[player], trump);
   Card_print(&lead);
   cout << " led by " << game_ptr->players[player].name << endl;
   whose_card[0] = player;

   player = Next_player(player);
   Card c1 = Player_play_card(&game_ptr->players[player], lead.suit, trump);
   Card_print(&c1);
   cout << " played by " << game_ptr->players[player].name << endl;
   whose_card[1] = player;

   player = Next_player(player);
   Card c2 = Player_play_card(&game_ptr->players[player], lead.suit, trump);
   Card_print(&c2);
   cout << " played by " << game_ptr->players[player].name << endl;
   whose_card[2] = player;

   player = Next_player(player);
   Card c3 = Player_play_card(&game_ptr->players[player], lead.suit, trump);
   Card_print(&c3);
   cout << " played by " << game_ptr->players[player].name << endl;
   whose_card[3] = player;

   player = Find_winning_card(&lead, &c1, &c2, &c3, trump, whose_card);
   *lead_player = player;
   cout << game_ptr->players[player].name << " takes the trick\n\n";
   if (player % 2) *(hand_score + 1) += 1;
   else *hand_score += 1;
}
/* REQUIRES: whose_card points to an array of integers between 0 and 3
 * EFFECTS: Find the winning card and returns the number of the player
 *          who played that card
 */
static int Find_winning_card(Card *lead, Card *c1, Card *c2, Card *c3,
                             Suit trump, const int * whose_card)
{
    int winner = 0;  // winner refers to the number of the winning card
                     // i.e: winner is 1 if card c1 is the winner
    Card * cards[4] = {lead, c1, c2, c3};
    if (Card_compare(cards[0], c1, trump, lead->suit) < 0){
       winner = 1;
    }
    if (Card_compare(cards[winner], c2, trump, lead->suit) < 0){
       winner = 2;
    }
    if (Card_compare(cards[winner], c3, trump, lead->suit) < 0){
       winner = 3; 
    }
    return *(whose_card + winner);
}

/* REQUIRES: maker is between 0 and 3 inclusive
 *           hand_score is an array of 2 ints which are not equal
 *           to eachother
 * MODIFIES: game_ptr, stdout
 * EFFECTS: determines winner of hand, updates and prints score
 */
static void Game_update_score(Game *game_ptr, const int * hand_score, int maker)
{
   if (*hand_score > *(hand_score + 1)){ // if team 0 won the hand
      cout << game_ptr->players[0].name << " and "
           << game_ptr->players[2].name << " win the hand\n";
      if (maker % 2 == 0){ 
         if (*hand_score < 5) game_ptr->score[0] += 1;
         else if (*hand_score == 5){ // march
            game_ptr->score[0] += 2; 
            cout << "march!\n";
         }
      }
      else { // euchred
         game_ptr->score[0] += 2;
         cout << "euchred!\n";
      }
   }
   else{
      cout << game_ptr->players[1].name << " and "
           << game_ptr->players[3].name << " win the hand\n";
      if (maker % 2 == 1){
         if (*(hand_score + 1) < 5) game_ptr->score[1] += 1;
         else if (*(hand_score + 1) == 5) { // march
            game_ptr->score[1] += 2;
            cout << "march!\n";
         }
      }
      else{
         game_ptr->score[1] += 2; // euchered
         cout << "euchred!\n";
      }
   }

   // print the game score
   cout << game_ptr->players[0].name << " and "
        << game_ptr->players[2].name << " have "
        << game_ptr->score[0] << " points\n";
   cout << game_ptr->players[1].name << " and "
        << game_ptr->players[3].name << " have "
        << game_ptr->score[1] << " points\n\n";
}


