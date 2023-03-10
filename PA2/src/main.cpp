#include <iostream>
#include "../lib/tm_usage.h"
#include "maxPlanarSubset.h"

using namespace std;

int main(int argc, char** argv){
    if (argc != 3){
        cout << "usage: mps <input_file_name> <output_file_name>" << endl;
        return 0;}
    
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    MaxPlanarSubset mps;
    mps.init(input_file, output_file);

    //put the max num in the output_file
    const int max = mps.Max_cal(0, mps.num_vertex-1);
    char tmp[32];
    sprintf(tmp, "%d\n", max);
    fputs(tmp, output_file);

    //put all the valid chords in the output_file
    mps.all_chord(0, mps.num_vertex -1);
    
    //close the files
    fclose(input_file);
    fclose(output_file);
    return 0;
}