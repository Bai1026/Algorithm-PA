// #define DEBUG
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int N, M;  // vertex #, edges #

// edge struct
struct Edge {
    int s, e, w;
    bool in_tree;
};
bool operator<(Edge a, Edge b) { return a.w > b.w; }
Edge* edges;

// Node
vector<int>* g;
int* isVisit;

void dfs(int root) {
    // printf("%d", root);
    isVisit[root] = 1;
    for (auto& v : g[root]) {
        if (!isVisit[v]) dfs(v);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "[Usage] ./test <input file name> <output file name>\n");
        return 0;
    }
    FILE* in = fopen(argv[1], "r");   // input
    FILE* out = fopen(argv[2], "r");  // output

    // read number
    char type;
    int zero;
    fscanf(in, "%c", &type);
    // read vertices
    fscanf(in, "%d", &N);
    g = new vector<int>[N];
    isVisit = new int[N]();

    // read edges
    fscanf(in, "%d", &M);
    edges = new Edge[M];
    for (int i = 0; i < M; ++i) {
        int s, e, w;
        fscanf(in, "%d %d %d", &s, &e, &w);
        edges[i] = {s, e, w, true};
    }

    // read end
    fscanf(in, "%d", &zero);

    // read remove edges
    int total_remove;
    fscanf(out, "%d", &total_remove);
    int u, v, w;
    while (fscanf(out, "%d %d %d", &u, &v, &w) != EOF) {
        // printf("%d, %d, %d\n", u, v, w);
        for (int i = 0; i < M; ++i) {
            if (edges[i].s == u && edges[i].e == v) {  // O(E^2), may use unordered_set
                edges[i].in_tree = false;
                break;
            }
        }
    }

    // read adjacent list
    for (int i = 0; i < M; ++i) {
        if (edges[i].in_tree) {
            g[edges[i].s].push_back(edges[i].e);
            g[edges[i].e].push_back(edges[i].s);
        }
    }

    dfs(0);

    fclose(in);
    fclose(out);

    for (int i = 0; i < N; ++i) {
        if (!isVisit[i]) {
            printf("Error, there isn't only one component !\n"); // the graph is not connedted
            return 0;
        }
    }
    printf("Test OK, only one connected component\n");
}