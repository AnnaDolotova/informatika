#include <iostream>

using namespace std;

class Node {

public:
    Node *l, *r;
    int info;

    Node(int i) {
        info = i;
        l = NULL;
        r = NULL;
    }

    void push(int a) {
        Node * t;

        if (a < info) {
            if (l == NULL) {
                t = new Node(a);
                l = t;
            } else {
                l->push(a);
            }
        } else {
            if (r == NULL) {
                t = new Node(a);
                r = t;
            } else {
                r->push(a);
            }
        }
    }

    void pop() {
        if (l == NULL) {
            cout << "min element = " << info << endl;
        } else {
            l->pop();
        }
    }

    Node * search(int num) {
        if (info == num) {
            return this;
        } else {
            if (l != NULL)
                l->search(num);
            if (r != NULL)
                r->search(num);
        }
        return NULL;
    }

    void print(int u) {
        if (l != NULL)
            l->print(u + 1);
        for (int i = 0; i < u; i++)
            cout << "|";
        cout << info << endl;
        if (r != NULL)
            r->print(u + 1);
    }
};


class Tree{

private:
    Node * root;

public:
    Tree(int a){
        root = new Node(a);
    }

    Tree() {
        root = new Node(0);
    }

    void push(int a) {
        root->push(a);
    }

    void print(){
        root->print(1);
    }

    void pop() {
        root->pop();
    }

    bool search(int num){
        Node * n = root->search(num);
        return n == NULL ? false : true;
    }
};
