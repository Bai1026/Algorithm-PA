#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class BergerShorFAS {
public:
    BergerShorFAS(
        FILE *input_file,
        FILE *output_file
    ){
        int V, E;
        const int err = fscanf(input_file, "%d %d", &V, &E);
        int vertices[V];
        bool delete_vertices[V];
        for (int i = 0; i < V; ++i){
            vertices[i] = i;
            delete_vertices[i] = false;
        }

        // first int indicates v, second int stands for weight(w)
        vector<vector<pair<int, int> > > adj_list(V);
        vector<vector<pair<int, int> > > inverse_graph(V);
        // read edges into adjecency list
        // also constructs inverse graph
        for (int i = 0; i < E; i++){
            int u, v, w;
            const int _err = fscanf(input_file, "%d %d %d", &u, &v, &w);
            adj_list[u].push_back(pair<int, int>(v, w));
            inverse_graph[v].push_back(pair<int, int>(u, w));
        }

        // starts BergerShorFAS algorithm
        random_shuffle(vertices, vertices + V);  // O(V) time
        // vector<vector<int> > removed_edge(E);
        int removed_edge[E][3];
        int cost = 0, count_rm = 0;;

        for (int i = 0; i < V; ++i)
            cout << vertices[i] << ' ';
        cout << endl;

        for (int i = 0; i < V; ++i){
            const int vertex = vertices[i];
            int in_degree = 0, out_degree = 0;
            // count out degree using original graph
            for (int j = 0; j < adj_list[vertex].size(); ++j)
                out_degree += !delete_vertices[adj_list[vertex][j].first];
            // count in degree cost using inverse graph
            for (int j = 0; j < inverse_graph[vertex].size(); ++j)
                in_degree += !delete_vertices[inverse_graph[vertex][j].first];

            cout << vertex << ' ' << in_degree << ' ' << out_degree << endl;
            if (in_degree > out_degree){
                // remove vertex out
                for (int j = 0; j < adj_list[vertex].size(); ++j)
                    if (!delete_vertices[adj_list[vertex][j].first]){
                        cout << adj_list[vertex][j].first << endl;
                        removed_edge[count_rm][0] = vertex;
                        removed_edge[count_rm][1] = adj_list[vertex][j].first;
                        removed_edge[count_rm][2] = adj_list[vertex][j].second;
                        ++ count_rm;
                        cost += adj_list[vertex][j].second;
                    }
            }
            else {
                // remove vertex in
                for (int j = 0; j < inverse_graph[vertex].size(); ++j)
                    if (!delete_vertices[inverse_graph[vertex][j].first]){
                        cout << inverse_graph[vertex][j].first << endl;
                        removed_edge[count_rm][0] = inverse_graph[vertex][j].first;
                        removed_edge[count_rm][1] = vertex;
                        removed_edge[count_rm][2] = inverse_graph[vertex][j].second;
                        ++ count_rm;
                        cost += inverse_graph[vertex][j].second;
                    }
            }
            delete_vertices[vertex] = true;
        }

        char buffer[32];
        sprintf(buffer, "%d\n", cost);
        fputs(buffer, output_file);
        // cout << cost << endl;
        for (int i = 0; i < count_rm; ++i){
            // cout << removed_edge[i][0] << ' ' << removed_edge[i][1] << ' ' << removed_edge[i][2] << endl;
            sprintf(buffer, "%d %d %d\n", removed_edge[i][0], removed_edge[i][1], removed_edge[i][2]);
            fputs(buffer, output_file);
        }
    }
};