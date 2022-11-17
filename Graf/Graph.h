#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_
#define EnableUnderline "\033[4m"
#define DisableUnderline "\033[0m"
#define TYPE true
//#define DEBUG
#include <queue>
#include <fstream>
#include <algorithm>
#include "Matrix.h"
#include "Edge.h"

template<typename T>
class Graph : public Matrix<T>
{
public:
	Graph(size_t n, bool digraph = false);
	Graph(std::initializer_list<std::initializer_list<T>> matrix, bool digraph = false);
	~Graph() override;
	
	void insertEdge(Edge& edge, T value);
	void createDotFile(std::string path, std::string type = "dot");
	bool isLinked();

	std::string findMinDistance(size_t start, size_t end);

private:
	bool digraph = false;

};

#endif // !_GRAPH_H_

template<typename T>
inline Graph<T>::Graph(size_t n, bool digraph) : Matrix<T>(n), digraph(digraph)
{
}

template<typename T>
inline Graph<T>::Graph(std::initializer_list<std::initializer_list<T>> matrix, bool digraph) : Matrix<T>(matrix), digraph(digraph)
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
		if (!digraph)
		{
			this->matrixArray[edge.top2][edge.top1] = value;
		}
	}
}

template<typename T>
inline void Graph<T>::createDotFile(std::string path, std::string type)
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
			file << "\t" << i << "\n";
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
		bool isVisit = false;
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

	std::queue<size_t> queue;

	queue.push(0);
	while (!queue.empty())
	{
		size_t index = queue.front();
		arrayNode[index].isVisit = true;
		queue.pop();

		for (size_t i = 0; i < this->n; i++)
		{
			if (matrix[index][i] != T() && arrayNode[i].isVisit == false)
			{
				queue.push(i);
				arrayNode[i].isVisit = true;
			}
		}
	}

	for (size_t i = 0; i < this->n; i++)
	{
		if (arrayNode[i].isVisit == false)
		{
			delete[] arrayNode;

			return false;
		}
	}

	delete[] arrayNode;

	return true;
}

template<typename T>
inline std::string Graph<T>::findMinDistance(size_t start, size_t end)
{
	if (!((start >= 0 && start < this->n) && (end >= 0 && end < this->n) && (start != end)))
	{
		return "None";
	}

	std::stringstream stringstream;

	size_t size = this->n;
	size_t maxWeight = 0;
	Matrix<T> matrix(this->matrixArray, size);
	std::queue<size_t> queue;
	size_t* minValues = new size_t[size];
	bool* nodeIsVisit = new bool[size];

	try
	{
		for (size_t i = 0; i < size; i++)
		{
			nodeIsVisit[i] = false;
			for (size_t j = 0; j < size; j++)
			{
				maxWeight += matrix[i][j];
			}
		}
		maxWeight *= 2;

		for (size_t i = 0; i < size; i++) { minValues[i] = maxWeight; }

		minValues[start] = 0;
		queue.push(start);

		while (!queue.empty())
		{
			std::vector<size_t> indexsTops;
			size_t index = queue.front();


			queue.pop();

			if (nodeIsVisit[index] == true) { continue; }

			for (size_t i = 0; i < size; i++)
			{
				if (matrix[index][i] != T())
				{
					size_t value = minValues[index] + matrix[index][i];
					if (value < minValues[i])
					{
						minValues[i] = value;
					}
					if (nodeIsVisit[i] == false)
					{
						//queue.push(i);
						indexsTops.push_back(i);
					}
				}
			}
			nodeIsVisit[index] = true;

			//
			std::sort(indexsTops.begin(), indexsTops.end(),
				[&matrix, &index](size_t& x, size_t& y) { return matrix[index][x] < matrix[index][y]; }
			);
			for (size_t _index: indexsTops)
			{
				queue.push(_index);
			}
		}

#ifdef DEBUG
		// DEBUG
		for (size_t i = 0; i < this->n; i++)
		{
			std::cout << i << ": " << minValues[i] << "\n";
		}
		// !DEBUG
#endif // DEBUG


		for (size_t i = 0; i < this->n; i++)
		{
			for (size_t j = 0; j < i; j++)
			{
				std::swap(matrix[i][j], matrix[j][i]);
			}
		}

#ifdef DEBUG
		std::cout << matrix << "\n";
#endif // DEBUG


		if (minValues[end] == maxWeight)
		{
			delete[] nodeIsVisit;
			delete[] minValues;

			return "None";
		}

		size_t travelValue = minValues[end];
		size_t index = end;

		std::vector<size_t> travel{ end };

		while (index != start && minValues[end] != maxWeight)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (matrix[index][i] != T())
				{
					if ((travelValue - matrix[index][i]) == minValues[i])
					{
						travelValue = minValues[i];
						index = i;
						travel.push_back(index);
						break;
					}
				}
			}
		}

		std::reverse(travel.begin(), travel.end());

		for (size_t i = 0; i < travel.size(); i++)
		{
			stringstream << travel[i];

			if (i != (travel.size() - 1))
			{
				stringstream << " --{" << matrix[travel[i + 1]][travel[i]] << "}--> ";
			}
			else
			{
				stringstream << ": " << minValues[end];
			}
		}
	}
	catch (const std::exception&)
	{
		stringstream.str(std::string());
		stringstream << "None";
	}

	delete[] nodeIsVisit;
	delete[] minValues;

	return stringstream.str();
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
	ostream << " " << tempString << EnableUnderline << std::setw(2);
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