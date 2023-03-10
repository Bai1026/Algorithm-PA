#include "CycleBreaking.h"

/**************************************/
/*class CycleBreaking member functions*/
/**************************************/
void CycleBreaking::processing()
{
	if(_isDirected)
	{
		_graph->directed_Cycle_remove(_edgesToRemoved);
	}
	else
	{
		_graph->KruskalMST(_edgesToRemoved);
	}
	for(uint32_t i = 0; i < _edgesToRemoved.size(); ++i)
		_rmWeightSum += _edgesToRemoved[i]->weight;
	cout << "Total Rm E: " << _edgesToRemoved.size() << endl;
	cout << "Total Rm weight: " << _rmWeightSum << endl;
}
bool CycleBreaking::readFile(const char* filename)
{
	ifstream ifs(filename);
	if(!ifs.is_open())
		return false;
	uint32_t nV = 0, nE = 0;
	char type;
	ifs >> type;
	if(type == 'd')
		_isDirected = true;

	ifs >> nV;
	ifs >> nE;

	_graph = new Graph(nV, nE, _isDirected); // build the graph

	for(uint32_t k = 0; k < nE; ++k)
	{
		int i, j;
		int16_t w;
		ifs >> i >> j >> w;
		_graph->AddEdge(i, j, w);
	}

	ifs.close();
	return true;
}
bool CycleBreaking::writeFile(const char* filename)
{
	ofstream ofs(filename);
	if(!ofs.is_open())
		return false;

	if(_edgesToRemoved.empty())
		ofs << "0" << endl;
	else
	{
		ofs << _rmWeightSum << endl;
		for(uint32_t i = 0; i < _edgesToRemoved.size(); ++i)
			ofs << _edgesToRemoved[i]->u << " " << _edgesToRemoved[i]->v << " "
				<< _edgesToRemoved[i]->weight << "\n";
	}

	ofs.flush();
	ofs.close();

	delete _graph;
	return true;
}

/**************************************/
/*    class Graph member functions    */
/**************************************/
Graph::Graph(uint32_t V, uint32_t E, bool isDirected)
	: num_vertices(V)
	, num_edges(E)
	, isDirected(isDirected)
{
	cout << "Graph initialization" << endl;
	if(isDirected)
	{
		adj_list.reserve(num_vertices);
		for(uint32_t i = 0; i < num_vertices; ++i)
			adj_list[i].reserve(num_vertices);
	}
	_edges.reserve(E);
}

Graph::~Graph()
{
	if(isDirected)
	{
		for(uint32_t i = 0; i < num_vertices; ++i)
			adj_list[i].clear();
		adj_list.clear();
	}
	_edges.clear();
}
void Graph::AddEdge(const int& u, const int& v, const int16_t& w)
{
	if(isDirected)
		adj_list[u][v] = new int16_t(w);
	_edges.emplace_back(Edge(u, v, w));
}
/**************************************/
/*   Apply KruskalMST to solve case1,2  */
/**************************************/
void Graph::KruskalMST(vector<Edge*>& _edgesToRemoved)
{
	DisjoinSet ds(num_vertices);
	sort(_edges.begin(), _edges.end(), [](const Edge& e1, const Edge& e2) {
		return e1.weight > e2.weight;
	});
	for(uint32_t i = 0; i < num_edges; ++i)
	{
		int u = _edges[i].u;
		int v = _edges[i].v;
		if(ds.find(u) != ds.find(v))
		{
			ds.Union_by_rank(u, v);
		}
		else
		{
			_edgesToRemoved.emplace_back(&_edges[i]);
		}
	}
}
/**************************************/
/*            solve case3             */
/**************************************/
void Graph::directed_Cycle_remove(vector<Edge*>& _edgesToRemoved)
{
	vector<Edge*> _tmpedges;
	KruskalMST(_tmpedges); // get edges to remove
	//remove edges from original adj list
	for(size_t i = 0; i < _tmpedges.size(); ++i)
	{
		delete adj_list[_tmpedges[i]->u][_tmpedges[i]->v]; //prevent memory leak
		adj_list[_tmpedges[i]->u][_tmpedges[i]->v] = nullptr;
	}

	sort(_tmpedges.begin(), _tmpedges.end(), [](const Edge* e1, const Edge* e2) {
		return e1->weight > e2->weight;
	});
	for(uint32_t i = 0; i < _tmpedges.size(); ++i)
	{
		if(_tmpedges[i]->weight <= 0)
		{
			_edgesToRemoved.emplace_back(_tmpedges[i]);
		}
		else
		{
			adj_list[_tmpedges[i]->u][_tmpedges[i]->v] = &_tmpedges[i]->weight;
			if(find_Cycle())
			{
				_edgesToRemoved.emplace_back(_tmpedges[i]);
				adj_list[_tmpedges[i]->u][_tmpedges[i]->v] = nullptr;
			}
		}
	}
}
bool Graph::find_Cycle() const
{
	// uint8_t color[num_vertices] = {WHITE};
	vector<uint8_t> color(num_vertices, WHITE);
	for(uint32_t u = 0; u < num_vertices; ++u)
	{
		if(color[u] == WHITE && DFS(u, color))
			return true;
	}
	return false;
}
bool Graph::DFS(uint32_t& u, vector<uint8_t>& color) const
{
	color[u] = GRAY;
	for(uint32_t v = 0; v < num_vertices; ++v)
	{
		if(adj_list[u][v] == nullptr)
			continue;
		if(color[v] == WHITE && DFS(v, color))
			return true;
		else if(color[v] == GRAY)
			return true;
	}
	color[u] = BLACK;
	return false;
}