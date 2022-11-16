#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_
#define EnableUnderline "\033[4m"
#define DisableUnderline "\033[0m"
#define TYPE true
#include <queue>
#include <fstream>
#include "Matrix.h"
#include "Edge.h"

template<typename T>
class Graph : public Matrix<T>
{
public:
	Graph(size_t n);
	Graph(std::initializer_list<std::initializer_list<T>> matrix);
	~Graph() override;
	
	void insertEdge(Edge& edge, T value, bool digraph = TYPE);
	void createDotFile(std::string path, std::string type = "dot", bool digraph = TYPE);
	bool isLinked();

	size_t findMinDistance(T start, T end);

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
inline void Graph<T>::insertEdge(Edge& edge, T value, bool digraph)
{
	if (edge.top1 != edge.top2)
	{
		this->matrixArray[edge.top1][edge.top2] = value;
		if (!digraph)
		{
			this->matrixArray[edge.top2][edge.top1] = value;
		}
	}
}

template<typename T>
inline void Graph<T>::createDotFile(std::string path, std::string type, bool digraph)
{
	std::fstream file(path, std::ios_base::out);

	file << "strict ";
	
	if (digraph)
	{
		file << "digraph ";
	}
	else
	{
		file << "graph ";
	}

	file << "test {\n\tlayout = \"" << type << "\"\n\tnode[shape = circle]\n\tedge[shape = vee]\n";

	for (size_t i = 0; i < this->n; i++)
	{
		bool isLively = false;
		for (size_t j = 0; j < this->n; j++)
		{
			if (this->matrixArray[i][j] != T())
			{
				isLively = true;
				break;
			}
		}

		if (isLively == false)
		{
			continue;
		}

		for (size_t j = 0; j < this->n; j++)
		{
			if (this->matrixArray[i][j] != T())
			{
				file << "\t" << i;
				if (digraph)
				{
					file << " -> ";
				}
				else
				{
					file << " -- ";
				}
				file << j << " " << "[label = \"" << this->matrixArray[i][j] << "\"]\n";
			}
		}
	}

	file << "}";
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
	Matrix<T> matrix(this->matrixArray, this->n);

	for (size_t i = 0; i < this->n; i++)
	{
		for (size_t j = 0; j < this->n; j++)
		{
			if (matrix[i][j] != T())
			{
				matrix[j][i] = matrix[i][j];
			}
			else if (matrix[j][i] != T())
			{
				matrix[i][j] = matrix[j][i];
			}
		}
	}

	for (size_t i = 0; i < this->n; i++)
	{
		arrayNode[i] = Node{ i, false, false };
		for (size_t j = 0; j < this->n; j++)
		{
			if (matrix[i][j] != T())
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

		for (size_t i = 0; i < matrix.size(); i++)
		{
			if (matrix[index][i] != T() && arrayNode[i].isVisit == false)
			{
				queue.push(i);
				arrayNode[i].isVisit = true;
			}
		}
	}

	for (size_t i = 0; i < matrix.size(); i++)
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
inline size_t Graph<T>::findMinDistance(T start, T end)
{

	return size_t();
}


template<typename T>
std::ostream& operator<< (std::ostream& ostream, Graph<T>& graph)
{
	size_t n = graph.size();
	size_t maxWidth = 1;
	size_t maxWidthVertical = std::to_string(graph.size() - 1).size();

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
	std::string tempString(" ", maxWidthVertical);
	ostream << "  " << tempString << EnableUnderline << std::setw(2);
	for (size_t i = 0; i < n; i++)
	{
		ostream << " " << std::setw(maxWidth + 1) << i;
	}
	ostream << "\n" << DisableUnderline;

	std::stringstream stringstream(std::to_string(graph));
	std::string string;

	for (size_t i = 0; std::getline(stringstream, string, '\n'); i++)
	{
		ostream << std::setw(maxWidthVertical) << i << "|" << string;
		if (i < (graph.size() - 1))
		{
			ostream << "\n";
		}
	}

	return ostream;
}