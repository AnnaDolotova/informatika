#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

int main(int argc, const char * argv[]) {
	setlocale(LC_ALL, "Russian");

	int count_of_vertex;
	cout << "Enter number of vertex in graph" << endl;
	cin >> count_of_vertex;

	int a=0, b=0;

	Graph *Orlov = new Graph(count_of_vertex);
	cout << "Object was created" << endl;

	Orlov->fill_graph();
	Orlov->print_graph_like_matrix();

	cout << "Which vertex would you like to find path from?" << endl;
	cin >> a;
	while (a>count_of_vertex && a!=0) {
		cout << "Bad decision. Try again." << endl;
		cin >> a;
	}

	cout << "Find path to" << endl;
	cin >> b;
	while (b>count_of_vertex && b!=0) {
		cout << "Bad decision. Try again." << endl;
		cin >> b;
	}

	Orlov->path(a,b);

	delete Orlov;
    return 0;
}
