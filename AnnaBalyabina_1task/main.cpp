#include <iostream>
#include "header.h"
using namespace std;


int main ()
{
    Tree * my_tree = NULL;
    int n, s, k;
    cout << "vvedite kolichestvo elementov  " << endl;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cout << "vvedite chislo " << endl;
        cin >> s;

        if (my_tree == NULL)
            my_tree = new Tree(s);
        else
            my_tree->push(s);

    }
    cout << "your tree" << endl;
    my_tree->print();
    cout << "vvedite num for search" << endl;
    cin >> k;
    if (my_tree->search(k))
        cout<< k << " is in the tree" << endl;
    else
        cout<< k << " isn't in the tree" << endl;


    my_tree->pop();
    my_tree->print();
    return 0;
}
