#if !defined MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "Vertex.h"
#include "Edge.h"
#include "StackLinked.h"


#include "Text.h"
using CSC2110::String;

#include "ReadFile.h"
using CSC2110::ReadFile;

#include "ListArray.h"
using CSC2110::ListArray;

#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

using namespace std;

class Matrix
{
   private:
      ListArray<Vertex>* rows;
      ListArray<Vertex>* cols;
      int size;
      int** edges;
      bool** isVisited;

   public:
      Matrix(ListArray<Vertex>* r, ListArray<Vertex>* c, int size);
      ~Matrix();

      ListArray<Vertex>* getRows();
      void displaySize();
      void displayMatrix();
      int getSize();
      void addEdges(ListArray<Edge>* edges);
      int** getEdges();
      QueueLinked<Vertex>* DFS(Matrix* matrix);
      QueueLinked<Vertex>* dfs(int** edges, QueueLinked<Vertex>* dfs, int count);
};

Matrix::Matrix(ListArray<Vertex>* r, ListArray<Vertex>* c, int size)
{
   this->rows = r;
   this->cols = c;
   this->size = size;
   this->edges = new int* [size];

   for(int i=0; i < size; i++)
   {
      edges[i] = new int [size];
   }

   for(int r = 0; r < size; r++)
   {
      for(int j = 0;  j < size; j++)
      {
         edges[r][j] = 0;
      }
   }

}

Matrix::~Matrix()
{
   delete rows;
   delete cols;
}

ListArray<Vertex>* Matrix::getRows()
{
   return this->rows;
}

void Matrix::displaySize()
{
   cout << "The size of the matrix is " << size << "x" << size << endl;
}

int Matrix::getSize()
{
   return size;
}

int** Matrix::getEdges()
{
   return this->edges;
}
void Matrix::displayMatrix()
{
   cout << endl <<  "---------------------------------------------------------------------------------------" << endl;

   for(int i = 0; i < size; i++)
   { 
      for(int j = 0; j < size; j++)
      {          
         cout << setw(6) << edges[i][j] << setw(2);
      }
      cout << endl << endl;
   }

   cout << "---------------------------------------------------------------------------------------" << endl;

}

void Matrix::addEdges(ListArray<Edge>* edges)
{
   cout << "All edges are assigned." << endl;

   ListArrayIterator<Edge>* itr = edges->iterator();

   while(itr->hasNext())
   {
      Edge* edge = itr->next();

      Vertex* src_vertex = edge->getSourceVertex();
      Vertex* des_vertex = edge->getDestinationVertex();
      int weight = edge->getWeight();
      for(int i = 1; i <= rows->size(); i++)
      {
         Vertex* row = rows->get(i);
         int compare = row->compareVertices(src_vertex);
         if(compare == 0)
         {
            //cout << "(1) Passed first test." << endl;
                  
            for(int j = 1; j <= cols->size(); j++)
            {
               Vertex* col = cols->get(j);
               //col->displayVertex();
               int compare = col->compareVertices(des_vertex);
               if(compare == 0)
               {
                  //cout << "(2) Passed second test." << endl;
                  this->edges[i - 1][j - 1] = weight;
                  this->edges[j - 1][i - 1] = weight;
                  //cout << "The weight is " << this->edges[i - 1][j - 1] << " assigned to index " << i << " and " << j << endl << endl;
               }
               
            }
         }  
      }
   }
   
}
#endif
