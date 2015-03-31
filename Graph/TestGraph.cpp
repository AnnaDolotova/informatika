#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

int main(int argc, const char * argv[]) {
	int count_of_vertex;
	cout << "Введите количество вершин графа" << endl;
	cin >> count_of_vertex;

	int a=0, b=0;
	while (a>count_of_vertex && a!=0) {
		cout << "Недопустимое значение" << endl;
		cin >> a;
	}
	while (b>count_of_vertex && b!=0) {
		cout << "Недопустимое значение! Попробуйте ещё." << endl;
		cin >> b;
	}

	Graph Orlov = new Graph(count_of_vertex);
	fill_graph();
	print_graph_like_matrix();
	path(a,b);

	delete Orlov;
    return 0;
}
