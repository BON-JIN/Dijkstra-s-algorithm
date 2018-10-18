#if !defined VERTX_H
#define VERTX_H

#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <math.h> 

#include"QueueLinked.h"
using CSC2110::QueueLinked;

#include "ListArray.h"
using CSC2110::ListArray;

#include "ReadFile.h"
using CSC2110::ReadFile;

#include "Text.h"
using CSC2110::String;

using namespace std;

class Vertex
{
   private:
      string vertex;
      int visited;
      int shortest_path;
      Vertex* penultimate_vertex;
      
   public:
      Vertex(string vertex);
      ~Vertex();

      void visit();
      void noVisit();
      int isVisited();
      

      static ListArray<Vertex>* readVertices(const char* file_name);

      void displayVertex();
      string getKey();
      int compareVertices(Vertex* vertex_compare);

      void setStartVertex();
      
      static int compare_items(Vertex* item_1, Vertex* item_2);
      void setShortestPath(int shortest_path);
      int getShortestPath();
      void setPenultimateVertex(Vertex* penultimate_vertex);
      void displayShortestPath();
      Vertex* getPenultimateVertex();

};

Vertex* Vertex::getPenultimateVertex()
{
   return this->penultimate_vertex;
}

void Vertex::displayShortestPath()
{
   cout << "(" << penultimate_vertex->getKey() << ", " << this->getKey() << ", " << this->getShortestPath() << ")" << endl;
}

void Vertex::setPenultimateVertex(Vertex* penultimate_vertex)
{
   this->penultimate_vertex = penultimate_vertex;
}

int Vertex::getShortestPath()
{
   return this->shortest_path;
}

void Vertex::setShortestPath(int shortest_path)
{
   this->shortest_path = shortest_path;
}

int Vertex::compare_items(Vertex* item_1, Vertex* item_2)
{

   if(item_1->getShortestPath() > item_2->getShortestPath())
   {
      return 1;
   }
   else 
      return -1;
}

Vertex::Vertex(string vertex)
{
   this->vertex = vertex;
   this->visited = -1;
   this->shortest_path = 25000; // Over length of circumference of the earth
   this->penultimate_vertex = NULL;
}

void Vertex::setStartVertex()
{
   this->setPenultimateVertex(this);
   shortest_path = 0;
}

int Vertex::isVisited()
{
   return this->visited;
}
void Vertex::noVisit()
{
   this->visited = -1;
}

void Vertex::visit()
{
   this->visited = 0;
}

Vertex::~Vertex()
{
   delete &vertex;
}
 
int Vertex::compareVertices(Vertex* vertex_compare)
{
   string vertex1 = this->getKey();
   string vertex2 = vertex_compare->getKey();
   return vertex1.compare(vertex2);
}

string Vertex::getKey()
{
   return vertex;
}

void Vertex::displayVertex()
{
   cout << vertex << " ";
}

#endif
