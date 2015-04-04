/* graph.h */
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Graph {
	private:
	
		int number; // количество вершин в графе
		char* matrix; // указатель на матрицу

		bool recursion(int k, int tmp, char* path_of_vertex, int to, int b) {  // рекурсия для поиска пути в графе
			for (int i=b; i<=number; i++) {
				if (matrix[(tmp-1)*number+i-1] == 1) {
					path_of_vertex[k] = i;
					tmp = i;
					if (i == to) {
						return true;
					}
					for (int j=0; j<k; j++) {
						if (path_of_vertex[j] == i) {
							path_of_vertex[j] = 0;
							b++;
							break;
						}
					}
					k++;
				}
			}
			return false;
		}

    public:
		Graph(int count_of_vertex){  // конструктор
			number = count_of_vertex;
			matrix = (char*)calloc(sizeof(char), number*number);
		}
    
		void fill_graph() {  // заполнение матрицы смежности
			srand(time(0));
			for (int i=0; i<number; i++) {
				for (int j=0; j<number; j++) 
					matrix[i*number+j] = rand()%2;
			}
		}

		void print_graph_like_matrix() { // печать матрицы смежности
			for (int i=0; i<number; i++) {

				for (int j=0; j<number; j++) 
					cout << (int)matrix[i*number+j] << " ";
					cout << " " << endl;
			};
		}

		void path(int from, int to) {  // поиск пути в графе
			char* path_of_vertex; // сюда будем записывать путь, по которому шли, чтобы попасть в вершину
			path_of_vertex = (char*)calloc(sizeof(char), number);

			int k = 1; // количество пройденных ребёр
			int tmp = from; //вершина, в которой находимся в данный момент
			path_of_vertex[0]=from;
			int b=1;

			bool existing = recursion(k, tmp, path_of_vertex, to, b);

			if (existing == true) {
				cout << "Путь из вершины " << from << " в вершину " << to << ": ";
				for (int i=0; i<number; i++) {
					if (path_of_vertex[i] != 0) {
						cout << (int)path_of_vertex[i];
					}
				}
				cout << endl;
			}
			else cout << "Путь из вершины " << from << " в вершину " << to << " не существует."  << endl;
		}


		~Graph() {  // деструктор
			free(matrix);
			cout << "Память была очищена. До свидания!" << endl;
		}    

};



