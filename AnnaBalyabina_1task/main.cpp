#include <iostream>
#include <curses.h>
#include "header.h"
using namespace std ;



int main ()
{
    node *d = NULL;
    int n;
    int s;
    cout << "vvedite kolichestvo elementov  " << endl;
    cin >> n;
    
    for (int i = 0; i < n; ++i)
    {
        cout << "vvedite chislo " << endl;
        cin >> s;
        d->push(s, &d);
        
    
    }
    cout<<"your tree"<<endl;
    d->print(d,0);

}