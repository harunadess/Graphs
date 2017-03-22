#include "Graph.h"
#include <iostream>
#include <string>

//constructor
Graph::Graph(const char *fname)
{
	ifstream fin(fname);
	if (!fin)
	{
		std::cout << "can't open: " << fname << std::endl;
		fin.close();
		exit(1);
	}

	//read number of vertices
	fin >> num_v;
	//read directed/undirected
	char c;
	fin >> c;
	if (c == 'd')
	{
		directed = true;
		//allocate space for edges (num_v x num_v)
		edges = new double*[num_v];

		for (int i = 0; i < num_v; i++)
			edges[i] = new double[num_v];

		for (int i = 0; i < num_v; i++)
			for (int j = 0; j < num_v; j++)
				edges[i][j] = 0.0;
	}
	else if (c == 'u')
	{
		directed = false;
		//first row has one element, second has two (half matrix)
		edges = new double*[num_v];

		for (int i = 0; i < num_v; i++)		//i=0, assign 1 column | i=1, assign 2 columns | i=2, assign 3 columns
			edges[i] = new double[i + 1];

		for (int i = 0; i < num_v; i++)
			for (int j = i; j >= 0; j--) //[0][0] | [1][1],[1][0] | [2][2],[2][1],[2][0]
				edges[i][j] = 0.0;
	}

	//read all edges
	int source, dest; double weight;
	while (fin >> source >> dest >> weight)
	{
		edges[source][dest] = weight;
		if (!directed && dest > source)
			edges[dest][source] = weight;
	}
	fin.close();
}

//destructor
Graph::~Graph()
{
	for (int i = 0; i < num_v; i++)
		delete[] edges[i];

	delete[] edges;
}

//return the weight between source & dest; weight = 0.0 means no edge
double Graph::get_edge(int source, int dest) const
{
	if (!directed && dest > source)
		return edges[dest][source];

	return edges[source][dest];
}