#include "maxPlanarSubset.h"
#include <iostream>
using namespace std;

MaxPlanarSubset::MaxPlanarSubset(void) {}

void MaxPlanarSubset::init(FILE* input_file, FILE* output_file) {
    fin = input_file;
    fout = output_file;
 
    fscanf(fin, "%d", &num_vertex);
    num_chord = num_vertex >> 1; //means /2
    chord = new int[num_vertex];
    
    for (int i = 0; i < num_chord; ++i) {
        int a, b;
        fscanf(fin, "%d %d", &a, &b);
        chord[a] = b, chord[b] = a;
    }

    Maxarr = new int*[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        Maxarr[i] = new int [num_vertex];
        for (int j = 0; j < num_vertex; ++j)
            Maxarr[i][j] = -1;
    }
    // cout << Maxarr[0][0] << endl;
}

int MaxPlanarSubset::Max_cal(const int& i, const int& j) {
    if (i >= j) //default is i < j
        return 0;

    if (Maxarr[i][j] != -1)
        return Maxarr[i][j]; //memoization

    const int k = chord[j];
    if (k > j || k < i){ //case 1
        Maxarr[i][j] = Max_cal(i, j-1);
        return Maxarr[i][j]; 
    }

    if (k == i){ //case 3
        Maxarr[i][j] = 1 + Max_cal(i+1, j-1);
        return Maxarr[i][j];
    }

    if (k < j && k > i){ //case 2
        const int in = 1 + Max_cal(i, k-1) + Max_cal(k+1, j-1); // include kj
        const int nin =  Max_cal(i, j-1); // not include kj

        if (in >= nin){
            Maxarr[i][j] = in;
            return Maxarr[i][j];
        }
        else{
            Maxarr[i][j] = nin;
            return Maxarr[i][j];
        }
    }
    
    return 0;
}

// get all valid chords
void MaxPlanarSubset::all_chord(const int &i, const int &j){
    if (i >= j) return;

    const int k = chord[j];
    char tmp[32];

    if (k > j || k < i) 
        all_chord(i, j - 1);

    else if (k > i && k < j){
        const int in = Maxarr[i][k - 1] + Maxarr[k + 1][j - 1] + 1;
        const int nin = Maxarr[i][j - 1];

        if (in >= nin) {
            all_chord(i, k - 1);
            sprintf(tmp, "%d %d\n", k, j);
            fputs(tmp, fout);
            all_chord(k + 1, j - 1);
        }

        else {
            all_chord(i, j - 1);
        }
    }
    else if (k == i){
        sprintf(tmp, "%d %d\n", i, j);
        fputs(tmp, fout);
        all_chord(i + 1, j - 1);
    }
    return;
}
