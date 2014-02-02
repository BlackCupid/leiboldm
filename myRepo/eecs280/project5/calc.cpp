#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include "dlist.h"
#define NDEBUG
using namespace std;

//EFFECTS: returns true if stack has two or more elements
//         returns false if stack has less than two elements
bool stackHasTwoOperands(Dlist<double>& stack)
{
   if (stack.isEmpty()) return false;
   double top = stack.removeFront();
   if (stack.isEmpty()){
      stack.insertFront(top);
      return false;
   }
   else{
      stack.insertFront(top);
      return true;
   }
}


int main()
{
   Dlist<double> stack;
   string s;
   while (cin >> s){
      if (isdigit(s[0])) stack.insertFront(atof(s.c_str()));
      else if (s == "+")
      {
         if (!stackHasTwoOperands(stack)) cout << "Not enough operands\n";
         else {
            double top, second;
            top = stack.removeFront();
            second = stack.removeFront();
            top += second;
            stack.insertFront(top);
         }
      } 
      else if (s == "-")
      {
         if (!stackHasTwoOperands(stack)) cout << "Not enough operands\n";
         else {
            double top, second;
            top = stack.removeFront();
            second = stack.removeFront();
            second = second - top;
            stack.insertFront(second);
         }
      }
      else if (s == "*")
      {
         if (!stackHasTwoOperands(stack)) cout << "Not enough operands\n";
         else {
            double top, second;
            top = stack.removeFront();
            second = stack.removeFront();
            top *= second;
            stack.insertFront(top);
         }
      }
      else if (s == "/"){
         if (stack.isEmpty()) cout << "Not enough operands\n";
         else { 
            double top = stack.removeFront();
            if (stack.isEmpty()){
               cout << "Not enough operands\n";
               stack.insertFront(top);
            }
            else if (top == 0){
               cout << "Divide by zero\n";
               stack.insertFront(top);
            }
            else {
               double second = stack.removeFront();
               second = second / top;
               stack.insertFront(second); 
            }
         }
      }
      else if (s == "n")
      {
         if (stack.isEmpty()) cout << "Not enough operands\n";
         else {
            double top = stack.removeFront();
            top *= -1;
            stack.insertFront(top);
         }
      }
      else if (s == "d")
      {
         if (stack.isEmpty()) cout << "Not enough operands\n";
         else {
            double top = stack.removeFront();
            stack.insertFront(top);
            stack.insertFront(top);
         }
      }
      else if (s == "r")
      {
         if (!stackHasTwoOperands(stack)) cout << "Not enough operands\n";
         else {
            double top, second;
            top = stack.removeFront();
            second = stack.removeFront();
            stack.insertFront(top);
            stack.insertFront(second);
         }
      }
      else if (s == "p"){
         if (!stack.isEmpty()) {
            double top = stack.removeFront();
            stack.insertFront(top);
            cout << top << endl;
         }
         else cout << endl;
      }
      else if (s == "c") {
         while (!stack.isEmpty()){
            stack.removeFront();
         }
      }
      else if (s == "a") {
         Dlist<double> stackCopy = stack;
         if (stackCopy.isEmpty()) cout << " ";
         while (!stackCopy.isEmpty()){
            cout << stackCopy.removeFront() << " ";
         }
         cout << endl;
      }
      else if (s == "q") {
         return 0;
      }
      else cout << "Bad input\n";
   }
   return 1;
}
