#if !defined (STACKLINKED_H)
#define STACKLINKED_H

#include "NextNode.h"

template < class T >
class StackLinked
{
   private:
      NextNode<T>* top;
      int sze;  // number of items in the stack

   public:
      StackLinked();
      ~StackLinked();
      bool isEmpty();
      int size();
      void popAll();
      T* pop();
      void push(T* item);
      T* peek();
};

template < class T >
StackLinked<T>::StackLinked()
{
   top = NULL;
   sze = 0;
}

template < class T >
StackLinked<T>::~StackLinked()
{
   popAll();
}

template < class T >
bool StackLinked<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
int StackLinked<T>::size()
{
   return sze;
}

template < class T >
void StackLinked<T>::popAll()
{
   //loop over the stack, deleting the nodes
   //the actual items are not deleted
   if (sze == 0) return; 

   NextNode<T>* curr = top;
   NextNode<T>* prev = NULL;
   while (curr != NULL)
   {
      prev = curr;
      curr = curr->getNext();
      prev->setNext(NULL);
      delete prev;
   }
}

//If the top is not empty, it gets an item on the top and returns it.
template < class T >
T* StackLinked<T>::peek()
{
   T* item = NULL;
   //DO THIS
   if(isEmpty()) 
   {
      return item;
   }

   item = top->getItem(); //Get the item on the top.
   return item;
}

//Add an item on the top of the Stack.
template < class T >
void StackLinked<T>::push(T* item)
{
   //DO THIS
   NextNode<T>* node = new NextNode<T> (item); //Create a node that holds the item added.
   node->setNext(top); //The node on the top will point the next node of it.
   top = node; //The item is added on the top.
   sze++; //Item was added we need to size + 1.
}

//Basically this is a part of removing function,but it similars to peek function which returns 
//the item on the top of the stack to remove it.
template < class T >
T* StackLinked<T>::pop()
{
   if (sze == 0) return NULL; //If no item on the top, it returns NULL.

   //DO THIS
   T* item = NULL; //Create item box which will hold the removing item.
   if(sze > 0)
   {
      NextNode<T>* curr = top;
      item = top->getItem(); //Get the item on the top.
      top = top->getNext(); //The pointer of the top will point the next array of it.
      sze--; //Because we remove item, we need to decrement sz here.
      delete curr;
      return item;
   }
}

#endif
