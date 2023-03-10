#include <stdio.h>
#include <stdlib.h>
#include "mst.h"
#include "acyclic.h"

int main(int argc, char *argv[]){
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w+");
    char mode;
    const int err = fscanf(input_file, "%c", &mode);
    if (mode == 'u'){
        MST mst(input_file, output_file);
    }
    else {
        Acyclic acyclic(input_file, output_file);
    }
}