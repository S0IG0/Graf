#pragma once
#ifndef _EDGE_H_
#define _EDGE_H_

class Edge
{
public:
	Edge(int top1, int top2);
	~Edge();

	int top1, top2;
};

#endif // !_EDGE_H_

inline Edge::Edge(int top1, int top2) : top1(top1), top2(top2)
{
}

inline Edge::~Edge()
{
}
