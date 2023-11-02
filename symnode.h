#pragma once
#include "string"
using namespace std;

class SymNode {
public:
    string key;
    int height;
    int address=-1;
    
    SymNode* par = NULL;
    SymNode* left = NULL;
    SymNode* right = NULL;

    SymNode();
    SymNode(string k);

    SymNode* LeftLeftRotation(); 
    SymNode* RightRightRotation();
    SymNode* LeftRightRotation(); 
    SymNode* RightLeftRotation(); 

    ~SymNode();
    
};