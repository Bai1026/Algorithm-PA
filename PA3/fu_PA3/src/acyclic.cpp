#include "acyclic.h"

bool operator<(const A_Edge &e1, const A_Edge &e2){
    return e1.w > e2.w;
}

Acyclic::Acyclic(FILE *input_file, FILE *output_file){
    // Initialization
    const int err = fscanf(input_file, "%d %d", &V, &E);
    // Tree represents vertex parent
    vector<vector<int> > adj_list(V);
    A_Edge* edge = new A_Edge[E];
    disjoint_set = new int [V];

    for (int i = 0; i < E; ++i){
        const int _err = fscanf(input_file, "%d %d %d", &(edge[i].i), &(edge[i].j), &(edge[i].w));
        edge[i].deleted = false;
    }

    // Add positive weight edges as long as it is acyclic
    int consider = 0;
    sort(edge, edge + E);
    for (consider = 0; consider < E && edge[consider].w >= 0; ++consider){
        adj_list[edge[consider].i].push_back(edge[consider].j);
        bool creates_cycle = false;
        dfs_has_cycle(adj_list, creates_cycle);
        edge[consider].deleted = creates_cycle;
        if (creates_cycle)
            adj_list[edge[consider].i].pop_back();
    }

    for (int i = consider; i < E; ++i)
        edge[i].deleted = true;
    // Add negetive weight edges until graph is connected
    for (; consider < E && !is_connected(adj_list); ++consider){
        adj_list[edge[consider].i].push_back(edge[consider].j);
        bool creates_cycle = false;
        dfs_has_cycle(adj_list, creates_cycle);
        edge[consider].deleted = creates_cycle;
        if (creates_cycle)
            adj_list[edge[consider].i].pop_back();
    }

    char buffer[32];
    int cost = 0;
    for (int i = 0; i < E; i++)
        if (edge[i].deleted)
            cost += edge[i].w;
    sprintf(buffer, "%d\n", cost);
    fputs(buffer, output_file);
    for (int i = 0; i < E; i++)
        if (edge[i].deleted){
            sprintf(buffer, "%d %d %d\n", edge[i].i, edge[i].j, edge[i].w);
            fputs(buffer, output_file);
        }
}

void Acyclic::dfs_has_cycle(const vector<vector<int>>& adj_list, bool &ans){
    char color[V];
    for (int i = 0; i < V; ++i)
        color[i] = 'w';
    for (int i = 0; i < V; ++i){
        if (color[i] == 'w')
            dfs_visit(adj_list, color, i, ans);
        if (ans)
            return;
    }
}

void Acyclic::dfs_visit(const vector<vector<int>>& adj_list, char *color, const int& cur, bool &ans){
    if (ans)
        return;
    color[cur] = 'g';
    for (int i = 0; i < adj_list[cur].size(); ++i){
        if (color[adj_list[cur][i]] == 'w'){
            dfs_visit(adj_list, color, adj_list[cur][i], ans);
            continue;
        }
        if (color[adj_list[cur][i]] == 'g'){
            ans = true;
            return;
        }
    }
    color[cur] = 'b';
}

bool Acyclic::is_connected(const vector<vector<int>>& adj_list){
    for (int i = 0; i < V; i++)
        disjoint_set[i] = i;
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < adj_list[i].size(); j++)
            merge(i, adj_list[i][j]);
    for (int i = 0; i < V - 1; ++i)
        if (find(i) != find(i + 1))
            return false;
    return true;
}

int Acyclic::find(const int &x){
    return x == disjoint_set[x] ? x : disjoint_set[x] = find(disjoint_set[x]);
}

void Acyclic::merge(const int &x, const int &y){
    disjoint_set[find(x)] = find(y);
}