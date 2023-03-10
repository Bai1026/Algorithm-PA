#include "mst.h"

bool operator<(const Edge &e1, const Edge &e2){
    return e1.w > e2.w;
}

MST::MST(
    FILE *input_file,
    FILE *output_file
){
    // Initialization
    const int err = fscanf(input_file, "%d %d", &V, &E);
    disjoint_set = new int [V];
    for (int i = 0; i < V; i++)
        disjoint_set[i] = i;
    edge = new Edge[E];
    for (int i = 0; i < E; i++){
        const int _err = fscanf(input_file, "%d %d %d", &(edge[i].i), &(edge[i].j), &(edge[i].w));
        edge[i].merged = false;
    }

    // Kruskal algorithm
    std::sort(edge, edge + E);
    for (int i = 0, j = 0; i < V - 1 && j < E; j++){
        if (find(edge[j].i) == find(edge[j].j)) continue;
        merge(edge[j].i, edge[j].j);
        edge[j].merged = true;
        ++ i;
    }

    // output result
    char buffer[32];
    int cost = 0;
    for (int i = 0; i < E; i++)
        if (!edge[i].merged)
            cost += edge[i].w;
    sprintf(buffer, "%d\n", cost);
    fputs(buffer, output_file);
    for (int i = 0; i < E; i++)
        if (!edge[i].merged){
            sprintf(buffer, "%d %d %d\n", edge[i].i, edge[i].j, edge[i].w);
            fputs(buffer, output_file);
        }
}

int MST::find(const int &x){
    return x == disjoint_set[x] ? x : disjoint_set[x] = find(disjoint_set[x]);
}

void MST::merge(const int &x, const int &y){
    disjoint_set[find(x)] = find(y);
}