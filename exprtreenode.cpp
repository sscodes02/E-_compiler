
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{
    type = "";
    id = "";
    left = nullptr;
    right = nullptr;
    num = 0;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    type = t;
    if (t == "VAL")
    {
        num = v;
        id = "";
        left = nullptr;
        right = nullptr;
    }
    else if (t == "VAR")
    {
        num = 0;
        id = "";
        left = nullptr;
        right = nullptr;
    }
    else if (t == "DEL")
    {
        id = "";
        num = 0;
        left = nullptr;
        right = nullptr;
    }
    else if (t == "RET")
    {
        id = "";
        num = 0;
        left = nullptr;
        right = nullptr;
    }
    else
    {
        id = "";
        num = 0;
        left = nullptr;
        right = nullptr;
    }
}

ExprTreeNode::~ExprTreeNode()
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
