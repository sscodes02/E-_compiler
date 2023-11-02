
#include "symnode.h"
SymNode::SymNode()
{
    key = "";
    height = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k)
{
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode *SymNode::LeftLeftRotation()
{
    return NULL;
}

SymNode *SymNode::RightRightRotation()
{
    return NULL;
}

SymNode *SymNode::LeftRightRotation()
{
    return NULL;
}

SymNode *SymNode::RightLeftRotation()
{
    return NULL;
}

SymNode::~SymNode()
{
    if (left != nullptr)
    {
        delete left;
    }
    if (right != nullptr)
    {
        delete right;
    }
}