#include "dlist.h"
#include <iostream>
#include <string>

using namespace std;

enum Job {STUDENT, FACULTY, STAFF};

struct Record {
  string name;
  string uniqname;
  Job job;
};

int main() {

  Dlist<Record*> wolverineaccess; //records are big, so store pointer

  Record* p1 = new Record;
  p1->name = "Andrew DeOrio";
  p1->uniqname = "awdeorio";
  p1->job = FACULTY;

  Record* p2 = new Record;
  p2->name = "Matt Leibold";
  p2->uniqname = "leiboldm";
  p2->job = STUDENT;

  Record* p3 = new Record;
  p3->name = "John Doe";
  p3->uniqname = "JD";
  p3->job = FACULTY;

  wolverineaccess.insertFront(p1);
  wolverineaccess.insertFront(p2);
  wolverineaccess.insertFront(p3);
  wolverineaccess.insertFront(p1);

  Dlist<Record*> NSA;
  
  NSA = wolverineaccess;

  cout << "cout << NSA: \n";
  while ( !NSA.isEmpty() ) {
    Record *r = NSA.removeFront();
    cout << r->name << " " << r->uniqname << " " << r->job << endl;
  }

  cout << "cout << wolverinaccess: \n";
  while ( !wolverineaccess.isEmpty() ) {
    Record *r = wolverineaccess.removeFront();
    cout << r->name << " " << r->uniqname << " " << r->job << endl;
  }
  delete p1; delete p2; delete p3;

  return 0;
}
