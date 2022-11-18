#include <iostream>
#include "Graph.h"


static std::string engines[] = {
	"dot",
	"sfdp",
	//"neato",
	//"fdp",
	//"circo",
	//"twopi",
	//"nop",
	//"nop2",
	//"osage",
	//"patchwork",
};

void testGraph1()
{
	Graph<int> graph(
		{
			{  0,  0,  0,  0,  0,  0,  0,  0},
			{  0,  0,  0,  0,  0, 11,  8,  0},
			{  0,  1,  0, 12,  0,  0,  0,  0},
			{  0,  0,  0,  0,  6,  0,  0,  0},
			{  0,  0,  0,  0,  0,  0,  0,  7},
			{  0,  0, 13,  2,  0,  0,  0,  3},
			{  0,  0,  0,  0,  0,  2,  0,  0},
			{  0,  0,  0,  6,  0,  0,  5,  0}
		},
		true
	);

	std::cout << graph.findMinDistance(2, 1) << "\n";
	std::cout << graph.findMinDistance(2, 3) << "\n";
	std::cout << graph.findMinDistance(2, 4) << "\n";
	std::cout << graph.findMinDistance(2, 5) << "\n";
	std::cout << graph.findMinDistance(2, 6) << "\n";
	std::cout << graph.findMinDistance(2, 7) << "\n";

	for (std::string& typeEngin : engines)
	{
		std::cout << typeEngin << "\n";
		graph.createDotFile("test.dot", typeEngin);

		system("dot .\\test.dot -Tpng -o out.png");
		system(".\\out.png");
		system("pause");
	}
}

void testGraph2()
{
	Graph<int> graph(
		{
			{  0,  0,  0,  0,  0,  0,  0,  0},
			{  0,  0,  1,  0,  0, 11,  8,  0},
			{  0, 15,  0, 12,  0,  0,  0,  0},
			{  0,  0,  0,  0,  6,  1,  0,  0},
			{  0,  0,  0,  0,  0,  9,  0,  7},
			{  0,  0, 13,  2,  0,  0,  0,  3},
			{  0,  7,  0,  0,  0,  4,  0,  0},
			{  0,  0,  0,  6, 17,  0,  5,  0}
		},
		true
	);


	std::cout << graph.findMinDistance(2, 1) << "\n";
	std::cout << graph.findMinDistance(2, 3) << "\n";
	std::cout << graph.findMinDistance(2, 4) << "\n";
	std::cout << graph.findMinDistance(2, 5) << "\n";
	std::cout << graph.findMinDistance(2, 6) << "\n";
	std::cout << graph.findMinDistance(2, 7) << "\n";

	for (std::string& typeEngin: engines)
	{
		std::cout << typeEngin << "\n";
		graph.createDotFile("test.dot", typeEngin);

		system("dot .\\test.dot -Tpng -o out.png");
		system(".\\out.png");
		system("pause");
	}
}

void manipulateGraph()
{
	setlocale(LC_ALL, "ru");

	bool type = false;
	size_t size = 0;

	std::cout << "“ип графа (0 - неориентированный / 1 - ориентированный): ";
	std::cin >> type;

	std::cout << "¬ведите кол-во вершин в графе: ";
	std::cin >> size;

	Edge edge(0, 0);
	Graph<int> graph(size, type);

	std::size_t n;

	std::cout << "¬ведите кол-во ребр/дуг которые хотите добавить: ";
	std::cin >> n;

	size_t top1, top2;
	int value;
	for (size_t i = 0; i < n; i++)
	{
		std::cout << "¬ведите вершину 1: ";
		std::cin >> top1;

		std::cout << "¬ведите вершину 2: ";
		std::cin >> top2;

		std::cout << "¬ведите вес (ребра/дуги): ";
		std::cin >> value;

		edge = Edge(top1, top2);
		graph.insertEdge(edge, value);

		std::cout << "\n";
	}


	std::cout << graph << "\n";
	std::cout << "явл€етс€ ли граф св€зным: " << std::boolalpha << graph.isLinked() << "\n";

	std::cout << "¬ведите кол-во орпераций по поиску минимального пути из вершины 1 в вершину 2: ";
	std::cin >> n;

	for (size_t i = 0; i < n; i++)
	{
		std::cout << "¬ведите вершину 1: ";
		std::cin >> top1;

		std::cout << "¬ведите вершину 2: ";
		std::cin >> top2;

		std::cout << graph.findMinDistance(top1, top2) << "\n\n";
	}

	for (std::string& typeEngin : engines)
	{
		std::cout << typeEngin << "\n";
		graph.createDotFile("test.dot", typeEngin);

		system("dot .\\test.dot -Tpng -o out.png");
		system(".\\out.png");
		system("pause");
	}
}

int main()
{
	testGraph1();
	testGraph2();
	manipulateGraph();

	return 0;
}
