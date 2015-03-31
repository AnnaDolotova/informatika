/* graph.h */
#include <string>
#include <iostream>

using namespace std;

class Graph {
    private:
		int number; // ���������� ������ � �����
		char* matrix; // ��������� �� �������

    public:
    Graph(int count_of_vertex){  // �����������
		number = count_of_vertex;
        matrix = (char*)calloc(sizeof(char), number*number);
    }
    
    void fill_graph() {
		for (int i=0; i<number; i++) {
			for (int j=0; j<number; j++) 
				matrix[i*number+j]=rand()%2;
		}
	}

	void print_graph_like_matrix() {
		for (int i=0; i<number; i++) {
			for (int j=0; j<number; j++) 
				cout << matrix[i*number+j];
		};
		cout << endl;
	}

	void path(int from, int to) {
		bool existing = false;
		char* path_of_vertex; // ���� ����� ���������� ����, �� �������� ���, ����� ������� � �������
		path_of_vertex = (char*)calloc(sizeof(char), number);

		int k = 1; // ���������� ���������� ����
		int tmp = from; //�������, � ������� ��������� � ������ ������

		void recursion(int k) {
			for (int i=0; i<number; i++) {
				if (matrix[tmp*number+i] == 1) {
					path_of_vertex[k] = i;
					tmp = i;
					if (i == to) {
						break;
						existing = true;
					}
					for (int j=1; j<=k; j++) {
						if (path_of_vertex[j] == i) {
							break;
							path_of_vertex[j] = 0;
							i++;
						}
					}
					k++;
					recursion(k);
				}
			}
		};

		if (existing == true) {
			cout << "���� �� ������� " << from << "� ������� " << to << ": ";
			for (int i=0; i<number; i++) {
				cout << ", " << path_of_vertex[i];
			}
		}
		else cout << "���� �� ������� " << from << "� ������� " << to << "�� ����������."  << endl;
	}


    ~Graph() {  // ����������
        free(matrix);
		cout << "������ ���� �������. �� ��������!" << endl;
    }    
}
