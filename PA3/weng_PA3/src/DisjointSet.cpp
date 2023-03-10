#include "DisjointSet.h"

/**************************************/
/*  class DisjoinSet member functions */
/**************************************/
DisjoinSet::DisjoinSet(uint32_t& n)
	: _nSubset(n)
{
	_subset = new set[n];
	makeSet();
}

DisjoinSet::~DisjoinSet()
{
	delete[] _subset;
}

void DisjoinSet::makeSet()
{
	for(uint32_t i = 0; i < _nSubset; ++i)
	{
		_subset[i].parent = i;
		_subset[i].rank = 0;
	}
}
//apply path_compression
int DisjoinSet::find(int& i) const
{
	if(_subset[i].parent != i)
		_subset[i].parent = find(_subset[i].parent);
	return _subset[i].parent;
}

void DisjoinSet::Union_by_rank(int& i, int& j)
{
	int iRoot = find(i);
	int jRoot = find(j);
	if(_subset[iRoot].rank < _subset[jRoot].rank)
		_subset[iRoot].parent = jRoot;
	else if(_subset[iRoot].rank > _subset[jRoot].rank)
		_subset[jRoot].parent = iRoot;
	else
	{
		_subset[jRoot].parent = iRoot;
		_subset[iRoot].rank++;
	}
}