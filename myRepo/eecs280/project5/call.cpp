#include <iostream>
#include "dlist.h"
#include <string>
#include <cstdlib>
#define NDEBUG
using namespace std;

struct Caller {
   int timestamp;
   string name;
   string status;
   int duration;
};

int main()
{
   int events = 0;
   cin >> events;

   Dlist<Caller*> noneQ, goldQ, silverQ, platinumQ, allCallers; //queues
   string t, n, s, d; //time, name, status, duration
   while (cin >> t >> n >> s >> d)
   {
      Caller* caller_ptr = new Caller;
      caller_ptr->timestamp = atoi(t.c_str());
      caller_ptr->name = n;
      caller_ptr->status = s;
      caller_ptr->duration = atoi(d.c_str());
      allCallers.insertBack(caller_ptr);
   }

   int tick = 0;
   bool callsActive = true;
   bool agentBusy = false;
   int remainingDuration = 0;
   while (callsActive)
   {
      remainingDuration = remainingDuration - 1;
      if (remainingDuration <= 0) agentBusy = false;
      cout << "Starting tick #" << tick << endl;
      bool currentCall = true;
      while (currentCall){
         if (!allCallers.isEmpty()){
            Caller* caller_ptr = allCallers.removeFront();
            if (caller_ptr->timestamp == tick)
            {
               if (caller_ptr->status == "none")
                  cout << "Call from " << caller_ptr->name << " a regular member\n";
               else 
                  cout << "Call from " << caller_ptr->name << " a "
                       << caller_ptr->status << " member\n";
               if (caller_ptr->status == "none") noneQ.insertBack(caller_ptr);
               else if (caller_ptr->status == "gold") goldQ.insertBack(caller_ptr);
               else if (caller_ptr->status == "silver") silverQ.insertBack(caller_ptr);
               else platinumQ.insertBack(caller_ptr);
            }
            else {
               allCallers.insertFront(caller_ptr);
               currentCall = false;   
            }
         }
         else currentCall = false;
      }
      if (!agentBusy) {
         if (!platinumQ.isEmpty()){
            Caller* caller_ptr = platinumQ.removeFront();
            cout << "Answering call from " << caller_ptr->name << endl;
            remainingDuration = caller_ptr->duration;
            agentBusy = true;
            delete caller_ptr;
         }
         else if (!goldQ.isEmpty()){
            Caller* caller_ptr = goldQ.removeFront();
            cout << "Answering call from " << caller_ptr->name << endl;
            remainingDuration = caller_ptr->duration;
            agentBusy = true;
            delete caller_ptr;
         }
         else if (!silverQ.isEmpty()) {
            Caller* caller_ptr = silverQ.removeFront();
            cout << "Answering call from " << caller_ptr->name << endl;
            remainingDuration = caller_ptr->duration;
            agentBusy = true;
            delete caller_ptr;
         }
         else if (!noneQ.isEmpty()) {
            Caller* caller_ptr = noneQ.removeFront();
            cout << "Answering call from " << caller_ptr->name << endl;
            remainingDuration = caller_ptr->duration;
            agentBusy = true;
            delete caller_ptr;
         }
      }
      if (!agentBusy && allCallers.isEmpty()) callsActive = false;
      tick += 1;
   }
   return 0;
}
