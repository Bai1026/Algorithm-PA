#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>

using namespace std;

void printarr(vector<int> &data){
    for (int i = 0; i < data.size(); i++){
        cout << data[i] << " ";
    }
    cout << endl;
}

void MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    int l = root*2;
    int r = root*2+1;
    int largest = 0;

    if (l <= data.size() && data[l-1] > data[root-1])
        largest = l;
    
    else
        largest = root;

    if (r <= data.size() && data[r-1] > data[largest-1])
        largest = r;

    if (largest != root){
        swap(data[root-1], data[largest-1]);
        MaxHeapify(data, largest);
    }
}

int main()
{
    int a[8] = {2,4,8,7,1,1000,3,6};
    vector<int> data(a, a + sizeof(a)/sizeof(int)); //intialize the vector

    printarr(data);
    // max(data, 2);

    // MaxHeapify(data, );
    printarr(data);

    return 0;
}
