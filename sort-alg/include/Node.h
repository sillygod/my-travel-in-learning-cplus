//Node.h
#ifndef NODE_H
#define NODE_H

#include "main.h"
//--------------------------------------------------
//Name:Node
//Desc:combine some data in this class for convenience
//--------------------------------------------------
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
