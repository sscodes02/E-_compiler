
#include "parser.h"


Parser::Parser()
{
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression)
{
    string first_element = expression[0];
    vector<ExprTreeNode *> s;
    ExprTreeNode *root = new ExprTreeNode();
    root->type = ":=";
    if (first_element == "del")
    {
        ExprTreeNode *deltypenode = new ExprTreeNode("DEL", 0);
        string delvarname = expression[2];
        ExprTreeNode *delvar = new ExprTreeNode("VAR", 0);
        delvar->id = delvarname;
        root->left = deltypenode;
        root->right = delvar;
        symtable->remove(expression[2]);
        expr_trees.push_back(root);
        return;
    }
    else if (first_element == "ret")
    {
        ExprTreeNode *rettyprnode = new ExprTreeNode("RET", 0);
        root->left = rettyprnode;
        ExprTreeNode *pseudo_root = new ExprTreeNode();
        ExprTreeNode *curr = pseudo_root;
        vector<string> tokens(expression.begin() + 2, expression.end());
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "(")
            {
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->left = node;
                curr = node;
            }
            else if (tokens[i] == "+")
            {
                curr->type = "ADD";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == "-")
            {
                curr->type = "SUB";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == "*")
            {
                curr->type = "MUL";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == "/")
            {
                curr->type = "DIV";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == ")")
            {
                if (!s.empty())
                {
                    curr = s.back();
                    s.pop_back();
                }
            }
            else if (tokens[i] > "0" && tokens[i] < "9")
            {
                curr->type = "VAL";
                curr->num = stoi(tokens[i]);
                if (!s.empty())
                {
                    curr = s.back();
                    s.pop_back();
                }
            }
            else
            {
                curr->type = "VAR";
                curr->id = tokens[i];
                if (!s.empty())
                {
                    curr = s.back();
                    s.pop_back();
                }
            }
        }
        root->right = curr;
        expr_trees.push_back(root);
    }
    else
    {
        ExprTreeNode *vartype = new ExprTreeNode();
        vartype->type = "VAR";
        vartype->id = expression[0];
        root->left = vartype;
        // added insert
        symtable->insert(expression[0]);
        ExprTreeNode *pseudo_root = new ExprTreeNode();
        ExprTreeNode *curr = pseudo_root;
        vector<string> tokens(expression.begin() + 2, expression.end());
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "(")
            {
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->left = node;
                curr = node;
            }
            else if (tokens[i] == "+")
            {
                curr->type = "ADD";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == "-")
            {
                curr->type = "SUB";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == "*")
            {
                curr->type = "MUL";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == "/")
            {
                curr->type = "DIV";
                ExprTreeNode *node = new ExprTreeNode();
                s.push_back(curr);
                curr->right = node;
                curr = node;
            }
            else if (tokens[i] == ")")
            {
                if (!s.empty())
                {
                    curr = s.back();
                    s.pop_back();
                }
            }
            else if (tokens[i] > "0" && tokens[i] < "9")
            {
                curr->type = "VAL";
                curr->num = stoi(tokens[i]);
                if (!s.empty())
                {
                    curr = s.back();
                    s.pop_back();
                }
            }
            else
            {
                curr->type = "VAR";
                curr->id = tokens[i];
                if (!s.empty())
                {
                    curr = s.back();
                    s.pop_back();
                }
            }
        }
        root->right = curr;
        expr_trees.push_back(root);
    }
}
Parser::~Parser()
{
        while (!expr_trees.empty())
    {
        delete expr_trees.back();
        expr_trees.pop_back();
    }
}