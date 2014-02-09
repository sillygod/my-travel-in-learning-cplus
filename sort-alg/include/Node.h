//Node.h
#ifndef NODE_H
#define NODE_H

#include "main.h"
/*
*Name:Node
*Desc:
*  combine some data in this class for convenience
*  it should be able to be sorted by its member
*  1. frequency
*  2. string's alpha
*  create two interator
*/

template<typename T>
class iter
{
public:
    iter()
    :mData(NULL)
    {}

    ~iter()
    {

    }



private:
    T *mData;
};


class Node
{
    public:

        Node();
        ~Node();



        int mStringTimes;       //record the word's times
        int mRow;               //record the row of word's position
        int mColumn;            //here use the word as the base of column
        char *mStringTail;
        char *mStringHead;
};

#endif //NODE_H
