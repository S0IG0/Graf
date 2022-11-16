#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_
#define EnableUnderline "\033[4m"
#define DisableUnderline "\033[0m"
#include <queue>
#include "Matrix.h"
#include "Edge.h"

template<typename T>
class Graph : public Matrix<T>
{
public:
	Graph(size_t n);
	Graph(std::initializer_list<std::initializer_list<T>> matrix);
	~Graph() override;
	
	void insertEdge(Edge& edge, T value);
	bool isLinked();

};

#endif // !_GRAPH_H_

template<typename T>
inline Graph<T>::Graph(size_t n) : Matrix<T>(n)
{
}

template<typename T>
inline Graph<T>::Graph(std::initializer_list<std::initializer_list<T>> matrix) : Matrix<T>(matrix)
{
}

template<typename T>
inline Graph<T>::~Graph()
{
}

template<typename T>
inline void Graph<T>::insertEdge(Edge& edge, T value)
{
	if (edge.top1 != edge.top2)
	{
		this->matrixArray[edge.top1][edge.top2] = value;
		this->matrixArray[edge.top2][edge.top1] = value;
	}
}

template<typename T>
inline bool Graph<T>::isLinked()
{
	struct Node
	{
		size_t index;
		bool isVisit;
		bool isLively;
	};

	Node* arrayNode = new Node[this->n];


	for (size_t i = 0; i < this->n; i++)
	{
		arrayNode[i] = Node{ i, false, false };
		for (size_t j = 0; j < this->n; j++)
		{
			if (this->matrixArray[i][j] != T())
			{
				arrayNode[i].isLively = true;
				break;
			}
		}
	}

	std::queue<size_t> queue;

	queue.push(0);
	while (!queue.empty())
	{
		size_t index = queue.front();
		arrayNode[index].isVisit = true;
		queue.pop();

		for (size_t i = 0; i < this->n; i++)
		{
			if (this->matrixArray[index][i] != T() && arrayNode[i].isVisit == false)
			{
				queue.push(i);
				arrayNode[i].isVisit = true;
			}
		}
	}

	for (size_t i = 0; i < this->n; i++)
	{
		if (arrayNode[i].isVisit == false && arrayNode[i].isLively == true)
		{
			delete[] arrayNode;

			return false;
		}
	}

	delete[] arrayNode;

	return true;
}


template<typename T>
std::ostream& operator<< (std::ostream& ostream, Graph<T>& graph)
{
	size_t n = graph.size();
	size_t maxWidth = 1;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			size_t tempWidth = std::to_string(graph[i][j]).size();
			if (tempWidth > maxWidth)
			{
				maxWidth = tempWidth;
			}
		}
	}

	ostream << "  "  << EnableUnderline << std::setw(2) ;
	for (size_t i = 0; i < n; i++)
	{
		ostream << " " << std::setw(maxWidth + 1) << i;
	}
	ostream << "\n" << DisableUnderline;

	std::stringstream stringstream(std::to_string(graph));
	std::string string;

	for (size_t i = 0; std::getline(stringstream, string, '\n'); i++)
	{
		ostream << i << "|" << string;
		if (i < (graph.size() - 1))
		{
			ostream << "\n";
		}
	}

	return ostream;
}