#pragma once
#include <string>
using namespace std;

class ExprTreeNode {
public:
    string type;
    string id;

    int num;

    ExprTreeNode* left = NULL;
    ExprTreeNode* right = NULL;

    ExprTreeNode();
    ExprTreeNode(string t,int v);

    ~ExprTreeNode();
};