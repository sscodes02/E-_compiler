
#include "symtable.h"
SymbolTable::SymbolTable()
{
    size = 0;
    root = nullptr;
}
int actual_height(SymNode*x){
    if(x->right!=NULL&&x->left!=NULL){
        if(x->right->height>x->left->height){
            return x->right->height+1;
        }
        else if(x->left->height>x->right->height){
            return x->left->height+1;
        }
        else{
            return x->right->height+1;
        }
    }
    else if(x->right&&x->left==NULL){
         return x->right->height+1;
    }
    else if(x->left&&x->right==NULL){
       return x->left->height+1; 
    }
}
int hgt(SymNode *x)
{
    if (x == NULL)
    {
        return -1;
    }
    return x->height;
}
SymNode *leftrotate(SymNode *x)
{

    SymNode *y = x->right;
    SymNode *z = y->left;
    y->left = x;
    x->right = z;
    x->height=actual_height(x);
    y->height=actual_height(y);
    return y;
}
SymNode *rightrotate(SymNode *x)
{
    SymNode *y = x->left;
    SymNode *z = y->right;
    y->right = x;
    x->left = z;
    x->height=actual_height(x);
    y->height=actual_height(y);
    return y;
}
SymNode*leftrightrotate(SymNode*x){
        x->left = leftrotate(x->left);
        return rightrotate(x);
}
SymNode*rightleftrotate(SymNode*x){
        x->right = rightrotate(x->right);
        return leftrotate(x);
}

int get_balance(SymNode *x)
{
    if (x == nullptr)
    {
        return -1;
    }
    else
    {
        return hgt(x->left) - hgt(x->right);
    }
}

SymNode *insert_rec(string k, int &size, SymNode *x)
{
    if (x == nullptr)
    {
        new SymNode(k);
        size++;
        return new SymNode(k);
    }
    if (k < x->key)
    {
        x->left = insert_rec(k, size, x->left);
    }
    else if (k > x->key)
    {
        x->right = insert_rec(k, size, x->right);
    }

    x->height = actual_height(x);

    int balance_factor = get_balance(x);
    if(balance_factor>1){
        if(k<x->left->key){
         return rightrotate(x);   
        }
        else if(k>x->left->key){
          return leftrightrotate(x);  
        }
    }
    else if(balance_factor<-1){
        if(k<x->right->key){
         return rightleftrotate(x);   
        }
        else if(k>x->right->key){
            return leftrotate(x);
        }
    }

    return x;
}
void SymbolTable::insert(string k)
{
    root = insert_rec(k, size, root);
}

SymNode *findsucc(SymNode *node)
{
    SymNode *curr = node;
    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}

SymNode *deleteNode(SymNode *x, string k, int &size)
{
    if (x == NULL)
        return x;
    if (k < x->key)
        x->left = deleteNode(x->left, k, size);
    else if (k > x->key)
        x->right = deleteNode(x->right, k, size);
    else
    {
        if (x->left == NULL && x->right == NULL)
        {
            x->left = x;
            x = NULL;
        }
        else if (x->left == NULL)
        {
            SymNode *temp = x->right;
            *x=*temp;
            delete temp;
            
        }
        else if (x->right == NULL)
        {
            SymNode *temp = x->left;
            *x=*temp; 
            delete temp;
           
        }
        else
        {
            SymNode *temp = findsucc(x->right);
            x->key = temp->key;
            x->right = deleteNode(x->right, temp->key, size);
        }
    }
    if (x == NULL)
    {
        return x;
    }
    x->height = actual_height(x);
    int balance_factor = get_balance(x);
    int leftbalancefactor=get_balance(x->left);
    int rightbalancefactor=get_balance(x->right);
    if(balance_factor>1){
        if(leftbalancefactor >= 0){
            return rightrotate(x);
            }
             else if(leftbalancefactor<0){
              return leftrightrotate(x);  
            }
        }
    
    else if(balance_factor<-1){
        if(rightbalancefactor<=0){
         return leftrotate(x);   
        }
        else if(rightbalancefactor>0){
           return rightleftrotate(x); 
        }
    }
    return x;
}
void SymbolTable::remove(string k)
{
    root = deleteNode(root, k, size);
}

int SymbolTable::search(string k)
{

    if (root == NULL)
    {
        return -2;
    }
    SymNode *node = root;
    while (node != nullptr)
    {

        if (k == node->key)
        {
            return node->address;
            break;
        }
        else if (k < node->key)
        {
            node = node->left;
        }
        else if (k > node->key)
        {
            node = node->right;
        }
    }
    return -2;
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *node = root;
    while (node != nullptr)
    {

        if (k == node->key)
        {
            node->address = idx;
            break;
        }
        else if (k < node->key)
        {
            node = node->left;
        }
        else if (k > node->key)
        {
            node = node->right;
        }
    }
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{
    delete root;
}
