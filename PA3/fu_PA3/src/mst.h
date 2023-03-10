#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

typedef struct Edge {
    int i;
    int j;
    int w;
    bool merged;
} Edge;
bool operator<(const Edge &e1, const Edge &e2);

class MST{
public:
    MST(FILE *input_file, FILE *output_file);
private:
    int find(const int &x);
    void merge(const int &x, const int &y);

    int V;
    int E;
    int *disjoint_set;
    Edge *edge;
};