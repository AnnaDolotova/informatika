#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

int main(int argc, const char * argv[]) {
	setlocale(LC_ALL, "Russian");

	int count_of_vertex;
	cout << "Введите количество вершин графа" << endl;
	cin >> count_of_vertex;

	int a=0, b=0;

	Graph *Orlov = new Graph(count_of_vertex);
	cout << "Объект создан" << endl;

	Orlov->fill_graph();
	Orlov->print_graph_like_matrix();

	cout << "Найти путь из какой вершины?" << endl;
	cin >> a;
	while (a>count_of_vertex && a!=0) {
		cout << "Недопустимое значение" << endl;
		cin >> a;
	}

	cout << "В какую?" << endl;
	cin >> b;
	while (b>count_of_vertex && b!=0) {
		cout << "Недопустимое значение! Попробуйте ещё." << endl;
		cin >> b;
	}

	Orlov->path(a,b);

	delete Orlov;
    return 0;
}
