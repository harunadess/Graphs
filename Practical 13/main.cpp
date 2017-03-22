#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <iostream>
#include "Graph.h"

#define FILENAME_LEN 100

/* Test graph exists and other fun stuff */
int main1()
{
	char *file_name = new char[FILENAME_LEN];
	
	std::cout << "provide graph definition file name: " << std::flush;
	std::cin >> file_name;

	//file path processing BS
	char *path = "C:\\Users\\Jordan\\Documents\\Uni\\2nd Year\\CSC2040 - Data Structures, Algorithms and Programming Languages\\Practicals\\Practical 13\\Practical 13\\Practical 13\\";
	std::string full_path = path;
	full_path += file_name;

	const char *c_path = full_path.c_str();

	//create the graph
	Graph graph(c_path);

	int source, dest; char c;
	do
	{
		std::cout << "test if there is an edge: source dest: " << std::flush;
		std::cin >> source >> dest;
		
		if (graph.get_edge(source, dest) == 0.0)
			std::cout << "No edge" << std::endl;
		else
			std::cout << source << " " << dest 
			<< " " << graph.get_edge(source, dest) << std::endl;

		std::cout << "try another? " << std::flush;
		std::cin >> c;
	} while (c == 'y');

	delete[] file_name, path, c_path;

	return 0;
}


std::vector<int> breadth_first_search(Graph &graph, int start_vertex)
{
	//number of vertices in graph
	int num_v = graph.get_numv();

	//vertices waiting to visit
	//queue - container, elements are pushed into
	//the "back" of the container and popped from its "front"
	std::queue<int> *queue = new std::queue<int>();
	//mark vertices that have been visited
	bool *visited = new bool[num_v];
	//backtrack vector, all elements initialised to -1
	std::vector<int> backtrack(num_v, -1);

	//initialisation
	for (int n = 0; n < num_v; n++)
		visited[n] = false;

	queue->push(start_vertex);
	visited[start_vertex] = true;

	//visit all vertices in queue
	while (!queue->empty())
	{
		//take a vertex 'source' out of queue to visit
		int source = queue->front();
		queue->pop();
		//for each destination vertex adjacent to source
		int dest;
		for (int i = 0; i < num_v; i++)
		{
			dest = i;
			double currentPath = graph.get_edge(source, dest);
			if (!visited[dest] && currentPath > 0.f)
			{
				queue->push(dest);
				visited[dest] = true;

				//track the source leading to this dest
				backtrack[dest] = source;
			}
		}
	}
	delete[] visited, queue;

	return backtrack;
}

/* Breadth First Search */
int main()
{
	char *file_name = new char[FILENAME_LEN];

	std::cout << "provide graph definition file name: " << std::flush;
	std::cin >> file_name;

	//file path processing BS
	char *path = "C:\\Users\\Jordan\\Documents\\Uni\\2nd Year\\CSC2040 - Data Structures, Algorithms and Programming Languages\\Practicals\\Practical 13\\Practical 13\\Practical 13\\";
	std::string full_path = path;
	full_path += file_name;

	const char *c_path = full_path.c_str();

	//create the graph
	Graph graph(c_path);

	//breadth-first search over the graph with start vertex = 0
	std::vector<int> backtrack = breadth_first_search(graph, 0);

	//use a stack to backtrack the shortest path from
	//0 vertext any vertex v
	//stack - container, Last In First Out
	int v;
	std::cout << "input destination vertex: " << std::flush;
	std::cin >> v;

	std::stack<int> *stack = new std::stack<int>();
	while (backtrack[v] != -1)
	{
		stack->push(v);
		v = backtrack[v];
	}
	std::cout << "The shortest path from 0 is: 0 " << std::flush;
	while (!stack->empty())
	{
		std::cout << stack->top() << " " << std::flush;
		stack->pop();
	}
	std::cout << std::endl;

	delete[] file_name, stack;

	return 0;
}


void dijkstras_algorithm(Graph &graph, int start_vertex, int *backtrack, double *distance)
{
	int num_v = graph.get_numv();

	//initialisation
	//all unprocessed vertices v except start_vertex in set v_s
	//with corresponding distance and parent from start_vertex to v
	//set - containers store unique elements, always sorted
	std::set<int> v_s;
	for (int n = 0; n < num_v; n++)
		if (n != start_vertex)
			v_s.insert(n);

	for (std::set<int>::iterator itr = v_s.begin(); itr != v_s.end(); itr++)
	{
		int v = *itr;
		double w = graph.get_edge(start_vertex, v);
		distance[v] = (w > 0.) ? w : DBL_MAX;
		backtrack[v] = start_vertex;
	}
	backtrack[start_vertex] = -1;

	//search for all vertices v in v_s
	while (!v_s.empty())
	{
		//find the vertex u in v_s with the smallest distance[u]
		double min_distance = DBL_MAX;
		int u = -1;
		for (std::set<int>::iterator itr = v_s.begin(); itr != v_s.end(); itr++)
		{
			int v = *itr;
			if (distance[v] < min_distance)
			{
				min_distance = distance[v];
				u = v;
			}
		}

		//remove u from set v_s
		v_s.erase(u);

		//for all vertices v in v_s that are adjacent to u
		for (std::set<int>::iterator itr = v_s.begin(); itr != v_s.end(); itr++)
		{
			int v = *itr;
			if (graph.get_edge(u, v) != 0.0)
			{
				//distance from start_vertex to u then to v
				double d = distance[u] + graph.get_edge(u, v);
				//compared to distance from start_vertex to v
				if (d < distance[v])
				{
					distance[v] = d;
					backtrack[v] = u;
				}
			}
		}
	}
}

/* Dijkstra's Algorithm*/
int main3()
{
	char *file_name = new char[FILENAME_LEN];

	std::cout << "provide graph definition file name: " << std::flush;
	std::cin >> file_name;

	//file path processing BS
	char *path = "C:\\Users\\Jordan\\Documents\\Uni\\2nd Year\\CSC2040 - Data Structures, Algorithms and Programming Languages\\Practicals\\Practical 13\\Practical 13\\Practical 13\\";
	std::string full_path = path;
	full_path += file_name;

	const char *c_path = full_path.c_str();

	//create the graph
	Graph graph(c_path);

	//search the shortest path to all destination from start vertex 0
	double *distance = new double[graph.get_numv()];
	int *backtrack = new int[graph.get_numv()];
	dijkstras_algorithm(graph, 0, backtrack, distance);

	//show the path & distance to any destination v
	int v;
	std::cout << "input dest v: " << std::flush;
	std::cin >> v;
	std::cout << "The shortest distance from 0 is: " << distance[v] << std::endl;
	std::stack<int> stack;
	while (backtrack[v] != -1)
	{
		stack.push(v);
		v = backtrack[v];
	}
	std::cout << "The shortest path from 0 is: 0 " << std::flush;
	while (!stack.empty())
	{
		std::cout << stack.top() << " " << std::flush;
		stack.pop();
	}
	std::cout << std::endl;

	delete[] file_name, distance, backtrack, file_name;

	return 0;
}
