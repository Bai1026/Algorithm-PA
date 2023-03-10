#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

struct A_Edge{
    int i;
    int j;
    int w;
    bool deleted;
};

bool operator<(const A_Edge &e1, const A_Edge &e2);

class Acyclic {
public:
    Acyclic(){};
    // Acyclic(FILE *input_file, FILE *output_file);  
    void INIT(FILE *input_file, FILE *output_file);
    void cal(){};
    void END(FILE *input_file, FILE *output_file);

    void dfs_has_cycle(const vector<vector<int>>& adj_list, bool &ans);
    void dfs_visit(const vector<vector<int>>& adj_list, char *color, const int& cur, bool &ans);
    bool is_connected(const vector<vector<int>>& adj_list);
    int find(const int &x);

private:
    int V, E;
    int *disjoint_set;
};

