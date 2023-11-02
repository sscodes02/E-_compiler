

#include "eppcompiler.h"

EPPCompiler::EPPCompiler()

{
    mem_loc.resize(memory_size);
    for (int i = 0; i < memory_size; i++)
    {
        mem_loc[i] = 0;
    }

}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    output_file = out_file;
    memory_size = mem_limit;
    mem_loc.resize(memory_size);
}

void EPPCompiler::compile(vector<vector<string>> code)
{
   
    for (vector<string> exp : code)
    {

        string first_element = exp[0];
        if (first_element == "del")
        {
            string var_name = exp[2];
            int mem_add = targ.symtable->search(var_name);

            mem_loc[mem_add] = 0;

            targ.parse(exp);
            vector<string> com;
            com.push_back("DEL = mem[" + to_string(mem_add) + "]");


            write_to_file(com);
        }
        else if (first_element == "ret")
        {

            targ.parse(exp);
            vector<string> com = generate_targ_commands();

            write_to_file(com);
        }
        else
        { 
            targ.parse(exp);
            int mem_add;
            if (targ.symtable->search(first_element) == -1)
            {
                {
                    for (int i = 0; i < memory_size; i++)
                    {
                        if (mem_loc[i] == 0)
                        {
                            mem_loc[i] = 1;
                            mem_add = i;
                            break;
                        }
                    }

                    targ.symtable->assign_address(first_element, mem_add);

                }

                vector<string> com = generate_targ_commands();

                write_to_file(com);
            }
        }

    }
}
vector<string> generating_commands(ExprTreeNode *x, SymbolTable *symT)
{
    vector<string> saumya;
    if (x == NULL)
    {
        return saumya;
    }

    if (x->right != NULL)
    {
        if (x->right->type == "ADD")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());
            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("ADD");
        }
        else if (x->right->type == "SUB")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());
            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("SUB");
        }
        else if (x->right->type == "MUL")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());
            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("MUL");
        }
        else if (x->right->type == "DIV")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());
            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("DIV");
        }

        else if (x->right->type == "VAL")
        {
            saumya.push_back("PUSH " + to_string(x->right->num));
        }
        else if (x->right->type == "VAR")
        {
            saumya.push_back("PUSH mem[" + to_string(symT->search(x->right->id)) + "]");
        }
    }
    if (x->left != NULL)
    {
        if (x->left->type == "DEL")
        {
            saumya.push_back("DEL = mem[" + x->left->id + "]");

        }
        else if (x->left->type == "RET")
        {
            saumya.push_back("RET = POP");
        }
        else if (x->left->type == "VAR" && x->type == ":=")
        {
            saumya.push_back("mem[" + to_string(symT->search(x->left->id)) + "] = POP");
        }
        else if (x->left->type == "VAR" && x->type != ":=")
        {
            saumya.push_back("PUSH mem[" + to_string(symT->search(x->left->id)) + "]");
        }
        else if (x->left->type == "VAL")
        {
            saumya.push_back("PUSH " + to_string(x->left->num));
        }
        else if (x->left->type == "ADD")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());
            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("ADD");
        }
        else if (x->left->type == "SUB")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());

            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("SUB");
        }
        else if (x->left->type == "MUL")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());
            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("MUL");
        }
        else if (x->left->type == "DIV")
        {
            vector<string> right_subtree = generating_commands(x->right, symT);
            vector<string> left_subtree = generating_commands(x->left, symT);
            saumya.insert(saumya.end(), left_subtree.begin(), left_subtree.end());
            saumya.insert(saumya.end(), right_subtree.begin(), right_subtree.end());

            saumya.push_back("DIV");
        }
    }

    return saumya;
}
vector<string> EPPCompiler::generate_targ_commands()
{

    ExprTreeNode *tree = targ.expr_trees.back();
    vector<string> main_commands = generating_commands(tree, targ.symtable);
    return main_commands;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream outFile(output_file, ios::app);
    for (const string &com : commands)
    {
        outFile << com << endl;
    }
    outFile.close();
}

EPPCompiler::~EPPCompiler()
{
}
