#if !defined ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream>
#include <iomanip>

#include "Vertex.h"
#include "Edge.h"

#include "QueueLinked.h"
using CSC2110::QueueLinked;

#include "ListArray.h"
using CSC2110::ListArray;

#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

using namespace std;

class AdjacencyList
{
	private:
		int sz;

	public:
		QueueLinked<Vertex>** adjacency_list;
		QueueLinked<Edge>** adjacency_list_edge;
		
		AdjacencyList(int sz);
		Vertex* dequeue();
		void addFirstItemsToAdjacency_list(ListArray<Vertex>* first_items);
		void addToadjacency_list(ListArray<Vertex>* vertices, ListArray<Edge>* added_edges);
		int size();

		void addForUndirected(Vertex* src, Vertex* des);
		
};

AdjacencyList::AdjacencyList(int sz)
{
	this->adjacency_list = new QueueLinked<Vertex>*[sz]();
	this->adjacency_list_edge = new QueueLinked<Edge>*[sz]();
	this->sz = sz;
}

int AdjacencyList::size()
{
	return this->sz;
}

void AdjacencyList::addFirstItemsToAdjacency_list(ListArray<Vertex>* first_items)
{
	for(int i = 1; i <= this->size(); i++)
	{
		QueueLinked<Vertex>* first_vertices = new QueueLinked<Vertex>();
		Vertex* vertex_first = first_items->get(i);
		first_vertices->enqueue(vertex_first);
		this->adjacency_list[i - 1] = first_vertices;
		QueueLinked<Edge>* edges = new QueueLinked<Edge>();
		this->adjacency_list_edge[i - 1] = edges;
	}
}

void AdjacencyList::addToadjacency_list(ListArray<Vertex>* vertices, ListArray<Edge>* edges)
{
	int count = 0;
	for(int i = 0; i < this->size(); i++)
	{
		Vertex* vertex_first = this->adjacency_list[i]->peek();
		
			for(int j = 1; j <= edges->size(); j++)
			{
				Edge* edge_added = edges->get(j);
					
				Vertex* source = edge_added->getSourceVertex();
				if(vertex_first->compareVertices(source) == 0)
				{
					//edge_added->displayEdge();
					this->adjacency_list_edge[i]->enqueue(edge_added);
					count++;
					//addForUndirected(source, vertex); //When the lie is commented out, and if the input edges are directed, it will create a directed adj list. 
				}	
			}

		
	}
	cout << "COUNT " << count;
/*
	for(int i = 0; i < this->size(); i++)
	{
		Vertex* vertex_first = this->adjacency_list[i]->peek();
		
				for(int j = 1; j <= edges->size(); j++)
				{
					Edge* edge_added = edges->get(j);
					
					Vertex* source = edge_added->getSourceVertex();
					if(vertex_first->compareVertices(source) == 0)
					{
						Vertex* destination = edge_added->getDestinationVertex();

						for(int r = 1; r <= vertices->size(); r++ && destination != NULL)
						{
							Vertex* vertex = vertices->get(r);

							if(vertex->compareVertices(destination) == 0)
							{
								edge_added->displayEdge();
								//this->adjacency_list[i]->enqueue(vertex);
								this->adjacency_list_edge[i]->enqueue(edge_added);
								//addForUndirected(source, vertex); //When the lie is commented out, and if the input edges are directed, it will create a directed adj list. 

							}	
						}	
					}	
				}

		
	}
*/

/*
	for(int i = 0; i < vertices->size(); i++)
	{
		while(!(this->adjacency_list_edge[i]->isEmpty()))
		{
			Edge* edge = adjacency_list_edge[i]->dequeue();
			edge->displayEdge();
		}
		cout << endl << endl;
	}
*/
}


void AdjacencyList::addForUndirected(Vertex* src0, Vertex* des4)
{
	for(int i = 0; i < this->size(); i++)
	{
		Vertex* vertex_first = this->adjacency_list[i]->peek();
		
		if(vertex_first->compareVertices(des4) == 0)
		{
				for(int j = 0; j < this->size(); j++)
				{
					Vertex* added = this->adjacency_list[j]->peek();

					if(added->compareVertices(src0) == 0)
					{
						this->adjacency_list[i]->enqueue(added);
					}	
						
				}
		}
						
	}
}
/*
void AdjacencyList::addToadjacency_list(ListArray<Vertex>* vertices, ListArray<Edge>* edges)
{

	for(int i = 0; i < this->size(); i++)
	{
		Vertex* vertex_first = this->adjacency_list[i]->peek();
		
				for(int j = 1; j <= edges->size(); j++)
				{
					Edge* edge_added = edges->get(j);
					
					Vertex* source = edge_added->getSourceVertex();
					if(vertex_first->compareVertices(source) == 0)
					{
						Vertex* destination = edge_added->getDestinationVertex();

						for(int r = 1; r <= vertices->size(); r++ && destination != NULL)
						{
							Vertex* vertex = vertices->get(r);

							if(vertex->compareVertices(destination) == 0)
							{
								this->adjacency_list[i]->enqueue(vertex);
								//this->adjacency_list_edge[i]->enqueue(edge_added);
								//addForUndirected(source, vertex); //When the lie is commented out, and if the input edges are directed, it will create a directed adj list. 

							}	
						}	
					}	
				}

		
	}



	for(int i = 0; i < vertices->size(); i++)
	{
		Vertex* vertex = adjacency_list[i]->dequeue();
		vertex->displayVertex();
		while(!(this->adjacency_list[i]->isEmpty()))
		{
			cout << "  ----->  ";
			Vertex* vertex = adjacency_list[i]->dequeue();
			vertex->displayVertex();
		}
		cout << endl << endl;
	}
		
}*/
#endif