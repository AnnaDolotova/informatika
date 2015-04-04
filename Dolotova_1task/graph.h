/* graph.h */
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Graph {
	private:
	
		int number; // number of vertex in matrix
		char* matrix; // pointer to matrix

		bool help(int k, int tmp, char* path_of_vertex, int to, int b) {  // function, which helps to find path
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
		Graph(int count_of_vertex){  // constructor
			number = count_of_vertex;
			matrix = (char*)calloc(sizeof(char), number*number);
		}
    
		void fill_graph() {  // filling matrix by random
			srand(time(0));
			for (int i=0; i<number; i++) {
				for (int j=0; j<number; j++) 
					matrix[i*number+j] = rand()%2;
			}
		}

		void print_graph_like_matrix() { // print matrix
			for (int i=0; i<number; i++) {

				for (int j=0; j<number; j++) 
					cout << (int)matrix[i*number+j] << " ";
					cout << " " << endl;
			};
		}

		void path(int from, int to) {  // finding path
			char* path_of_vertex; // tmp path
			path_of_vertex = (char*)calloc(sizeof(char), number);

			int k = 1; // number of vertex, which were found in path
			int tmp = from; // tmp vertex
			path_of_vertex[0]=from;
			int b=1;

			bool existing = help(k, tmp, path_of_vertex, to, b);

			if (existing == true) {
				cout << "Path from vertex " << from << " to " << to << ": ";
				for (int i=0; i<number; i++) {
					if (path_of_vertex[i] != 0) {
						cout << (int)path_of_vertex[i];
					}
				}
				cout << endl;
			}
			else cout << "Path from vertex " << from << " to " << to << " doesn't exist."  << endl;
		}


		~Graph() {  // destructor
			free(matrix);
			cout << "Memory was deleted. Good bye!" << endl;
		}    

};



