//Node.cpp

#include "Node.h"


Node::Node()
:mStringTimes(1),mRow(0),mColumn(0),mStringTail(NULL),mStringHead(NULL)
{
}

Node::~Node()
{
    mStringTail=NULL;
    mStringHead=NULL;
}
