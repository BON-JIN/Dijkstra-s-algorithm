#if !defined EDGE_H
#define EDGE_H

#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <stdlib.h>

#include "Vertex.h"

#include"QueueLinked.h"
using CSC2110::QueueLinked;

#include "ListArray.h"
using CSC2110::ListArray;

#include "ReadFile.h"
using CSC2110::ReadFile;

#include "Text.h"
using CSC2110::String;

#include "ReadFile.h"
using CSC2110::ReadFile;

using namespace std;

class Edge
{
   private:
      Vertex* src_vertex; 
      Vertex* des_vertex;
      int weight;

   public:
      Edge(Vertex* src_vertex, Vertex* des_vertex, int weight);
      ~Edge();
      int getWeight();
      void displayEdge();
      void displaySource();
      void displayDestination();

      static int compare_items(Edge* item_1, Edge* item_2);

      Vertex* getSourceVertex();
      Vertex* getDestinationVertex();
      static ListArray<Edge>* addFirstItems(ListArray<Vertex>* cities);
      static ListArray<Edge>* readEdges(const char* file_name);

};

int Edge::compare_items(Edge* item_1, Edge* item_2)
{

   if(item_1->getWeight() > item_2->getWeight())
   {
      return 1;
   }
   else 
      return -1;
}


Edge::Edge(Vertex* src_vertex, Vertex* des_vertex, int weight)
{
   this->src_vertex = src_vertex;
   this->des_vertex = des_vertex;
   this->weight = weight;
}

Edge::~Edge()
{
   delete this->src_vertex;
   delete this->des_vertex;
   //delete this->weight;
}

Vertex* Edge::getSourceVertex()
{
   return  this->src_vertex;
}

Vertex* Edge::getDestinationVertex()
{
   return  this->des_vertex;
}

int Edge::getWeight()
{
   return this->weight;
}

void Edge::displayEdge()
{
   if(src_vertex == NULL)
   {
      cout << "Source vertex is NULL ";
   }
   else
   src_vertex->displayVertex();

   cout << " -----> ";

   if(des_vertex == NULL)
   {
      cout << "Destination is NULL" << endl;
   }
   else 
   des_vertex->displayVertex();

   cout << weight << endl << endl;
}

void Edge::displaySource()
{
   src_vertex->displayVertex();
}

void Edge::displayDestination()
{
   des_vertex->displayVertex();
}

ListArray<Edge>* Edge::addFirstItems(ListArray<Vertex>* cities)
{
   ListArray<Edge>* edges = new ListArray<Edge>();   

   for(int i = 1; i <= cities->size(); i++)
   {
      Vertex* first_vertex = cities->get(i);
      Edge* edge = new Edge(first_vertex, NULL, 0);
      edges->add(i, edge);
   }

   return edges;
}


ListArray<Edge>* Edge::readEdges(const char* file_name)
{
   ListArray<Edge>* edges = new ListArray<Edge>();
   fstream infile; 
   infile.open(file_name); 

   string sc;
   string dc;
   string w;
   
   infile >> sc;
   int count = 1;

   while (!infile.eof())
   {  
      Vertex* src_vertex = new Vertex(sc);
      
      infile >> dc;
      Vertex* dis_vertex = new Vertex(dc);
      
      infile >> w;
      int weight = atoi(w.c_str());

      Edge* edge = new Edge(src_vertex, dis_vertex, weight);
      edges->add(count, edge);

      infile >> sc;
      count++;
   }
      
   infile.close();

   return edges;
}

#endif
