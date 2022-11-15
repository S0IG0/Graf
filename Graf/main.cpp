#include <iostream>
#include "Graph.h"

int main()
{
	Graph<int> graph//(9);
	{
		{0, 1, 0, 0},
		{1, 0, 0, 0},
		{0, 0, 0, 1},
		{0, 0, 1, 0},
	};

	//Edge edge(3 - 1, 2 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(3 - 1, 1 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(3 - 1, 6 - 1);
	//graph.insertEdge(edge, 1);

	//edge = Edge(1 - 1, 4 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(4 - 1, 5 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(5 - 1, 8 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(5 - 1, 8 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(5 - 1, 7 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(8 - 1, 7 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(7 - 1, 9 - 1);
	//graph.insertEdge(edge, 1);
	//edge = Edge(7 - 1, 6 - 1);
	//graph.insertEdge(edge, 1);

	std::cout << graph << "\n";
	std::cout << graph.isLinked() << "\n";


	return 0;
}

