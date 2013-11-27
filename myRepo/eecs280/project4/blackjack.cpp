#include <iostream>
#include <cassert>
#include <cstdlib>

#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include "rand.h"

using namespace std;

struct Game {
   Player * player;
   Hand pHand, dHand; //pHand is the player's hand, dHand is the dealer's hand
   int bankroll;
   int maxHands;
   int hand; // counts number of hands played
   Deck deck;
};
const int MINIMUM = 5;

//REQUIRES: argv[1] and argv[2] contain positive integers, argv[3] contains
//          either "simple" "counting" or "competitor".  argc == 4
//MODIFIES: game
//EFFECTS: initializes a game with the inputs specified in argv
static void init_game(int argc, char** argv, Game* game);

//REQUIRES: game has been initialized
//MODIFIES: game, stdout
//EFFECTS: plays one hand of blackjack. Returns how much money player won
//         or lost
static int game_play_hand(Game *game, int wager, Card upCard, Card holeCard);

//REQUIRES: game has been initialized
//MODIFIES: game, stdout
//EFFECTS: shuffles the deck by making 7 random cuts
static void game_shuffle(Game *game);

//REQUIRES: game has been initialized
//MODIFIES: game, upCard, stdout
//EFFECTS: deals 2 cards to the player and two card to the dealer.
//         returns the dealer's hole card
static Card game_deal(Game *game, Card* upCard);


int main(int argc, char** argv)
{
   Game game;
   init_game(argc, argv, &game);
   game_shuffle(&game);
   while (game.bankroll >= MINIMUM && game.hand <= game.maxHands)
   {
      cout << "Hand " << game.hand << " bankroll " << game.bankroll << endl;
      if (game.deck.cards_remaining() < 20) game_shuffle(&game);
      int wager = game.player->bet(game.bankroll, MINIMUM);
      cout << "Player bets " << wager << endl;
      Card upCard;
      Card holeCard = game_deal(&game, &upCard);
      int payout = game_play_hand(&game, wager, upCard, holeCard);
      game.bankroll = game.bankroll + payout;
      game.hand += 1;
      game.pHand.discard_all();
      game.dHand.discard_all();
   }
   if (game.bankroll < 0) game.bankroll = 0; // this shouldn't ever happen
   cout << "Player has " << game.bankroll << " after "
        << game.hand - 1 << " hands\n";
   return 0;   
}

static void init_game(int argc, char** argv, Game* game)
{
   if (argc != 4) assert(0);
   game->bankroll = atoi(argv[1]);
   game->maxHands = atoi(argv[2]);
   game->hand = 1;
   game->deck = Deck();
   game->player = player_factory(argv[3]); 
}


static int game_play_hand(Game *game, int wager, Card upCard, Card holeCard)
{
    if (game->pHand.hand_value() == 21){
       cout << "Player dealt natural 21\n";
       return (wager * 3) / 2;
    }
    bool hit = game->player->draw(upCard, game->pHand);
    while(hit){
       Card c = game->deck.deal();
       game->pHand.add_card(c);
       game->player->expose(c);
       cout << "Player dealt " << c << endl;
       hit = game->player->draw(upCard, game->pHand);
       if (game->pHand.hand_value() > 21) break;
    }   
    cout << "Player's total is " << game->pHand.hand_value() << endl;
    if (game->pHand.hand_value() > 21){
       cout << "Player busts\n";
       return 0 - wager;
    }
    cout << "Dealer's hole card is " << holeCard << endl;
    game->player->expose(holeCard);
    while (game->dHand.hand_value() < 17){
       Card c = game->deck.deal();
       game->dHand.add_card(c);
       cout << "Dealer dealt " << c << endl;
       game->player->expose(c);
    }
    cout << "Dealer's total is " << game->dHand.hand_value() << endl;
    if (game->dHand.hand_value() > 21){
       cout << "Dealer busts\n";
       return wager;
    }
    else if (game->dHand.hand_value() > game->pHand.hand_value()){
       cout << "Dealer wins\n";
       return 0 - wager;
    }
    else if (game->dHand.hand_value() == game->pHand.hand_value()){
       cout << "Push\n";
       return 0;
    }
    else {
       cout << "Player wins\n";
       return wager;
    }
}

static void game_shuffle(Game *game)
{
   cout << "Shuffling the deck\n";
   for(int i = 0; i < 7; i++)
   {
      int cut = get_cut();
      game->deck.shuffle(cut);
      cout << "cut at " << cut << endl;
   }
   game->player->shuffled();
}

static Card game_deal(Game *game, Card* upCard)
{
   Card c = game->deck.deal();
   game->pHand.add_card(c);
   game->player->expose(c);
   cout << "Player dealt " << c << endl;

   c = game->deck.deal();
   game->player->expose(c);
   game->dHand.add_card(c);
   cout << "Dealer dealt " << c << endl;
   *upCard = c;

   c = game->deck.deal();
   game->pHand.add_card(c);
   game->player->expose(c);
   cout << "Player dealt " << c << endl;

   // hole card
   c = game->deck.deal();
   game->dHand.add_card(c);
   return c;
}

