#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <climits>

using namespace std;

void help_message() {
    cout << "Wrong input type!" << endl;
}

struct Edge {
    int start, end, weight;
};
bool operator< (Edge a, Edge b) { return a.weight < b.weight; }

int N, M;  // vertex #, edges #

int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }

    //////////// read the input file /////////////
    char type;
    int junk, start, end, weight, N, M;
    FILE * fp_in;
    FILE * fp_out;
    fp_in = fopen (argv[1], "r");
    fp_out = fopen (argv[2], "w+");

    junk = fscanf(fp_in, "%c", &type);
    junk = fscanf(fp_in, "%d", &N);
    junk = fscanf(fp_in, "%d", &M);
    
    vector<vector<int>> adj_matrix, cycle_matrix;
    vector<int> adj_submatrix, cycle_submatrix;
    adj_matrix.reserve(N);
    adj_submatrix.reserve(N);
    cycle_matrix.reserve(N);
    cycle_submatrix.reserve(N);

    for(int i = 0;i < N;i++){
       adj_submatrix.push_back(INT_MIN);
       cycle_submatrix.push_back(INT_MIN);
    }

    for(int i = 0;i < N;i++){
       adj_matrix.push_back(adj_submatrix);
       cycle_matrix.push_back(cycle_submatrix);
    }

    for(int i = 0;i < M;i++){
        junk = fscanf(fp_in, "%d", &start);
        junk = fscanf(fp_in, "%d", &end);
        junk = fscanf(fp_in, "%d", &weight);
        if(type == 'u'){
            adj_matrix[start][end] = weight;
            adj_matrix[end][start] = weight;
        }else{
            adj_matrix[start][end] = weight;
            cycle_matrix[start][end] = weight;
            cycle_matrix[end][start] = weight;
        }
    }

    if(type == 'u'){
        int Distance[N];
        int Parent[N];
        bool Visit[N];

        for(int i = 0;i < N;i++){
            Distance[i] = INT_MIN;
            Parent[i] = -1;
            Visit[i] = false;
        }
        
        //Prim's algorithm
        priority_queue<Edge> pq_Prim;
        Distance[0] = 0;
        Parent[0] = 0;
        pq_Prim.push((Edge){0, 0, 0});

        while(!pq_Prim.empty()){
            Edge now = pq_Prim.top();
            pq_Prim.pop();
            
            if(!Visit[now.end]){
                Visit[now.end] = true;
                Distance[now.end] = now.weight;
            }
            
            for(int i = 0;i < N;i++){
                if(!Visit[i] && Distance[i] < adj_matrix[now.end][i]){
                    Distance[i] = adj_matrix[now.end][i];
                    Parent[i] = now.end;
                    pq_Prim.push((Edge){now.end, i, adj_matrix[now.end][i]});
                }
            }
        }

        // construct the output file
        //disguise the edge which is in use
        for(int i = 0;i < N;i++){
            adj_matrix[Parent[i]][i] = INT_MIN;
            adj_matrix[i][Parent[i]] = INT_MIN;    
        }

        vector<Edge> output;
        output.reserve(M);
        int sum = 0;
        
        for(int i = 0;i < N;i++){
            for(int j = i + 1;j < N;j++){
                if(adj_matrix[i][j] != INT_MIN){
                    // cout << adj_matrix[i][j] << endl;
                    output.push_back((Edge){i, j, adj_matrix[i][j]});
                    sum += adj_matrix[i][j];
                }
            }
        }
        cout << sum << endl;

        

        fprintf(fp_out, "%d", sum);
        for (int i = 0; i < output.size(); i++){
                fprintf(fp_out, "\n%d %d %d", output[i].start, output[i].end, output[i].weight);
        }
        fclose(fp_in);
        fclose(fp_out);
        return 0;
        
    }else{
        int Distance[N];
        int Parent[N];
        bool Visit[N];

        for(int i = 0;i < N;i++){
            Distance[i] = INT_MIN;
            Parent[i] = -1;
            Visit[i] = false;
        }
        
        //Prim's algorithm
        priority_queue<Edge> pq_Prim;
        Distance[0] = 0;
        Parent[0] = 0;
        pq_Prim.push((Edge){0, 0, 0});

        int count = 0;
        while(!pq_Prim.empty()){
            Edge now = pq_Prim.top();
            pq_Prim.pop();

            if (adj_matrix[now.start][now.end] != INT_MIN){
                if (adj_matrix[now.end][now.start] != INT_MIN)
                    cout << "not simple" << endl;
            }
            else {
                swap(now.start, now.end);
            }
            
            if(!Visit[now.end]){
                count ++;
                cout << "start: " << now.start << ", end: " << now.end << endl;
                if (adj_matrix[now.start][now.end] != INT_MIN)
                    cout << "True exist" << endl;
                else
                    cout << "Don't exist" << endl;
                Visit[now.end] = true;
                Distance[now.end] = now.weight;
                adj_matrix[now.start][now.end] = INT_MIN;
            }
            
            for(int i = 0;i < N;i++){
                if(!Visit[i] && Distance[i] < cycle_matrix[now.end][i]){
                    Distance[i] = cycle_matrix[now.end][i];
                    Parent[i] = now.end;
                    pq_Prim.push((Edge){now.end, i, cycle_matrix[now.end][i]});
                }
            }
            // for (int i = 0; i < N; i++)
            //     cout << Parent[i] << ' ';
            // cout << endl;
            // for (int i = 0; i < N; i++)
            //     cout << Distance[i] << ' ';
            // cout << endl;
        }
        cout << count << endl;

        // construct the output file
        //disguise the edge which is in use
        // for(int i = 0;i < N;i++){
        //     adj_matrix[Parent[i]][i] = INT_MIN;
        //     adj_matrix[i][Parent[i]] = INT_MIN;    
        // }

        vector<Edge> output;
        output.reserve(M);
        int sum = 0;

        
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                if(adj_matrix[i][j] != INT_MIN){
                    // cout << adj_matrix[i][j] << endl;
                    output.push_back((Edge){i, j, adj_matrix[i][j]});
                    sum += adj_matrix[i][j];
                }
            }
        }
        cout << sum << endl;

        fprintf(fp_out, "%d", sum);
        for (int i = 0; i < output.size(); i++){
                fprintf(fp_out, "\n%d %d %d", output[i].start, output[i].end, output[i].weight);
        }
        fclose(fp_in);
        fclose(fp_out);
        return 0;
    }
}

