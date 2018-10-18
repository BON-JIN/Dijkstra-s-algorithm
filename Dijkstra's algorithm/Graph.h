#if !defined GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string> 
using namespace std;

#include "Vertex.h"
#include "Matrix.h"
#include "Edge.h"
#include "AdjacencyList.h"
#include "StackLinked.h"

#include "QuickUnion.h"

#include "AVLTree.h"

#include "ListArray.h"
using CSC2110::ListArray;

#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include"QueueLinked.h"
using CSC2110::QueueLinked;


/*
//adds a Vertex to the Graph with a unique String identifier stored at the Vertex
void addVertex(T item) 

//adds a directed Edge between the two specified vertices, with the specified weight
void addEdge(String start_vertex_key, String end_vertex_key, double edge_weight) 

//returns a List of the edges in the minimum spanning tree computed using Prim's algorithm 
(use the first vertex in the vertex list as the starting vertex)
List prim() 

//returns a List of the edges in the minimum spanning tree computed using Kruskal's algorithm
List kruskal() 

//returns the shortest path between the specified vertices
List shortestPath(String start_vertex_key, String end_vertex_key) 
*/


class Graph
{
	private:
		int max_num_vertices;
		ListArray<Vertex>* vertices;
		ListArray<Edge>* edges;
		QueueLinked<Vertex>* bfs_queue;
		QueueLinked<Vertex>* dfs_linked;
		StackLinked<Vertex>* stuck_topological;

		QueueLinked<Edge>*  MST; // Minimum spannning tree.
		ListArray<Vertex>* djkstra;

	public:

		//constructor should accept the maximum number of vertices allowed in the graph
		Graph(int maxNumVertices);
		~Graph();
		//allow items (items are identified by String search keys) to be stored in the Graph vertices
		void addVertex(Vertex* item); 

		//add a directed edge between two vertices
		//void addEdge(String start_vertex_key, String end_vertex_key, double edge_weight);

		//perform a depth first search, adding items to a linked list
		QueueLinked<Vertex>* DFS(); 
		void dfs(int** edges, int count, ListArray<Vertex>* rows);
		//perform a breadth first search, adding items to a linked list
		QueueLinked<Vertex>* BFS();
		void bfs(QueueLinked<Vertex>* visited_queue, int count, AdjacencyList* v);
		//compute a topological sort using depth first search, return null if not a dag
		QueueLinked<Vertex>* topological_sort();

		//returns a List of the edges in the minimum spanning tree computed using Prim's algorithm 
		//(use the first vertex in the vertex list as the starting vertex)
		QueueLinked<Edge>* PRIM();
		void prim(AdjacencyList* edges);

		//returns a List of the edges in the minimum spanning tree computed using KRUSKAL's algorithm 
		//(use the first vertex in the vertex list as the starting vertex)
		QueueLinked<Edge>* KRUSKAL();
		void kruskal(AVLTree<Edge>* avl);

		QueueLinked<Vertex>* DJKSTRA(string start_vertex_key, string end_vertex_key);
		QueueLinked<Vertex>* calculateShortestPath(Vertex* startVertex, Vertex* endVertex, QueueLinked<Vertex>* a);

		int size();

		void readVertices(const char* file_name);
		void readEdges(const char* file_name);
		void displayVertices();
		void displayEdges();
		int getIndex(Vertex* vertex);

		Vertex* getVertex(string key);
		int getEdge(Vertex* source, Vertex* destination);

		void resetStatus(); // To make every vertex unvisited;

		AVLTree<Vertex>* decrease(Vertex* v);
};

int Graph::getEdge(Vertex* source, Vertex* destination)
{
	for(int i = 1; i <= edges->size(); i++)
	{
		Edge* edge = edges->get(i);
		Vertex* s = edge->getSourceVertex();
		Vertex* d = edge->getDestinationVertex();
		if(s->compareVertices(source) == 0 && d->compareVertices(destination) == 0 )
		{
			return edge->getWeight();
		}
	}
}

Vertex* Graph::getVertex(string key)
{
	for(int i = 1; i <= vertices->size(); i++)
	{
		Vertex* vertex_compare = vertices->get(i);
		string vertex2 = vertex_compare->getKey();
		if(key.compare(vertex2) == 0)
		{
			return vertex_compare;			
		}
	}
	
	cout << "Cannot find it" << endl;
	
	return NULL;
}


QueueLinked<Vertex>* Graph::calculateShortestPath(Vertex* startVertex, Vertex* d, QueueLinked<Vertex>* a)
{
	Vertex* vertex = d->getPenultimateVertex();
	int test = startVertex->compareVertices(vertex);
	if(test == 0)
	{		
		a->enqueue(d);
	}
	else
	{
		a = calculateShortestPath(startVertex, vertex, a);
		a->enqueue(d);
	}

	return a;
}

QueueLinked<Vertex>* Graph::DJKSTRA(string start_vertex_key, string end_vertex_key)
{

	AVLTree<Vertex>* avl = new AVLTree<Vertex>(&Vertex::compare_items);
	QueueLinked<Vertex>* shortestPath = new QueueLinked<Vertex>();

	Vertex* startVertex = getVertex(start_vertex_key);
	startVertex->setStartVertex(); // the shortest path is stored 0;

	Vertex* endVertex = getVertex(end_vertex_key);

	if(startVertex->compareVertices(endVertex) == 0)
	{
		shortestPath->enqueue(startVertex);
		return shortestPath;
	}

	for(int i = 1; i <= vertices->size(); i++)
	{
		avl->insert(vertices->get(i));
	}


	for(int i = 1; i <= vertices->size(); i++)
	{
		Vertex* sourceVertex = avl->remove();
		sourceVertex->visit();
		
		for(int i = 1; i <= vertices->size(); i++)
		{
			Vertex* destination = vertices->get(i);
			int path = getEdge(sourceVertex, destination);

			if((sourceVertex->getShortestPath() + path < destination->getShortestPath()) && path != 0)
			{
				destination->setShortestPath(sourceVertex->getShortestPath() + path);
				destination->setPenultimateVertex(sourceVertex);
	 			avl->decrease(destination);
				avl->insert(destination);
			}
		}

	}

	
	shortestPath = calculateShortestPath(startVertex, endVertex, shortestPath);

	return shortestPath;
}


QueueLinked<Edge>* Graph::KRUSKAL()
{
	ListArrayIterator<Edge>* itr = edges->iterator();
	AVLTree<Edge>* avl = new AVLTree<Edge>(&Edge::compare_items);
	while(itr->hasNext())
	{
		Edge* edge = itr->next();
		avl->insert(edge);
	}

	kruskal(avl);

	return MST;
}

void Graph::kruskal(AVLTree<Edge>* avl)
{
	QuickUnion<Vertex>* quick_union = new QuickUnion<Vertex>(size());

	while(!avl->isEmpty())
	{
		Edge* edge = avl->remove();
		Vertex* a = edge->getSourceVertex();
		Vertex* b = edge->getDestinationVertex();
		int x = getIndex(a);
		int y = getIndex(b);


		while(quick_union->same(x,y))
		{
			edge = avl->remove();
			if(avl->isEmpty())
			{
				break;
			}
			a = edge->getSourceVertex();
			b = edge->getDestinationVertex();
			x = getIndex(a);
			y = getIndex(b);
		}

		if(!avl->isEmpty())
		{
			quick_union->unite(x,y);
			MST->enqueue(edge);
		}

	}
}

void Graph::resetStatus()
{
	ListArrayIterator<Vertex>* itr = vertices->iterator();
	while(itr->hasNext())
	{
		Vertex* vertex = itr->next();
		vertex->noVisit();
	}

	if(MST->size() > 0)
	{
		this->MST = new QueueLinked<Edge>();
	}

}

QueueLinked<Edge>* Graph::PRIM()
{
	QueueLinked<Vertex>* visited_queue = new QueueLinked<Vertex>();
	AdjacencyList* adjacency_list = new AdjacencyList(max_num_vertices);
	adjacency_list->addFirstItemsToAdjacency_list(vertices);
	adjacency_list->addToadjacency_list(vertices, edges);

	prim(adjacency_list);
	return MST;

}

void Graph::prim(AdjacencyList* v)
{
	AVLTree<Edge>* avl = new AVLTree<Edge>(&Edge::compare_items);	
	int count = 0;

	for(int i = 0; i < 6; i++)
	{
		while(!v->adjacency_list_edge[count]->isEmpty())
		{
			Edge* edge = v->adjacency_list_edge[count]->dequeue();
			avl->insert(edge);
		}

		Edge* left = avl->remove();
		while(left->getDestinationVertex()->isVisited() == 0)
		{
			left = avl->remove();
		}

		Vertex* a = left->getSourceVertex();
		Vertex* b = left->getDestinationVertex();
		a->visit();
		b->visit();

		this->MST->enqueue(left);

		count = 0;
		for(int i = 0; i < size(); i++)
		{
			if(!v->adjacency_list_edge[i]->isEmpty())
			{
				Vertex* a = left->getDestinationVertex();
				Edge* b = v->adjacency_list_edge[i]->peek();
				Vertex* c = b->getSourceVertex();
				if(a->compareVertices(c) == 0)
				count = i;			
			}
		}		
	}

}


Graph::Graph(int maxNumVertices)
{
	this->max_num_vertices = maxNumVertices;
	this->vertices = new ListArray<Vertex>();
	this->edges = new ListArray<Edge>();
	this->bfs_queue = new QueueLinked<Vertex>();
	this->dfs_linked = new QueueLinked<Vertex>();
	this->stuck_topological = new StackLinked<Vertex>();
	this->MST = new QueueLinked<Edge>();
	this->djkstra = new ListArray<Vertex>();
}

Graph::~Graph()
{
	delete &max_num_vertices;
	delete vertices;
}

int Graph::size()
{
	return max_num_vertices;
}

void Graph::addVertex(Vertex* item)
{
	vertices->add(max_num_vertices + 1, item);
	max_num_vertices = max_num_vertices + 1;
} 


void Graph::displayVertices()
{
	ListArrayIterator<Vertex>* itr = vertices->iterator();
	while(itr->hasNext())
	{
		Vertex* vertex = itr->next();
		vertex->displayVertex();
	}
}

void Graph::displayEdges()
{
	ListArrayIterator<Edge>* itr = edges->iterator();
	while(itr->hasNext())
	{
		Edge* edge = itr->next();
		edge->displayEdge();
	}
}

QueueLinked<Vertex>* Graph::DFS()
{
	Matrix* matrix = new Matrix(vertices, vertices, max_num_vertices);
	
 	matrix->displaySize();
	
	ListArray<Vertex>* rows = matrix->getRows();
	matrix->addEdges(this->edges);
	matrix->displayMatrix();
  	int** edges = matrix->getEdges();
   
	int count = 0;
	dfs(edges, count, rows);

	
	return dfs_linked;
}
void Graph::dfs(int** edges, int count, ListArray<Vertex>* rows)
{
      Vertex* vertex = rows->get(count + 1);
      dfs_linked->enqueue(vertex);
      
      for(int r = 0; r < this->size(); r++)
      {
          edges[r][count] = 0;
      }

      for(int j = 0; j <this->size(); j++)
      {          
        
        if(edges[count][j] > 0)
        {  
            edges[count][j] = 0;
            edges[j][count] = 0;
            int c = j;
            dfs(edges, c, rows);
        }
      }

      stuck_topological->push(vertex);
}


QueueLinked<Vertex>* Graph::topological_sort()
{
	QueueLinked<Vertex>* topological = new QueueLinked<Vertex>(); 
	while(!stuck_topological->isEmpty())
	{
		Vertex* vertex = stuck_topological->pop();
		topological->enqueue(vertex);
	}
	return topological;
}

int Graph::getIndex(Vertex* vertex)
{
	int index;
	for(int i = 1; i <= this->size(); i++)
	{
			Vertex* compare = vertices->get(i);
			if(vertex->compareVertices(compare) == 0)
			{
				index = i;
				return index;
			}

	}

	return -1;
}


QueueLinked<Vertex>* Graph::BFS()
{
	QueueLinked<Vertex>* visited_queue = new QueueLinked<Vertex>();

	AdjacencyList* adjacency_list = new AdjacencyList(max_num_vertices);

	adjacency_list->addFirstItemsToAdjacency_list(vertices);
	adjacency_list->addToadjacency_list(vertices, edges);
	
	
	for(int i = 0; i < this->size(); i++)
	{
		QueueLinked<Vertex>* vertex = adjacency_list->adjacency_list[i];
		if(!(vertex->isEmpty()))
		{
			Vertex* vertex = adjacency_list->adjacency_list[i]->peek();
			if(vertex->isVisited() != 0)
			{
				bfs(visited_queue, i, adjacency_list);
			}
		}

	}

	return bfs_queue;
}

void Graph::bfs(QueueLinked<Vertex>* visited_queue, int count, AdjacencyList* v)
{	
	while(!(v->adjacency_list[count]->isEmpty()))
	{
		Vertex* vertex = v->adjacency_list[count]->dequeue();
		
		if(vertex->isVisited() != 0)
		{
			vertex->visit();
			visited_queue->enqueue(vertex);
		}
	}

	Vertex* visited_vertex = visited_queue->dequeue();

	bfs_queue->enqueue(visited_vertex);
	
	
	if(!(visited_queue->isEmpty()))
	{	
		visited_vertex = visited_queue->peek();
		count = this->getIndex(visited_vertex);
	}
	else
	{
		count = -1;
	}
	
	if(count > 0)
	{
		bfs(visited_queue, count - 1, v);
	}
	
}


void Graph::readVertices(const char* file_name)
{
    string vertex_name;

    fstream infile; 
    infile.open(file_name); 
    infile >> vertex_name;
 
    Vertex* vertex = new Vertex(vertex_name);
    this->vertices->add(1, vertex);

    int index = 2;
    while (!infile.eof())
    { 
       infile >> vertex_name;    
       Vertex* vertex = new Vertex(vertex_name);
       //vertex->displayVertex();
       this->vertices->add(index, vertex);
       index++;
    }
   
   int max = this->vertices->size();
   this->max_num_vertices = max;

   infile.close();
}
void Graph::readEdges(const char* file_name)
{
	fstream infile; 
    infile.open(file_name); 
   
    string src;
    string des;
    string w;

    infile >> src;
    int index = 1;
    while (!infile.eof())
    {  
       infile >> des;
       infile >> w;

       Vertex* src_vertex = new Vertex(src);
       int x = getIndex(src_vertex);
       src_vertex = vertices->get(x);		

       Vertex* des_vertex = new Vertex(des); 
       int y = getIndex(des_vertex);
       des_vertex = vertices->get(y);	

       
       int weight = atoi(w.c_str());

       Edge* edge = new Edge(src_vertex, des_vertex, weight);
       this->edges->add(index, edge);
       index++;
       infile >> src;
    }

    infile.close();
}

#endif