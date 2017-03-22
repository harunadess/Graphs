#ifndef GRAPH_H
#define GRAPH_H
#include <fstream>

using std::ifstream;

class Graph
{
public:
	//constructor  -create a graph from file with the given name
	Graph(const char *fname);
	//destructor
	~Graph();

	//return the number of vertices
	int get_numv() const { return num_v; }
	//return the weight between source & dest; weight = 0.0 means no edge
	double get_edge(int source, int dest) const;

private:
	int num_v;
	bool directed;

	//2-D matrix showing edges from num_v vertices to num_v vertices
	double **edges;
};

#endif // !GRAPH_H
