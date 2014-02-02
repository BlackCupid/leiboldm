#include <iostream>
#include "dlist.h"
#include <cassert>
#include <string>

using namespace std;

struct Cat {
   string name;
   int age;
};

int main()
{
   Dlist<int> intList;
   intList.insertBack(1);
   intList.insertBack(2);
   intList.insertBack(3);
   intList.insertFront(0);

   Dlist<int> intList2(intList);

   cout << "cout << intList: \n";
   for (int i = 0; i < 4; i++)
   {
      int j = intList.removeFront();
      cout << j << endl;
      //assert(i == j);
   }

   cout << "cout << intList2: \n";
   for (int i = 0; i < 4; i++)
   {
      int j = intList2.removeBack();
      cout << j << endl;
   }

   Dlist<char> emptyList;
   assert(emptyList.isEmpty());

   Dlist<Cat> catList;
   Cat kitty;
   kitty.name = "kitty";
   kitty.age = 12;

   Cat whiskers;
   whiskers.name = "whiskers";
   whiskers.age = 10;

   catList.insertFront(kitty);
   catList.insertBack(whiskers);

   Cat cat;
   cat = catList.removeFront();
   cout << cat.name <<  endl;
   cat = catList.removeBack();
   cout << cat.age << endl;
   return 0;

}
