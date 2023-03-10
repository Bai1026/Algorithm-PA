#ifndef _CYCLEBREAKING_H_
#define _CYCLEBREAKING_H_

#include "DisjointSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

typedef pair<int, int16_t> AdjPair;

// vertex color
#define WHITE 0
#define GRAY 1
#define BLACK 2
class Edge
{
public:
	int u; //from
	int v; //to
	int16_t weight;
	Edge(const int& f, const int& t, const int16_t& w)
		: u(f)
		, v(t)
		, weight(w)
	{ }
};
class Graph
{
public:
	Graph(uint32_t, uint32_t, bool);
	~Graph();
	void KruskalMST(vector<Edge*>&);
	void AddEdge(const int& u, const int& v, const int16_t& w);
	void directed_Cycle_remove(vector<Edge*>&);
	bool find_Cycle() const;
	bool DFS(uint32_t&, uint8_t*) const;

private:
	vector<vector<int16_t*>> adj_list;
	vector<Edge> _edges;
	uint32_t num_vertices;
	uint32_t num_edges;
	bool isDirected;
};
class CycleBreaking
{
public:
	CycleBreaking(){};
	~CycleBreaking(){};
	void processing();
	bool readFile(const char*);
	bool writeFile(const char*);
	void reportGraph() const;

private:
	bool _isDirected = false;
	int _rmWeightSum = 0;
	Graph* _graph;
	vector<Edge*> _edgesToRemoved;
};

#endif // _CYCLEBREAKING_H_