#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class MaxPlanarSubset{
public:
    MaxPlanarSubset(void);
    void init(FILE*, FILE*);
    void all_chord(const int &, const int&);
    int Max_cal(const int &, const int&);
    int num_vertex, num_chord;

private:
    int *chord, **Maxarr;
    FILE *fin, *fout;
};