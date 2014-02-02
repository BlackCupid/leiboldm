#ifndef __DLIST_H__
#define __DLIST_H__
#include <cstddef>
#include <cassert>
/***************************************
 * Do not modify the class declarations!
 ***************************************/
template <typename T>
class Dlist {
  //OVERVIEW: a doubly-linked list
 public:

  //EFFECTS:  returns true if the list is empty
  bool isEmpty() const;

  //MODIFIES: this
  //EFFECTS:  inserts datum into the front of the list
  void insertFront(const T &datum);

  //MODIFIES: this
  //EFFECTS:  inserts datum into the back of the list
  void insertBack(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the front of the list
  T removeFront();

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the back of the list
  T removeBack();

  Dlist();                                   // ctor
  Dlist(const Dlist &l);                     // copy ctor
  Dlist &operator=(const Dlist &l);          // assignment
  ~Dlist();                                  // dtor

 private:
  struct Node {                              // A private type
    Node   *next;
    Node   *prev;
    T      datum;
  };

  Node   *first; // The pointer to the first node (0 if none)
  Node   *last;  // The pointer to the last node (0 if none)

  //MODIFIES: this
  //EFFECTS:  copies all nodes from l to this
  void copyAll(const Dlist &l);

  //MODIFIES: this
  //EFFECTS:  removes all nodes
  void removeAll();
};

/**** DO NOT MODIFY ABOVE THIS LINE *****/

/***************************************
 * Member function implementations here
 ***************************************/
template<typename T>
bool Dlist<T>::isEmpty() const
{
   if (first == 0) return true;
   if (last == 0) return true;
   else return false;
}

template<typename T>
void Dlist<T>::insertFront(const T &datum)
{
   Node* node_ptr = new Node;
   if (!isEmpty()) first->prev = node_ptr;
   node_ptr->prev = 0;
   node_ptr->next = first;
   node_ptr->datum = datum;
   if (isEmpty()) last = node_ptr;
   first = node_ptr;
}

template<typename T>
void Dlist<T>::insertBack(const T &datum)
{
   Node* node_ptr = new Node;
   if (!isEmpty()) last->next = node_ptr;
   node_ptr->prev = last;
   node_ptr->next = 0;
   node_ptr->datum = datum;
   if (isEmpty()) first = node_ptr;
   last = node_ptr;
}

template<typename T>
T Dlist<T>::removeFront()
{
   assert(first);
   T data = first->datum;
   Node* addr = first;
   if (first->next != 0) first->next->prev = 0;
   else last = 0;
   first = first->next;
   delete addr; addr = 0;
   return data;
}

template<typename T>
T Dlist<T>::removeBack()
{
   assert(last);
   T data = last->datum;
   Node* addr = last;
   if (last->prev != 0) last->prev->next = 0;
   else first = 0;
   last = last->prev;
   delete addr; addr = 0;
   return data;
}

template<typename T>
Dlist<T>::Dlist() : first(0), last(0) {}

template<typename T>
Dlist<T>::Dlist(const Dlist &l) 
{
   first = 0;
   last = 0;
   copyAll(l);   
}

template<typename T>
Dlist<T>& Dlist<T>::operator=(const Dlist &l)          // assignment
{
   copyAll(l);
   return *this;
}

template<typename T>
Dlist<T>::~Dlist()
{
   removeAll();
}

template<typename T>
void Dlist<T>::copyAll(const Dlist &l)
{
   removeAll();
   for (Node* i = l.first; i != 0; i = i->next)
   {
      Node* node_ptr = new Node;
      node_ptr->datum = i->datum;
      if (isEmpty())
      {
          node_ptr->prev = 0;
          first = node_ptr;
      }
      else{
         node_ptr->prev = last;
         last->next = node_ptr;
      }
      node_ptr->next = 0;
      last = node_ptr;
   }
}

template<typename T>
void Dlist<T>::removeAll()
{
   for (Node* i = first; i != 0; i = first)
   {
      first = i->next;
      delete i;
   }
   first = 0;
   last = 0;
}

/* this must be at the end of the file */
#endif /* __DLIST_H__ */
