#include <iostream>
#include "Graph.h"

int main()
{
	Graph<int> graph(7);
	//{
	//	{0, 1, 0, 0},
	//	{1, 0, 0, 0},
	//	{0, 0, 0, 1},
	//	{0, 0, 1, 0},
	//};

	/*Edge edge(3 - 1, 2 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(3 - 1, 1 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(3 - 1, 6 - 1);
	graph.insertEdge(edge, 1);

	edge = Edge(1 - 1, 4 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(4 - 1, 5 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(5 - 1, 8 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(5 - 1, 8 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(5 - 1, 7 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(8 - 1, 7 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(7 - 1, 9 - 1);
	graph.insertEdge(edge, 1);
	edge = Edge(7 - 1, 6 - 1);
	graph.insertEdge(edge, 1);

	edge = Edge(15, 16);
	graph.insertEdge(edge, 1);*/

	//Edge edge(1, 2);
	//graph.insertEdge(edge, 7);

	//edge = Edge(1, 3);
	//graph.insertEdge(edge, 9);

	//edge = Edge(1, 6);
	//graph.insertEdge(edge, 14);

	//edge = Edge(2, 3);
	//graph.insertEdge(edge, 10);

	//edge = Edge(2, 4);
	//graph.insertEdge(edge, 15);

	//edge = Edge(3, 4);
	//graph.insertEdge(edge, 11);

	//edge = Edge(3, 6);
	//graph.insertEdge(edge, 2);

	//edge = Edge(6, 5);
	//graph.insertEdge(edge, 9);

	//edge = Edge(4, 5);
	//graph.insertEdge(edge, 6);

	Edge edge(1, 2);
	graph.insertEdge(edge, 2);

	edge = Edge(1, 3);
	graph.insertEdge(edge, 5);

	edge = Edge(1, 3);
	graph.insertEdge(edge, 5);

	edge = Edge(2, 4);
	graph.insertEdge(edge, 6);

	edge = Edge(2, 5);
	graph.insertEdge(edge, 10);

	edge = Edge(3, 5);
	graph.insertEdge(edge, 8);

	edge = Edge(3, 4);
	graph.insertEdge(edge, 9);

	edge = Edge(5, 6);
	graph.insertEdge(edge, 3);

	edge = Edge(4, 6);
	graph.insertEdge(edge, 4);	

	std::cout << graph << "\n";
	std::cout << std::boolalpha << graph.isLinked() << "\n";
	graph.createDotFile("test.dot");

	std::cout << graph.findMinDistance(1, 6) << "\n";

	system("dot .\\test.dot -Tpng -o out.png");
	system(".\\out.png");

	return 0;
}

