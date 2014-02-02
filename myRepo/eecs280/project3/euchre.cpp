#include <iostream>
#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include "Game.h"
#include <cstdlib>
#include <cstring>

using namespace std;

const unsigned int MAX_NAME_SIZE = 100;

int main(int argc, char *argv[])
{
   char errorMessage[] = "Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 NAME2 NAME3 NAME4\n";

   if (argc != 8){
      cout << errorMessage;
      exit(EXIT_FAILURE);
   }

   int points_to_win = atoi(argv[3]);
   if (points_to_win < 1 || points_to_win > 100){
      cout << errorMessage;
      exit(EXIT_FAILURE);
   }

   if (strcmp(argv[2],"noshuffle") && strcmp(argv[2],"shuffle")){
      cout << errorMessage;
      exit(EXIT_FAILURE);
   }
   bool shuffle;
   if (!strcmp(argv[2],"noshuffle")) shuffle = false;
   else shuffle = true;
   
   for (int i = 0; i < argc; i++)
   {
      cout << argv[i] << " ";
   }
   cout << endl;

   Game game1;
   Game_init(&game1, argv[1], shuffle, points_to_win,
             const_cast<const char**>(&argv[4]));
   Game_play(&game1);
   
   return EXIT_SUCCESS;
}
