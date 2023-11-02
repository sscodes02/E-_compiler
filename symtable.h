#pragma once
#include "symnode.h"
#include "string"
using namespace std;

class SymbolTable {
private:
    int size = 0;
    SymNode* root = NULL;

public: 

    SymbolTable();
    ~SymbolTable();
    void insert(string k);
    void remove(string k);
    int search(string k);
    void assign_address(string k,int idx);
    int get_size();
    SymNode* get_root();
};
