//algorithm.cpp

#include "algorithm.h"
using namespace std;


algorithm::algorithm(int totalword,char *SortMode)
:mWordNumWithDF(0)
{
    mtotalword=totalword;
    mSortMode=*SortMode;
    mptr=new Node*[totalword];


}

algorithm::~algorithm()
{
    for(int i=0;i<mtotalword;i++)
    {
        mptr[i]=NULL;
    }
    delete [] mptr;

}

template<typename T>
void swap(T *a, T*b)
{
    T *temp;

    temp = a;
    a = b;
    b = temp;
}

void algorithm::deletetheSameword(Node *data)
{
    int i=1;
    int j=0;

    mptr[mWordNumWithDF]=data;

    while(i<mtotalword)
    {
        if(strcmp(data[j].mStringHead,data[i].mStringHead)==0)
        {
            data[j].mStringTimes++;
        }
        else
        {
            mptr[mWordNumWithDF]=(data+j);
            j=i;
            mWordNumWithDF++;

        }
        i++;
    }
    //the mWordNumWithDF will be added more one
}

void algorithm::WriteData(ofstream &output)
{
    int i=0;
    int j=0;

    output<<mtotalword<<endl;
    while(i<mWordNumWithDF)
    {

        int length=mptr[i]->mStringTail-(mptr[i]->mStringHead)+1; //  abc\0   \0 tail whick pointer points to
        char buffer[length+45];
        char str[length]; // one for '\0'


        strcpy(str,mptr[i]->mStringHead);
        sprintf(buffer,"%s %d %d_%d",str,mptr[i]->mStringTimes,mptr[i]->mRow,mptr[i]->mColumn);
        output<<buffer;

        if(mptr[i]->mStringTimes>1)
        {
            j=mptr[i]->mStringTimes;
            int k=1;
            while(k<j)
            {
                output<<" "<<mptr[i][k].mRow<<"_"<<mptr[i][k].mColumn;
                k++;
            }
            output<<"\n";
        }
        else
        {
            output<<"\n";
        }
        i++;
    }
}

void algorithm::sort(Node* wordNode)
{
    switch(mSortMode)
    {
        case 'b':bubbleSortAlphaBase(wordNode);
                 deletetheSameword(wordNode);
                 bubbleSortTimesBase();
                 break;

        case 'q':quickSortAlphaBase(wordNode,0,mtotalword-1);
                 deletetheSameword(wordNode);
                 quickSortTimesBase(0,mWordNumWithDF-1);
                 break;

        case 'i':insertionSortAlphaBase(wordNode);
                 deletetheSameword(wordNode);
                 insertionSortTimesBase();
                 break;

        case 'm':mergeSortAlphaBase(wordNode,0,mtotalword-1);
                 deletetheSameword(wordNode);
                 mergeSortTimesBase(0,mWordNumWithDF-1);
                 break;

        case 'h':heapSortAlphaBase(wordNode,mtotalword-1);
                 deletetheSameword(wordNode);
                 heapSortTimesBase(mWordNumWithDF-1);
                 break;


        default:
                cout<<"error mode";
                exit(0);
                break;
    }
}


//================bubbleSort=====================

void algorithm::bubbleSortTimesBase()
{

    Node *temp;
    for(int i=0;i<mWordNumWithDF;i++)
        for(int j=mWordNumWithDF-1;j>i;j--)
        {
            if(mptr[j]->mStringTimes > mptr[j-1]->mStringTimes)
            {
                temp     =mptr[j];
                mptr[j]  =mptr[j-1];
                mptr[j-1]=temp;

            }
        }

}

void algorithm::bubbleSortAlphaBase(Node *data)
{
    Node temp;
    for(int i=0;i<mtotalword;i++)
        for(int j=mtotalword-1;j>i;j--)
        {
            if(strcmp( data[j].mStringHead, data[j-1].mStringHead)<0) // data[j-1] alphabet large than data[j]
            {
                temp       =*(data+j);
                *(data+j)  =*(data+j-1);
                *(data+j-1)=temp;
            }
        }
}

//===============quicksort======================

int  algorithm::partitionTimesBase(Node** data, int left, int right)
{
    int lbase, rbase;
    int key;
    Node *temp;

    key = data[right]->mStringTimes;
    lbase = left - 1;

    for(rbase = left; rbase < right; rbase++)
    {
        if(data[rbase]->mStringTimes>key)
        {
            lbase++;

            temp=data[lbase];
            data[lbase]=data[rbase];
            data[rbase]=temp;
        }
        if(data[rbase]->mStringTimes==key && strcmp(data[rbase]->mStringHead,data[right]->mStringHead)<0 )
        {
            lbase++;

            temp=data[lbase];
            data[lbase]=data[rbase];
            data[rbase]=temp;
        }
    }

    temp=data[lbase+1];
    data[lbase+1]=data[right];
    data[right]=temp;

    return lbase+1;

}

void algorithm::quickSortTimesBase(int left,int right)
{
    int pivot;

    if(left < right)
    {
        pivot = partitionTimesBase(mptr, left, right);
        quickSortTimesBase(left, pivot-1);
        quickSortTimesBase(pivot+1, right);
    }
}


int algorithm::partitionAlphaBase(Node* data, int left, int right)
{
    int lbase, rbase;
    char* key;
    Node temp;

    key = data[right].mStringHead;
    lbase = left - 1;



    for(rbase = left; rbase < right; rbase++)
    {
        if(strcmp(data[rbase].mStringHead,key)<0 )
        {
            lbase++;

            temp=data[lbase];
            data[lbase]=data[rbase];
            data[rbase]=temp;
        }
    }

    temp=data[lbase+1];
    data[lbase+1]=data[right];
    data[right]=temp;

    return lbase+1;
}

void algorithm::quickSortAlphaBase(Node* data, int left, int right)
{
    int pivot;

    if(left < right)
    {
        pivot = partitionAlphaBase(data, left, right);
        quickSortAlphaBase(data, left, pivot-1);
        quickSortAlphaBase(data, pivot+1, right);
    }
}

//================insertionsort=========================

void algorithm::insertionSortAlphaBase(Node *data)
{
    Node key;
    int   i=0;

    for(int j=1;j<mtotalword;j++)
    {
        key=data[j];
        i=j-1;

        while(i>=0 && strcmp(data[i].mStringHead,key.mStringHead)>0)
        {
            data[i+1]=data[i];
            i=i-1;
        }
            data[i+1]=key;
    }
}

void algorithm::insertionSortTimesBase()
{
    Node* key;
    int   i=0;

    for(int j=1;j<mWordNumWithDF;j++)
    {
        key=mptr[j];
        i=j-1;

        while(i>=0 && mptr[i]->mStringTimes < key->mStringTimes)
        {
            mptr[i+1]=mptr[i];
            i=i-1;
        }
            mptr[i+1]=key;
    }
}

//=============Merge sort===================
void algorithm::mergeAlphaBase(Node *data,int start,int end)
{
    Node* temp= new Node[end-start+1];

    int i=start;
    int mid=(start+end)/2;
    int j=mid+1;
    int k=-1;

        while( i <= mid && j<=end ) //one of them may be empty, so it must set it to unlimited big
        {
            if(strcmp(data[i].mStringHead,data[j].mStringHead)<0)
            {
                temp[++k]=data[i++];
            }
            else
            {
                temp[++k]=data[j++];
            }
        }

        if( i > mid)
        {
            for(int t=j; t<=end; t++)
                temp[++k]=data[t];
        }
        if( j> end)
        {
            for(int t=i; t<=mid; t++)
                temp[++k]=data[t];
        }

        k=-1;

        for(int index=start; index<=end; index++)
            data[index]=temp[++k];

        delete [] temp;
}

void algorithm::mergeSortAlphaBase(Node *data,int start,int end)
{
    int mid=(end+start)/2;

    if(end>start)
    {
        mergeSortAlphaBase(data,start,mid);
        mergeSortAlphaBase(data,mid+1,end);
        mergeAlphaBase(data,start,end);
    }
}

void algorithm::mergeTimesBase(Node **data,int start,int end)
{
    Node** temp= new Node*[end-start+2];

    int i=start;
    int mid=(start+end)/2;
    int j=mid+1;
    int k=-1;

        while( i <= mid && j<=end ) //one of them may be empty, so it must set it to unlimited big
        {
            if(data[i]->mStringTimes > data[j]->mStringTimes )
            {
                temp[++k]=data[i++];
            }
            if(data[i]->mStringTimes == data[j]->mStringTimes && (strcmp(data[i]->mStringHead,data[j]->mStringHead)<0))
            {
                temp[++k]=data[i++];
            }
            if(data[i]->mStringTimes < data[j]->mStringTimes)
            {
                temp[++k]=data[j++];
            }
        }

        if( i > mid)
        {
            for(int t=j; t<=end; t++)
                temp[++k]=data[t];
        }
        if( j> end)
        {
            for(int t=i; t<=mid; t++)
                temp[++k]=data[t];
        }

        k=-1;

        for(int index=start; index<=end; index++)
            data[index]=temp[++k];

        for(int clear=0; clear<=(end-start+1); clear++)
            temp[clear]=NULL;

        delete [] temp;
}

void algorithm::mergeSortTimesBase(int start,int end)
{
    int mid=(end+start)/2;

    if(end>start)
    {
        mergeSortTimesBase(start,mid);
        mergeSortTimesBase(mid+1,end);
        mergeTimesBase(mptr,start,end);
    }
}

//===============heap sort===================
void algorithm::adjustHeapAlphaBase(Node *data, const int root, const int n)
{
    Node e=data[root];
    int j;

    for(j=2*root+1; j<=n; j=j*2+1)
    {
        if(j<n && strcmp(data[j].mStringHead,data[j+1].mStringHead)<0) j++;
        if( strcmp(e.mStringHead,data[j].mStringHead)>=0) break;
        data[(j-1)/2]=data[j];
    }
    data[(j-1)/2]=e;
}

void algorithm::heapSortAlphaBase(Node *data,const int n)
{
    Node temp;

    for(int i=(n-1)/2; i>=0;i--)
        adjustHeapAlphaBase(data,i,n);
    for(int i=n;i>=0;i--)
    {
        temp=data[0];
        data[0]=data[i];
        data[i]=temp;
        adjustHeapAlphaBase(data,0,i-1);
    }
}

void algorithm::adjustHeapTimesBase(Node **data, const int root, const int n)
{
    Node *e=data[root];
    int j;

    for(j=2*root+1; j<=n; j=j*2+1)
    {
        if(j<n && data[j]->mStringTimes > data[j+1]->mStringTimes) j++;
        else if(j<n && (data[j]->mStringTimes == data[j+1]->mStringTimes) && strcmp(data[j]->mStringHead,data[j+1]->mStringHead)<0) j++;
        if( e->mStringTimes == data[j]->mStringTimes && strcmp(e->mStringHead,data[j]->mStringHead)>0) break;
        if( e->mStringTimes < data[j]->mStringTimes) break;
        data[(j-1)/2]=data[j];
    }
    data[(j-1)/2]=e;
}

void algorithm::heapSortTimesBase(const int n)
{
    Node* temp;

    for(int i=(n-1)/2; i>=0;i--)
        adjustHeapTimesBase(mptr,i,n);
    for(int i=n;i>=0;i--)
    {
        temp=mptr[0];
        mptr[0]=mptr[i];
        mptr[i]=temp;
        adjustHeapTimesBase(mptr,0,i-1);
    }
}
