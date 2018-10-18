#include <iostream>


#include "Graph.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Edge.h"
#include "AdjacencyList.h"

#include "ListArray.h"
using CSC2110::ListArray;

#include"QueueLinked.h"
using CSC2110::QueueLinked;

#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include"QueueLinked.h"
using CSC2110::QueueLinked;

using namespace std;

int main(int argc, char *argv[])
{
	//Insert every city into the list array

	Graph* graph = new Graph(0);
	
	/*
	graph->readVertices("vertex_file.txt");//argv[1]);
	graph->readEdges("edge_file.txt");//argv[2]);
	
	graph->readVertices("romanian_cities.txt");
	graph->readEdges("romanian_mileages.txt");
	*/
	graph->readVertices("abc.txt");//argv[1]);
	graph->readEdges("abcVertex.txt");

	/*
	graph->readVertices(argv[1]);
	graph->readEdges(argv[2]);*/

	// PRIMS
	QueueLinked<Edge>* prim = graph->PRIM();
	
	cout << endl << "PRIMS" << endl;
	cout << "------------------------------" << endl;
	while(!(prim->isEmpty()))
	{
		Edge* edge = prim->dequeue();
		edge->displayEdge();
	}
	cout << "------------------------------" << endl;

	// KRUSKAL
	graph->resetStatus();
	QueueLinked<Edge>* kruskal = graph->KRUSKAL();
	
	cout << endl << "KRUSKAL" << endl;
	cout << "------------------------------" << endl;
	while(!(kruskal->isEmpty()))
	{
		Edge* edge = kruskal->dequeue();
		edge->displayEdge();
	}
	cout << "------------------------------" << endl;

	/*
	// DJKSTRA
	graph->resetStatus();
	QueueLinked<Vertex>* djkstra = graph->DJKSTRA(argv[3], argv[4]);
	cout << endl << "DJKSTRA" << endl;
	cout << "Travel from " << argv[3] << " to " << argv[4] << endl;
	cout << "------------------------------" << endl;
	int totalCost;

	while(!(djkstra->isEmpty()))
	{
		Vertex* vertex = djkstra->dequeue();
		vertex->displayShortestPath();
		totalCost = vertex->getShortestPath();
	}
	cout << "TOTAL COST: " << totalCost << endl;
	cout << "------------------------------" << endl;
	*/
	/*
	// DFS
	//QueueLinked<Vertex>* dfs = graph->DFS();
	//QueueLinked<Vertex>* topo = graph->topological_sort();
	/*cout << endl << "DFS" << endl;
	cout << "------------------------------" << endl;
	while(!(dfs->isEmpty()))
	{
		Vertex* vertex = dfs->dequeue();
		vertex->displayVertex();
	}

	// TOPOLOGICAL SORT
	cout << endl << "TOPOLOGICAL SORT" << endl;
	cout << "------------------------------" << endl;
	while(!(topo->isEmpty()))
	{
		Vertex* vertex = topo->dequeue();
		vertex->displayVertex();
	}

	// BFS
	cout << endl << "BFS" << endl;
	cout << "------------------------------" << endl;
	QueueLinked<Vertex>* bfs = graph->BFS();	
	while(!(bfs->isEmpty()))
	{
		Vertex* vertex = bfs->dequeue();
		vertex->displayVertex();
	}*/
	


	cout << endl << "Thank you!" << endl;

	cin.get();

	return 0;
}
