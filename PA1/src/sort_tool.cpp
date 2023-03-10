// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method --> DONE
void SortTool::InsertionSort(vector<int>& data) {
    for(int i=1; i<=data.size()-1; i++) {
        int min = data[i];
        int j = i-1; //往前一個找,前面都sorted

        while(j>=0 && data[j]>min){
            swap(data[j+1], data[j]);
            int tmp = data[j+1];
            data.erase(data.begin()+j);
            data.insert(data.begin()+j, tmp);
            j--;            
        }
        data[j+1] = min; //停止點的下一個
    }
}

// Quick sort method --> DONE
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    if (low < high) {
        int q = Partition(data, low, high);
        QuickSortSubVector(data,low,q-1);
        QuickSortSubVector(data,q+1,high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    srand(time(NULL));
    int pivot_r = low + rand()%(high-low);
    swap(data[pivot_r], data[high]);

    int mid = low-1;
    for (int j = low; j <= high-1; j++){
        if (data[j] <= data[high]){
            mid++;
            swap(data[mid], data[j]);
        }
    }
    swap(data[mid+1], data[high]);
    return mid+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
} 

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    if (low < high){
        int middle1 = floor( (low+high) /2);
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle1+1, high);
        Merge(data,low, middle1, middle1+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    vector<int> L(data.begin()+low, data.begin()+middle1+1);
    vector<int> R(data.begin()+middle1+1, data.begin()+high+1);
    L.insert(L.end(), INT_MAX);//sentinel
    R.insert(R.end(), INT_MAX);//sentinel

    int index_l=0,
        index_r=0;

    for(int i=low; i<=high; i++){
        if(L[index_l] <= R[index_r]){
            data[i] = L[index_l];
            index_l++;
        }
        else{
            data[i] = R[index_r];
            index_r++;
        }
    }
}


// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size()-1; i >= 0; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    int l = root*2 +1, //turn to index
        r = root*2 +2,
        largest; // no need to assign to root

    if (l < heapSize && data[l] > data[root]) // l<heapSize 
        largest = l;
    else
        largest = root;

    if (r < heapSize && data[r] > data[largest])
        largest = r;

    if (largest != root){
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    for (int i=floor(heapSize/2); i>=0; i--){
        MaxHeapify(data,i);
    }
}
