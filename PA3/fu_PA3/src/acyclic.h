#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct A_Edge {
    int i;
    int j;
    int w;
    bool deleted;
} A_Edge;
bool operator<(const A_Edge &e1, const A_Edge &e2);

class Acyclic {
public:
    Acyclic(FILE *input_file, FILE *output_file);
private:
    void dfs_has_cycle(const vector<vector<int>>& adj_list, bool &ans);
    void dfs_visit(const vector<vector<int>>& adj_list, char *color, const int& cur, bool &ans);
    bool is_connected(const vector<vector<int>>& adj_list);
    int find(const int &x);
    void merge(const int &x, const int &y);

    int V, E;
    int *disjoint_set;
    vector<vector<int> > *adj_list;
};