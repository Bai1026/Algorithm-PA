#ifndef _DISJOINTSET_H_
#define _DISJOINTSET_H_
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
struct set
{
	int parent;
	int rank;
};

class DisjoinSet
{
public:
	DisjoinSet(uint32_t&);
	~DisjoinSet();
	void makeSet();
	int find(int&) const;
	void Union_by_rank(int&, int&);

private:
	uint32_t _nSubset = 0;
	set* _subset;
};
#endif //_DISJOINTSET_H_