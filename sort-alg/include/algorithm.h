//algorithm.h

//yeap, do this one, first
//
//think a better way for providing this interface
//I find there are a lot of refundent, maybe...

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Node.h"
#include "main.h"

class algorithm
{
    public:
        algorithm(int totalword,char *SortMode);
        ~algorithm();
        void deletetheSameword(Node *data);
        void WriteData(std::ofstream &output);
        void sort(Node* wordNode);


        //quicksort the right = totalword-1
        int  partitionAlphaBase(Node* data, int left, int right);
        int  partitionTimesBase(Node** data, int left, int right);
        void quickSortAlphaBase(Node *data,int left,int right);
        void quickSortTimesBase(int left,int right);

        //bubblesort
        void bubbleSortAlphaBase(Node *data);
        void bubbleSortTimesBase();
        //insertionsort
        void insertionSortAlphaBase(Node *data);
        void insertionSortTimesBase();
        //Merge sort
        void mergeSortAlphaBase(Node *data,int start,int end);
        void mergeAlphaBase(Node *data,int start,int end);
        void mergeSortTimesBase(int start,int end);
        void mergeTimesBase(Node **data,int start,int end);
        //heap sort
        void adjustHeapAlphaBase(Node *data, const int root, const int n);
        void heapSortAlphaBase(Node *data,const int n);
        void adjustHeapTimesBase(Node **data, const int root, const int n);
        void heapSortTimesBase(const int n);


    private:
        int    mWordNumWithDF;
        int    mtotalword;
        char   mSortMode;
        Node** mptr;    // point to the different data

};


#endif //ALGORITHM_H
