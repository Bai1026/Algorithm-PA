#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stdint.h>
using namespace std;

struct A_Edge{
    int i, j, w;
    bool deleted;
};

bool operator<(const A_Edge &e1, const A_Edge &e2);

class Acyclic {
public:
    Acyclic();
    void process(FILE *, FILE *);
    void dfs(const vector<vector<int>>&, char *, const int&, bool &);
    void dfs_has_cycle(const vector<vector<int>>&, bool &);
    
    bool is_connected(const vector<vector<int>>&);
    int find(const int &);

private:
    int V, E;
    int *disjoint_set;

friend class MST; //in the check, MST would need to use Acyclic's function.
};

bool operator<(const A_Edge &e1, const A_Edge &e2){
    return e1.w > e2.w;
}

Acyclic::Acyclic(){}

void Acyclic::process(FILE *input_file, FILE *output_file){
    // Initialization
    const int err = fscanf(input_file, "%d %d", &V, &E);
    // Tree represents vertex parent
    vector<vector<int> > adj_list(V);
    A_Edge* edge = new A_Edge[E];
    disjoint_set = new int [V];

    for (uint32_t i = 0; i < E; ++i){
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

    for (uint32_t i = consider; i < E; ++i)
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
    for (uint32_t i = 0; i < E; i++)
        if (edge[i].deleted)
            cost += edge[i].w;
    sprintf(buffer, "%d\n", cost);
    fputs(buffer, output_file);
    for (uint32_t i = 0; i < E; i++)
        if (edge[i].deleted){
            sprintf(buffer, "%d %d %d\n", edge[i].i, edge[i].j, edge[i].w);
            fputs(buffer, output_file);
        }
}

void Acyclic::dfs_has_cycle(const vector<vector<int>>& adj_list, bool &ans){
    char color[V];
    for (uint32_t i = 0; i < V; ++i)
        color[i] = 'w';
    for (uint32_t i = 0; i < V; ++i){
        if (color[i] == 'w')
            dfs(adj_list, color, i, ans);
        if (ans)
            return;
    }
}

void Acyclic::dfs(const vector<vector<int>>& adj_list, char *color, const int& cur, bool &ans){
    if (ans) return;
    color[cur] = 'g';
    for (uint32_t i = 0; i < adj_list[cur].size(); ++i){
        if (color[adj_list[cur][i]] == 'w'){
            dfs(adj_list, color, adj_list[cur][i], ans);
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
    for (uint32_t i = 0; i < V; i++)
        disjoint_set[i] = i;

    for (uint32_t i = 0; i < V; ++i)
        for (uint32_t j = 0; j < adj_list[i].size(); j++)
            disjoint_set[find(i)] = find(adj_list[i][j]);

    for (uint32_t i = 0; i < V - 1; ++i)
        if (find(i) == find(i + 1))
            return true;
    return false;
}

int Acyclic::find(const int &x){
    if (x == disjoint_set[x]){
        return x;
    }
    else{
        return disjoint_set[x] = find(disjoint_set[x]);
    }
}

struct Edge {
    int u, v, w;
    bool merged;
};

bool operator<(const Edge &e1, const Edge &e2){
    return e1.w > e2.w;
}

class MST{
public:
    MST(); //constructor
    void INIT(FILE*, FILE*);
    void END(FILE*, FILE*);
    void check(char, FILE*, FILE*);

private:
    void kruskal();
    int find(const int &);
    int V, E;
    int *disjoint_set;
    Edge *edge;
};

MST::MST(){}; //constructor

void MST::INIT(FILE *input_file, FILE *output_file){
    const int err = fscanf(input_file, "%d %d", &V, &E);

    disjoint_set = new int [V];
    for (uint32_t i = 0; i < V; i++)
        disjoint_set[i] = i;

    edge = new Edge[E];

    for (uint32_t i = 0; i < E; i++){
        const int _err = fscanf(input_file, "%d %d %d", &(edge[i].u), &(edge[i].v), &(edge[i].w));
        edge[i].merged = 0; //not yet merged
    }
}

/**************************************/
/*   Apply KruskalMST to solve case1,2  */
/**************************************/
void MST::kruskal(){
    sort(edge, edge+E);

    for (uint32_t i = 0, j = 0; i < V - 1 && j < E; j++){
        if (find(edge[j].u) == find(edge[j].v))continue;
            
        disjoint_set[find(edge[j].u)] = find(edge[j].v);
        edge[j].merged = 1; //merged one
        ++i;
    }
}

void MST::END(FILE* input_file, FILE* output_file){
    char buffer[32];
    int cost = 0;
    for (uint32_t i = 0; i < E; i++)
        if (!edge[i].merged)
            cost += edge[i].w;
    sprintf(buffer, "%d\n", cost);
    fputs(buffer, output_file);

    for (uint32_t i = 0; i < E; i++)
        if (!edge[i].merged){
            sprintf(buffer, "%d %d %d\n", edge[i].u, edge[i].v, edge[i].w);
            fputs(buffer, output_file);
        }
}

int MST::find(const int &x){
    if (x == disjoint_set[x])return x;

    else return disjoint_set[x] = find(disjoint_set[x]);
}


void MST::check(char mode, FILE *input_file, FILE *output_file){
    if (mode == 'u'){
        INIT(input_file, output_file);
        kruskal();
        END(input_file, output_file);
    }
    else{
        Acyclic ac;
        ac.process(input_file, output_file);
    }
}





///////////////////////// main /////////////////////////
int main(int argc, char *argv[]){
    if (argc!=3){
        cerr << "[ERROR] Invalid parameters!\n";
	    cerr << "Usage ./bin/cb <inputfilename> <outputfilename>\n";
    	exit(EXIT_FAILURE);
    }
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w+");
    char mode;
    const int err = fscanf(input_file, "%c", &mode);

    MST mst;
    mst.check(mode, input_file, output_file);

    fclose(input_file);
    fclose(output_file);
}