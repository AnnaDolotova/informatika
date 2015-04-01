#include <iostream>

using namespace std;

class node {
public:
    int info;
    node *l, *r;
    void push(int a, node **t) {
        if ((*t) == NULL) {
            (*t) = new node;
            (*t)->info = a;
            (*t)->l = (*t)->r = NULL;
            return;
        }
        if (a > (*t)->info) push(a, &(*t)->r);
        else push(a, &(*t)->l);
    }
    
    void print (node *t,int u)
    {
        if (t == NULL) return;
        else
        {
            print(t->l,++u);
            for (int i = 0; i < u; ++i) cout << "|";
            cout << t->info << endl;
            u--;
        }
        print(t->r, ++u);
    }
};



