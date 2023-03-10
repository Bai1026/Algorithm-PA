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
int* color;


// bool Cycle_detect(int node) {
//   // 0 for white, 1 for gray, 2 for black
//   color[node] = 1;
//   bool adj = false;
//   for(int i = 0;i < N;i++){
//     adj = false;
//     for(int j = 0;j < g[node].size();j++){
//         if(g[node][j] == i)adj = true;
//     }

//     if(adj){
//       if (color[i] == 0){
//         if(Cycle_detect(i))return true;
//       }else if(color[i] == 1){
//         return true;
//       }
//     }
//   }
//   color[node] = 2;
//   return false;
// }
void dfs_visit(const int& node, bool &ans){
    if (ans || color[node] != 0)
        return;
    color[node] = 1;
    for (int i = 0; i < g[node].size(); ++i){
        if (color[g[node][i]] == 0)
            dfs_visit(g[node][i], ans);
        else if (color[g[node][i]] == 1)
            ans = true;
        if (ans)
            break;
    }
    color[node] = 2;
}

bool dfs(const int& N){
    bool ans = false;
    for (int i = 0; i < N; i++)
        if (color[i] == 0)
            dfs_visit(i, ans);

    return ans;
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
    color = new int[N]();

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
        if(edges[i].in_tree) {
            g[edges[i].s].push_back(edges[i].e);
        }
    }

    fclose(in);
    fclose(out);

    // for (int i = 0; i < N; ++i) {
    //     //reset the color to white
    //     for(int j = 0;j < N;j++){
    //         color[j] = 0;
    //     }
    //     if (dfs(i)) {
    //         Cycle = true;
    //     }
    // }
    for (int i = 0; i < N; i++)
        color[i] = 0;
    bool Cycle = dfs(N);
    
    if(Cycle){
        printf("Error, the graph has cycles !\n");
        return 0;
    }else{
        printf("The graph has no cycle.\n");
        return 0;
    }
}