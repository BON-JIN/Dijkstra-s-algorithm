#if !defined ROOTEDTREE_H
#define ROOTEDTREE_H

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

template < class T > 
class QuickUnion
{
	private:
		int* parentsIndex;
		int* height;
		int max_size;

	public:
		QuickUnion(int size);
		void initialize();
		int root(int index);
		bool same(int x, int y);
		void unite(int x, int y);
};

template < class T > 
QuickUnion<T>::QuickUnion(int max_size)
{
	parentsIndex = new int[max_size];
	height = new int[max_size];
	this->max_size = max_size;
	this->initialize();
}

template < class T > 
void QuickUnion<T>::initialize()
{
	for(int i = 1; i <= max_size; i++)
	{
		parentsIndex[i] = i;
		height[i] = 0;
	}
}

template < class T > 
int QuickUnion<T>::root(int index)
{
	if(parentsIndex[index] == index)
	{
		return index;
	}
	else
	{
		return parentsIndex[index] = root(parentsIndex[index]);
	}
}

template < class T > 
bool QuickUnion<T>::same(int x, int y)
{
	return root(x) == root(y);
}

template < class T > 
void QuickUnion<T>::unite(int x, int y)
{
	x = root(x);
	y = root(y);

	if(x==y)
	{
		return;
	}

	if(height[x] < height[y])
	{
		parentsIndex[x] = y;
	}
	else
	{
		parentsIndex[y] = x;
		if(height[x] == height[y])
		{
			height[x]++;
		}
	}
}

#endif