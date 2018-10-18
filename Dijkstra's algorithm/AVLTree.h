#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

//#include "Drawable.h"
#include "AVLTreeIterator.h"
//#include "Line.h"

#include "String.h"
using CSC2110::String;

#include <iostream>
using namespace std;

template < class T >
class AVLTree
{
   
   private:
      AVLTreeNode<T>* root;

      bool avlFlag;
      int sze;

      bool allow_duplicates;
      bool duplicates_on_left;
      bool min_or_max;

      int (*compare_item) (T* item_1, T* item_2);

      void setRootNode(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* getRootNode();
      int getHeight(AVLTreeNode<T>* tNode);
      int isBalanced(AVLTreeNode<T>* tNode);

      void destroyItem(AVLTreeNode<T>* tNode);
      void destroy();


      AVLTreeNode<T>* removeItem(AVLTreeNode<T>* tNode, T* item);


      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);
      AVLTreeNode<T>* removeNode(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* removeLeftMost(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* removeRightMost(AVLTreeNode<T>* tNode);
      T* findLeftMost(AVLTreeNode<T>* tNode);
      T* findRightMost(AVLTreeNode<T>* tNode);

      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);

      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixRemoveLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixRemoveRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left);
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right);


   public:
      AVLTree(int (*comp_item) (T* item_1, T* item_2));
      AVLTree(bool min_or_max, bool allow_duplicates, bool duplicates_on_left, int (*comp_item) (T* item_1, T* item_2));
      ~AVLTree();

      int size();
      void insert(T* item);
      T* remove();  //removes and returns the smallest/largest item in the tree based on booleans passed to the constructor

      bool isEmpty();
      void makeEmpty();

      T* getRootItem();
      AVLTreeIterator<T>* iterator();

      int getHeight();
      bool isBalanced();

      void decrease(T* item);


};


template < class T >
AVLTree<T>::AVLTree(bool min_max, bool allow_dupes, bool dupes_on_left, int (*comp_item) (T* item_1, T* item_2))
{
   root = NULL;
   sze = 0;

   compare_item = comp_item;

   allow_duplicates = allow_dupes;
   duplicates_on_left = dupes_on_left;
   min_or_max = min_max;
}

template < class T >
AVLTree<T>::AVLTree(int (*comp_item) (T* item_1, T* item_2))
{
   root = NULL;
   sze = 0;

   compare_item = comp_item;

   allow_duplicates = false;
   duplicates_on_left = true;
   min_or_max = true;
}

template < class T >
AVLTree<T>::~AVLTree()
{
   destroy();
}

template < class T >
T* AVLTree<T>::remove()
{
   T* item = NULL;
   if (root == NULL) return item;

   AVLTreeNode<T>* subtree;
   sze--;

   if (min_or_max)
   {
      item = findLeftMost(root);
      subtree = removeLeftMost(root);
      root = subtree;  //assigning a new root will not affect balancing
   }

   else
   {
      item = findRightMost(root);
      subtree = removeRightMost(root);
      root = subtree;
   }

   avlFlag = false;
   return item;
}

template < class T >
T* AVLTree<T>::findLeftMost(AVLTreeNode<T>* tNode)
{
   while (tNode->getLeft() != NULL)
   {
      tNode = tNode->getLeft();
   }

   return tNode->getItem();
}

template < class T >
T* AVLTree<T>::findRightMost(AVLTreeNode<T>* tNode)
{
   while (tNode->getRight() != NULL)
   {
      tNode = tNode->getRight();
   }

   return tNode->getItem();
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeLeftMost(AVLTreeNode<T>* tNode) 
{
   AVLTreeNode<T>* subtree;

   if (tNode->getLeft() == NULL) 
   {
      avlFlag = true;
      subtree = tNode->getRight();
      delete tNode;
      return subtree;
   }
   else 
   {
      subtree = removeLeftMost(tNode->getLeft());
      tNode->setLeft(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveLeft(tNode);
      }
      return tNode;
   }  
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeRightMost(AVLTreeNode<T>* tNode) 
{
   AVLTreeNode<T>* subtree;

   if (tNode->getRight() == NULL) 
   {
      avlFlag = true;
      subtree = tNode->getLeft();
      delete tNode;
      return subtree;
   }
   else 
   {
      subtree = removeRightMost(tNode->getRight());
      tNode->setRight(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);
      }
      return tNode;
   }  
}

template < class T >
void AVLTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool AVLTree<T>::isEmpty()
{
   return (sze == 0);
}

template < class T >
int AVLTree<T>::size()
{
   return sze;
}

template < class T >
void AVLTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
   return root;
}

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T* AVLTree<T>::getRootItem()
{
   T* root_item = root->getItem();
   return root_item;
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
   return new AVLTreeIterator<T>(root);
}


template < class T >
void AVLTree<T>::insert(T* item)
{
   root = insertItem(root, item);
   avlFlag = false;
} 

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item) 
{
   if (tNode == NULL) 
   {
      tNode = new AVLTreeNode<T>(item);
      tNode->setBalanceFactor(BALANCED);
      avlFlag = true; //need to check
      sze++;
      return tNode;
   } 

   AVLTreeNode<T>* subtree;
   T* node_item = tNode->getItem();
   int comp = (*compare_item) (item, node_item);

   if (comp == 0)
   {

      if (allow_duplicates)
      {
         if (duplicates_on_left)
         {
            subtree = insertItem(tNode->getLeft(), item);
            tNode->setLeft(subtree);

            //check balance factor and rotate if necessary
            if (avlFlag)
            {
               tNode = avlFixAddLeft(tNode);
            }
         }
         else
         {
            subtree = insertItem(tNode->getRight(), item);
            tNode->setRight(subtree);

            //check balance factor and rotate if necessary
            if (avlFlag)
            {
               tNode = avlFixAddRight(tNode);  //came from the right
            }
         }
      }

      //no duplicate search keys allowed, so do nothing
      else
      {
         return tNode;
      }
   }
   else if (comp < 0) 
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);

      //check balance factor and rotate if necessary
      if (avlFlag)  //still need to check
      {
         tNode = avlFixAddLeft(tNode);  //came from the left
      }
   }
   else 
   { 
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);

      //check balance factor and rotate if necessary
      if (avlFlag)
      {
         tNode = avlFixAddRight(tNode);  //came from the right
      }
   } 
   return tNode;
} 




template < class T >
AVLTreeNode<T>* AVLTree<T>::removeNode(AVLTreeNode<T>* tNode) 
{
   T* replacement_item;

   // test for a leaf --  this test is taken care of by the next two
   if ((tNode->getLeft() == NULL) && (tNode->getRight() == NULL)) 
   {
      delete tNode;
      return NULL;
   }  

   // test for no left child
   else if (tNode->getLeft() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   } 

   // test for no right child
   else if (tNode->getRight() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }  

   // there are two children:
   // retrieve and delete the inorder successor
   else 
   {
      replacement_item = findLeftMost(tNode->getRight());
      tNode->setItem(replacement_item);
      tNode->setRight(removeLeftMost(tNode->getRight()));
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);  //came from right
      }
      return tNode;
   }  
}

template < class T >
bool AVLTree<T>::isBalanced()
{
    int bal = isBalanced(getRootNode());
    if (bal == -1)
    {
       return false;
    }
    return true;
}

template < class T >
int AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return 0;
   }

   int balance = -1;
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* right = tNode->getRight();

   int left_height = isBalanced(left);
   int right_height = isBalanced(right);

   if (left_height != -1  &&  right_height != -1)
   {
       int bal = left_height - right_height;
       if (bal < 0) bal = bal * -1;
       if (bal <= 1)
       {
           if (left_height >= right_height)
           {
               balance = left_height + 1;
           }
           else
           {
               balance = right_height + 1;
           }
       }
   }
   return balance;
}

template < class T >
int AVLTree<T>::getHeight()
{
   int height = getHeight(root);
   return height;
}

template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
   int height;
   int right_height;

   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       height = getHeight(tNode->getLeft());
       right_height = getHeight(tNode->getRight());

       if (right_height > height)
       {
           height = right_height;
       }

       return height + 1;
   }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* rightleft = right->getLeft();

   tNode->setRight(rightleft);
   right->setLeft(tNode);

   return right;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* leftright = left->getRight();

   tNode->setLeft(leftright);
   left->setRight(tNode);

   return left;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* temp = rotateLeft(left);
   tNode->setLeft(temp);
   temp = rotateRight(tNode);
   return temp;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* temp = rotateRight(right);
   tNode->setRight(temp);
   temp = rotateLeft(tNode);
   return temp;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left)
{
   AVLTreeNode<T>* leftRight = left->getRight();
   AVL LRBF = leftRight->getBalanceFactor();
   leftRight->setBalanceFactor(BALANCED);

   if (LRBF == RIGHT_HEAVY)
   {
      left->setBalanceFactor(LEFT_HEAVY);
   }
   else if (LRBF == LEFT_HEAVY)
   {
      tNode->setBalanceFactor(RIGHT_HEAVY);    
   }

   tNode = DLR(tNode);
   //cout << "DLR" << endl;
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right)
{
   AVLTreeNode<T>* rightLeft = right->getLeft();
   AVL RLBF = rightLeft->getBalanceFactor();
   rightLeft->setBalanceFactor(BALANCED);

   if (RLBF == RIGHT_HEAVY)
   {
      tNode->setBalanceFactor(LEFT_HEAVY);
   }
   else if (RLBF == LEFT_HEAVY)
   {
      right->setBalanceFactor(RIGHT_HEAVY);
   }

   tNode = DRL(tNode);
   //cout << "DRL" << endl;
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
   tNode->insertLeft();
   AVL factor = tNode->getBalanceFactor();

   if (factor == BALANCED)
   {
      avlFlag = false; //no more to do this time around
   }
   else if (factor == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* left = tNode->getLeft();
      AVL LBF = left->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      left->setBalanceFactor(BALANCED);

      //DLR
      if (LBF == RIGHT_HEAVY)
      {
         tNode = DLR(tNode, left);
      }
      //SR
      else 
      {
         tNode = rotateRight(tNode);
         //cout << "SR" << endl;
      }

      avlFlag = false; //basically, stop checking (return the replacement node for this position)
   }
  
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
   tNode->insertRight();
   AVL factor = tNode->getBalanceFactor();

   if (factor == BALANCED)
   {
      avlFlag = false; //no more to do this time around
   }
   else if (factor == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* right = tNode->getRight();
      AVL RBF = right->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      right->setBalanceFactor(BALANCED);

      //DRL
      if (RBF == LEFT_HEAVY)
      {
         tNode = DRL(tNode, right);
      }

      //SL
      else 
      {
         tNode = rotateLeft(tNode);
         //cout << "SL" << endl;
      }

      avlFlag = false; //basically, stop checking (return the replacement node for this position)
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveLeft(AVLTreeNode<T>* tNode)
{
   tNode->removeLeft();
   AVL factor = tNode->getBalanceFactor();

   if (factor == RIGHT_HEAVY)  //was BALANCED, so completely done for this delete
   {
      avlFlag = false;
   }
   else if (factor == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* right = tNode->getRight();
      AVL RBF = right->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      right->setBalanceFactor(BALANCED);

      if (RBF == BALANCED)  //can't happen for insert, only delete
      {
         tNode->setBalanceFactor(RIGHT_HEAVY);
         right->setBalanceFactor(LEFT_HEAVY);
         tNode = rotateLeft(tNode);
         avlFlag = false;  //STOP
         //cout << "SL0" << endl;
      }
      else if (RBF == RIGHT_HEAVY)
      {
         tNode = rotateLeft(tNode);
         //cout << "SL" << endl;
         //KEEP GOING
      }
      else
      {
         tNode = DRL(tNode, right);
      }
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveRight(AVLTreeNode<T>* tNode)
{
   tNode->removeRight();
   AVL factor = tNode->getBalanceFactor();

   if (factor == LEFT_HEAVY)  //was BALANCED, so completely done for this delete
   {
      avlFlag = false;
   }
   else if (factor == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* left = tNode->getLeft();
      AVL LBF = left->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      left->setBalanceFactor(BALANCED);

      if (LBF == BALANCED)  //can't happen for insert, only delete
      {
         tNode->setBalanceFactor(LEFT_HEAVY);
         left->setBalanceFactor(RIGHT_HEAVY);
         tNode = rotateRight(tNode);
         avlFlag = false;  //STOP
         //cout << "SR0" << endl;
      }
      else if (LBF == LEFT_HEAVY)
      {
         tNode = rotateRight(tNode);
         //cout << "SR" << endl;
         //KEEP GOING
      }
      else 
      {
         tNode = DLR(tNode, left);
      }
   }

   return tNode;
}


template < class T >
void AVLTree<T>::decrease(T* item)
{
   root = removeItem(root, item);
   avlFlag = false;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeItem(AVLTreeNode<T>* tNode, T* item) 
{
   AVLTreeNode<T>* subtree;
   if (tNode == NULL) 
   {
      return tNode;  //item not present, take no action
   }

   T* node_item = tNode->getItem();
   int comp = (*compare_item) (item, node_item);

   if (comp == 0) 
   {
      //item is in the root of the subtree
      //found something to remove so set avlFlag to true
      avlFlag = true;
      tNode = removeNode(tNode);  // delete the item
      sze--;
   }
   else if (comp < 0) 
   {
      subtree = removeItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveLeft(tNode);  //came from left
      }
   }
   else 
   { 
      subtree = removeItem(tNode->getRight(), item);
      tNode->setRight(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);  //came from right
      }
   }  

   return tNode;
} 


#endif
