#include <iostream>
#include <getopt.h>
#include <string>
#include <sstream>
#include "farmpoint.h"
#include "Routing.h"

using namespace std;

void printmap(char** map, int farmsize, int farmcount);
void print_list_output(char** map, Farmpoint start, int farmsize);
char check_valid(char** map, Farmpoint pt, int farmsize);

int main(int argc, char** argv){
   struct option longOpts[] = {
      {"stack", no_argument, NULL, 's'},
      {"queue", no_argument, NULL, 'q'},
      {"help", no_argument, NULL, 'h'},
      {"output", required_argument, NULL, 'o'},
      {NULL, 0, 0, 0}
   };
   
   int opt = 0, index = 0;
   char stackOrQueue = 0;
   char outputMode = 'M';
   while((opt = getopt_long (argc, argv, "sqho:", longOpts, &index)) != -1){
      switch(opt) {
        case 's':
            stackOrQueue = 's';
            break;
        case 'q':
            if (stackOrQueue == 's') {
               cerr << "Contradictory choice of routing" << endl;
               exit(1);
            }
            stackOrQueue = 'q';
            break;
        case 'h':
            cout << "You need help? So do I!\n";
            break;
        case 'o':
            if (*optarg == 'L'){
               outputMode = 'L';
            }
            else if (*optarg != 'M'){
                cerr << "\nInvalid output option." << endl;
                exit(1);
            }
            break;
        case '?':
            cerr << "Invalid command line argument" << endl;;
            exit(1);
      }
   }
  
   string line;
   getline(cin, line);
   char mode = line[0];
   if (mode != 'M' && mode != 'L') {
      cerr << "Input file type is invalid" << endl;
      exit(1);
   }
   getline(cin, line);
   int farmsize = atoi(line.c_str());
   getline(cin, line);
   int farmcount = atoi(line.c_str());

   char** map = new char*[farmsize*farmcount];
   char** mapcopy = new char*[farmsize*farmcount];
   for (int i = 0; i < farmsize*farmcount; ++i) {
      map[i] = new char[farmsize];
      mapcopy[i] = new char[farmsize];
   }

   if (mode == 'M') {
      int line_count = 0;
      while (getline(cin, line)) {
         if (line[0] == '/' && line[1] == '/') continue;
         else if (line.empty()) {
            if (line_count < farmsize*farmcount - 1) { 
               // if we haven't reached the end of the map
               cerr << "Illegal space/newline or insufficient inputs" << endl;
               exit(1);
            }
            break;
         }
         else {
            for (int i = 0; i < farmsize; ++i) {
               if (line[i] != '.' && line[i] != '#' && line[i] != '>' &&
                   line[i] != '<' && line[i] != 'B' && line[i] != 'S') {
                   cerr << "Input file contains invalid character " <<
                           line[i] << endl;;
                   cerr << "line_count = " << line_count << endl;
                   exit(1);
               }
               else {
                  map[line_count][i] = line[i];
                  mapcopy[line_count][i] = line[i];
               }
            }
            ++line_count;
         }
      }
   }
   else {
      for (int i = 0; i < farmsize*farmcount; i++) {
         for (int j = 0; j < farmsize; j++) {
            map[i][j] = '.';
            mapcopy[i][j] = '.';
         }
      }
      while(getline(cin, line)) {
         if ((line[0] == '/' and line[1] == '/') || line.empty()) continue;
         else {
            int row = atoi(&line[1]);
            if (row >= farmsize*farmcount || row < 0) { 
                cerr << "row too big or too small. row = " << row << endl;
                exit(1);
            }
            int col = line.find_first_of(',', 2);
            int farm = line.find_first_of(',', col + 1);
            int cpos = line.find_first_of(',', farm + 1);
            char c = line[cpos + 1];
            col = atoi(&line[col + 1]);
            farm = atoi(&line[farm + 1]);
            if (col >= farmsize || col < 0) {
               cerr << "col too big or too small. col = " << col << endl;
               exit(1);
            }
            if (farm < 0 || farm >= farmcount) {
               cerr << "farm " << farm << " doesn't exist" << endl;
               exit(1);
            }
            if (c != '#' && c != '<' && c != '>' && c != 'S' && c != 'B') {
               cerr << "character " << c << ", row= " << row << " , col=" << col
                    << " ,farm= " << farm << ", is invalid character" << endl;
               exit(1);
            }
            map[row + farm*farmsize][col] = c;
            mapcopy[row + farm*farmsize][col] = c;
        }
      } 
   } 
   Farmpoint start;
   Farmpoint buck;
   start.row = -1; 
   start.col = -1; 
   start.farm = -1;
   for (int r = 0; r < farmsize; r++) {
      for (int c = 0; c < farmsize; c++){
         for (int f = 0; f < farmcount; f++) {
            if (map[f * farmsize + r][c] == 'S') {
               start.col = c;
               start.row = r;
               start.farm = f; 
            }
            else if (map[f * farmsize + r][c] == 'B') {
               buck.col = c;
               buck.row = r;
               buck.farm = f;
            }
         }
      }
   }

   bool buck_found = false;   
   if (stackOrQueue == 's'){ 
      buck_found = stackRout(map, farmsize, farmcount, start); 
   } 
   else if (stackOrQueue == 'q') { 
      buck_found = queueRout(map, farmsize, farmcount, buck);
      dequeueMap(map, mapcopy, buck, start, farmsize, farmcount);
   }   
   else {
      cerr << "You must specify either stack or queue" << endl;
      exit(1);
   }

   cout << farmsize << "\n" << farmcount << "\n";
   if (outputMode == 'M'){
      if (buck_found) printmap(map, farmsize, farmcount);
      else printmap(mapcopy, farmsize, farmcount);
   }
   else {
      if (buck_found) print_list_output(map, start, farmsize);
      else {
         cout << "//path taken\n";
      }
   }

   for (int i = 0; i < farmsize*farmcount; i++) {
      delete[] map[i];
      delete[] mapcopy[i];
   }
   delete map;
   delete mapcopy;
   return(0);
}

//Modifes: stdout
//EFFECTS: prints the map, used for debugging
void printmap(char** map, int farmsize, int farmcount) {
   for (int f = 0; f < farmcount ; f++) {
      cout << "//farm " << f << "\n";
      for (int r = 0; r < farmsize; r++) {
         for (int c = 0; c < farmsize; c++) {
            if (map[f * farmsize + r][c] == 'x' || 
                map[f * farmsize + r][c] == '-') cout << ".";
            else if (map[f * farmsize + r][c] == '(') cout << "<";
            else if (map[f * farmsize + r][c] == ')') cout << ">";
            else cout << map[f * farmsize + r][c];
         }
         cout << "\n";
      } 
   }
}

void print_list_output(char** map, Farmpoint start, int farmsize) {
   cout << "//path taken\n";
   char c = map[start.row + start.farm * farmsize][start.col]; 
   Farmpoint next = start, prev = {0,0,0};
   char nextc = 0;
   while(next.col != prev.col || next.row != prev.row || 
         next.farm != prev.farm) { 
      prev = start;
      cout << "(" << start.row << "," << start.col << "," << start.farm
           << "," << c << ")\n";
      if (c == 'n') {
         next.row -= 1; 
      }
      else if (c == 'e') {
         next.col += 1;
      }
      else if (c == 'w') {
         next.col -= 1;
      }
      else if (c == 's') {
         next.row += 1;
      }
      else if (c == 'd') {
         next.farm -= 1;
      }
      else if (c == 'u') {
         next.farm += 1;
      }
      nextc = map[next.row + next.farm * farmsize][next.col];
      if (nextc == 'B') return;
      else {
         start = next;
         c = nextc;
      }
   }
}
