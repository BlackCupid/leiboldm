#include <iostream>
#include <stack>
#include <queue>
#include <cctype>
#include "Routing.h"
#include "farmpoint.h"

using namespace std;

void pmap(char** map, int farmsize, int farmcount) {
   for (int f = 0; f < farmcount ; f++) {
      cout << "//farm " << f << "\n";
      for (int r = 0; r < farmsize; r++) {
         for (int c = 0; c < farmsize; c++) {
            cout << map[f * farmsize + r][c];
         }
         cout << "\n";
      } 
   }
}

char check_valid_q(char** map, Farmpoint pt, int farmsize) {
   if (pt.row < 0 || pt.row >= farmsize || pt.col < 0 || pt.col >= farmsize) {
      return 0; 
   }
   char c = map[pt.farm * farmsize + pt.row][pt.col];
   if (c != '.' && c != '<' && c != '>' && c != 'S') return 0;
   if (c == 'x') return 0;
   if (c == 'S') return 2;
   return 1;
   // S to B
}

char check_valid_s(char** map, Farmpoint pt, int farmsize, int farmcount) {
   if (!pt_exists(pt, farmsize, farmcount)) return 0;
   char c = map[pt.farm * farmsize + pt.row][pt.col];
   if (c != '.' && c != '<' && c != '>' && c != 'B') return 0;
   if (c == '-') return 0;
   if (c == 'B') return 2;
   if (c == 'x') return 3;
   return 1;
}

bool pt_exists(Farmpoint pt, int farmsize, int farmcount) {
   if (pt.row < 0 || pt.row >= farmsize || 
       pt.col < 0 || pt.col >= farmsize) return false;
   if (pt.farm < 0 || pt.farm == farmcount) return false;
   else return true;
}

bool stackRout(char** map, int farmsize, int farmcount, Farmpoint start){
   stack<Farmpoint> stack;
   stack.push(start);
   bool buckFound = false;
   Farmpoint prev = start;
   while (!buckFound && !stack.empty()) {
      pmap(map, farmsize, farmcount);
      Farmpoint top = stack.top();
      stack.pop();
      char c = map[top.farm * farmsize + top.row][top.col]; 
      Farmpoint next = {-1, -1, -1};
      bool invalid_move = false;
      bool tookLadder = false;
      if (c == '<' || c == '>' || c == '(' || c == ')') {    
         if (c == '<' || c == '(') {
            if (top.farm <= 0) invalid_move = true;
            next = {top.col, top.row, top.farm - 1};
         }
         else {
            next = {top.col, top.row, top.farm + 1};
            if (top.farm + 1 >= farmcount) invalid_move = true;
         }
         char n = 0;
         if (!invalid_move) n = map[next.farm * farmcount + next.row][next.col]; 
         if (next.farm >= farmcount || next.farm < 0 || 
             n == '#' || n == 'd' || n == 'u' || n == 'n' || n == 'e' ||
             n == 'w' || n == 's' || n == 'x') {
            invalid_move = true;
         }
         if (!invalid_move || n == 'B') {
            if (c == '<') map[top.farm * farmsize + top.row][top.col] = 'd';
            else map[top.farm * farmsize + top.row][top.col] = 'u';
            stack.push(next);
            tookLadder = true;
            prev = top;
            if (n == 'B') {
               buckFound = true;
               return true;
            }
         }
         if (invalid_move) {
            if (!stack.empty())
               backtrack(map, top, farmsize, stack.top(), farmcount);
            continue;
         }
      }
      if (!tookLadder) {
         char x = -1; // x holds return value from check_valid 
         bool no_moves = true;
         char nextc = 0;

         // Check north
         next = {top.col, top.row - 1, top.farm};
         x = check_valid_s(map, next, farmsize, farmcount);
         if (x == 3) no_moves = false;
         else if (x) {
            stack.push(next);
            nextc = map[next.farm * farmsize + next.row][next.col];
            if (nextc == '.') 
               map[next.farm * farmsize + next.row][next.col] = 'x';
            else if (nextc == '<')
               map[next.farm * farmsize + next.row][next.col] = '(';
            else if (nextc == '>')
               map[next.farm * farmsize + next.row][next.col] = ')';
            map[top.farm * farmsize + top.row][top.col] = 'n';
            no_moves = false;
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'B';
            return true;
         }

         // Check east
         next = {top.col + 1, top.row, top.farm};
         x = check_valid_s(map, next, farmsize, farmcount);
         if (x == 3) no_moves = false;
         else if (x) {
            stack.push(next);
            nextc = map[next.farm * farmsize + next.row][next.col];
            if (nextc == '.') 
               map[next.farm * farmsize + next.row][next.col] = 'x';
            else if (nextc == '<')
               map[next.farm * farmsize + next.row][next.col] = '(';
            else if (nextc == '>')
               map[next.farm * farmsize + next.row][next.col] = ')';
            map[top.farm * farmsize + top.row][top.col] = 'e';
            no_moves = false;
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'B';
            return true;
         }

         //Check south
         next = {top.col, top.row + 1, top.farm};
         x = check_valid_s(map, next, farmsize, farmcount);
         if (x == 3) no_moves = false;
         else if (x) {
            stack.push(next);
            nextc = map[next.farm * farmsize + next.row][next.col];
            if (nextc == '.') 
               map[next.farm * farmsize + next.row][next.col] = 'x';
            else if (nextc == '<')
               map[next.farm * farmsize + next.row][next.col] = '(';
            else if (nextc == '>')
               map[next.farm * farmsize + next.row][next.col] = ')';
            map[top.farm * farmsize + top.row][top.col] = 's';
            no_moves = false;
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'B';
            return true;
         }

         //Check west
         next = {top.col - 1, top.row, top.farm};
         x = check_valid_s(map, next, farmsize, farmcount);
         if (x == 3) no_moves = false;
         else if (x) {
            stack.push(next);
            nextc = map[next.farm * farmsize + next.row][next.col];
            if (nextc == '.') 
               map[next.farm * farmsize + next.row][next.col] = 'x';
            else if (nextc == '<')
               map[next.farm * farmsize + next.row][next.col] = '(';
            else if (nextc == '>')
               map[next.farm * farmsize + next.row][next.col] = ')';
            map[top.farm * farmsize + top.row][top.col] = 'w';
            no_moves = false;
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'B';
            return true;
         }
         if (no_moves && !stack.empty()) 
            backtrack(map, prev, farmsize, stack.top(), farmcount);
         else prev = top;
      } 
   }
   return false; // return false if buck wasn't found
}

void backtrack(char** map, Farmpoint current, int farmsize, 
               Farmpoint top, int farmcount) {
   //char c = map[current.farm * farmsize + current.row][current.col]; 
   map[current.farm * farmsize + current.row][current.col] = '-';
   Farmpoint north = {current.col, current.row - 1, current.farm};
   Farmpoint south = {current.col, current.row + 1, current.farm};
   Farmpoint east = {current.col + 1, current.row, current.farm};
   Farmpoint west = {current.col - 1, current.row, current.farm};
   //Farmpoint up = {current.col, current.row, current.farm + 1};
   //Farmpoint down = {current.col, current.row, current.farm - 1};
   if (top == north) {
      map[current.farm * farmsize + current.row][current.col] = 'n';
      return;
   }
   else if (top == south) {
      map[current.farm * farmsize + current.row][current.col] = 's';
      return;
   }
   else if (top == east) {
      map[current.farm * farmsize + current.row][current.col] = 'e';
      return;
   }
   else if (top == west) {
      map[current.farm * farmsize + current.row][current.col] = 'w';
      return;
   }
   else if (pt_exists(north, farmsize, farmcount) && 
            map[north.farm * farmsize + north.row][north.col] == 's') {
      backtrack(map, north, farmsize, top, farmcount); 
   }
   else if (pt_exists(south, farmsize, farmcount) && 
            map[south.farm * farmsize + south.row][south.col] == 'n') {
      backtrack(map, south, farmsize, top, farmcount);
   }
   else if (pt_exists(east, farmsize, farmcount) &&
            map[east.farm * farmsize + east.row][east.col] == 'w') {
      backtrack(map, east, farmsize, top, farmcount);
   }
   else if (pt_exists(west, farmsize, farmcount) && 
            map[west.farm * farmsize + west.row][west.col] == 'e') {
      backtrack(map, west, farmsize, top, farmcount);
   }
}

bool queueRout(char** map, int farmsize, int farmcount, Farmpoint start){
   queue<Farmpoint> queue;
   queue.push(start);
   bool buckFound = false;
   while (!buckFound && !queue.empty()) {
      Farmpoint top = queue.front();
      queue.pop();
      char c = map[top.farm * farmsize + top.row][top.col]; 
      Farmpoint next = {-1, -1, -1};
      bool invalid_move = false;
      bool tookLadder = false;
      if (c == '<' || c == '>') {    
         if (c == '<') {
            next = {top.col, top.row, top.farm - 1};
         }
         else {
            next = {top.col, top.row, top.farm + 1};
         }
         char n = map[next.farm * farmcount + next.row][next.col]; 
         if (next.farm >= farmcount || next.farm < 0 || 
             n == '#' || n == 'd' || n == 'u' || n == 'n' || n == 'e' ||
             n == 'w' || n == 's' || n == 'x') {
            invalid_move = true;
         }
         if (!invalid_move || n == 'S') {
            if (c == '<') map[top.farm * farmsize + top.row][top.col] = 'd';
            else map[top.farm * farmsize + top.row][top.col] = 'u';
            queue.push(next);
            tookLadder = true;
            if (n == 'S') {
               buckFound = true;
               return true;
            }
         }
      }
      if (!tookLadder) {
         char x = -1; // x holds return value from check_valid 
         char move = 0; 

         // Check north
         next = {top.col, top.row - 1, top.farm};
         x = check_valid_q(map, next, farmsize);
         if (x) {
            queue.push(next);
            if (map[next.farm * farmsize + next.row][next.col] == '.')
                map[next.farm * farmsize + next.row][next.col] = 'x';
            if (!move) move = 'n';
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'S';
            return true;
         }

         // Check east
         next = {top.col + 1, top.row, top.farm};
         x = check_valid_q(map, next, farmsize);
         if (x) {
            queue.push(next);
            if (map[next.farm * farmsize + next.row][next.col] == '.')
               map[next.farm * farmsize + next.row][next.col] = 'x';
            if (!move) move = 'e';
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'S';
            map[top.farm * farmsize + top.row][top.col] = move;
            return true;
         }

         //Check south
         next = {top.col, top.row + 1, top.farm};
         x = check_valid_q(map, next, farmsize);
         if (x) {
            queue.push(next);
            if (map[next.farm * farmsize + next.row][next.col] == '.')
               map[next.farm * farmsize + next.row][next.col] = 'x'; 
            if (!move) move = 's';
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'S';
            map[top.farm * farmsize + top.row][top.col] = move;
            return true;
         }

         //Check west
         next = {top.col - 1, top.row, top.farm};
         x = check_valid_q(map, next, farmsize);
         if (x) {
            queue.push(next);
            if (map[next.farm * farmsize + next.row][next.col] == '.')
               map[next.farm * farmsize + next.row][next.col] = 'x';
            if (!move) move = 'w';
         }
         if (x == 2) {
            map[next.farm * farmsize + next.row][next.col] = 'S';
            map[top.farm * farmsize + top.row][top.col] = move;
            return true;
         }

         if (move) map[top.farm * farmsize + top.row][top.col] = move;

      } 
   }
   return false;
}

void dequeueMap(char** map, char** mapcopy, Farmpoint buck,
                Farmpoint start, int farmsize, int farmcount) {
   char c = map[buck.farm * farmsize + buck.row][buck.col];
   map[buck.farm * farmsize + buck.row][buck.col] = 'B';
   Farmpoint next = buck;
   Farmpoint current = buck;
   if (c == 'e') {
      next.col += 1;
   }
   else if (c == 'n') {
      next.row += -1;
   } 
   else if (c == 'w') {
      next.col += -1;
   }
   else if (c == 's') {
      next.row += 1;
   }
   else if (c == 'd') {
      next.farm += -1;
   }
   else if (c == 'u') {
      next.farm += 1;
   }
   c = map[next.farm * farmsize + next.row][next.col];
   current = next;
   while (current.col != start.col || current.row != start.row
          || current.farm != start.farm) {
      if (c == 'e') {
         next.col += 1;
      }
      else if (c == 'n') {
         next.row += -1;
      } 
      else if (c == 'w') {
         next.col += -1;
      }
      else if (c == 's') {
         next.row += 1;
      }
      else if (c == 'd') {
         next.farm += -1;
      }
      else if (c == 'u') {
         next.farm += 1;
      }
      map[current.farm * farmsize + current.row][current.col] = toupper(c); 
      c = map[next.farm * farmsize + next.row][next.col];
      current = next;
   }
   for (int f = 0; f < farmcount; f++) {
      for (int r = 0; r < farmsize; r++) {
         for (int col = 0; col < farmsize; col++) {
            char c = map[f * farmsize + r][col];
            if (islower(c)) map[f * farmsize + r][col] = mapcopy[f * farmsize + r][col];
            if (isupper(c)) { 
               if (c == 'E') c = 'w';
               else if (c == 'N') c = 's';
               else if (c == 'W') c = 'e';
               else if (c == 'S') c = 'n';
               else if (c == 'D') c = 'u';
               else if (c == 'U') c = 'd';
               map[f * farmsize + r][col] = c;
            }
         }

      }
   }
   
}
