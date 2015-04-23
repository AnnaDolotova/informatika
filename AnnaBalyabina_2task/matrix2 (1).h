#include <iostream>
#include <stdio.h>
#include <vector> // заголовочный файл для использования векторов в программе
#include <time.h>
#include <stdlib.h>
#include <cmath>

using namespace std;
const double EPS = 1E-9;


class Matrix {
private:
	int n, k;
    vector< vector<double> > _mat; // объявление двумерного вектора, в котором будет наша матрица
	vector<double> arr; // ветор для миноров
    vector<pthread_t> pthreads; // вектор для тредов
public:
    Matrix(int N = 0, int K = 0) { // конструктор
        this->n = N;
        this->_mat.resize(N);
        for(int i = 0; i < N; i++) {
            this->_mat[i].resize(N);
            for(int j = 0; j < N; j++) {
                this->_mat[i][j] = rand() % 100; //числа рандомятся от 0 до 100 %-остаток от деления

            }
        }
        this->pthreads.resize(K);

        for(int i = 0; i < K; i++) {
            if(pthread_create(&(this->pthreads[i]), NULL, this->thread_job, i) > 0) { //shit
                printf("Can't creat a thread\n");
                exit(-1);
            }
        }
    }

    ~Matrix()  { // деструктор
        for (int i = 0; i < this->k; i++) {
            pthread_join(this->pthreads[i], NULL);
        }
    }

    void print() { // выводим матрицу на экран
        for(int i = 0; i < this->n; i++) {
            for(int j = 0; j < this->n; j++) {
                cout << this->_mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void* thread_job(void* t) { // функция для каждого треда
        int thread_number = *(int*)t;
		vector< vector<double> > in = this->_mat; // двумерный вектор
		for (int i = 1; i< this->n; i++) //  сдвиг матрицы вверх
			for (int j = 0; j< this->n; j++)
				in[i-1][j] = in[i][j];

		for (int i = 0; i< this->n; i++) // сдвиг второй части матрицы влево
			for (int j = thread_number+1; j< this->n; j++)
				in[i][j-1] = in[i][j];

		for (int i = 0; i< this->n; i++) in[i].resize((this->n)-1); // изменяем размер матрицы
    	in.resize((this->n)-1);

		double det = 1;
		for (int i=0; i< this->n; i++) {  // алгоритм Гаусса
			int k = i;
			for (int j=i+1; j< this->n; j++)
				if (abs(in[j][i]) > abs(in[k][i]))
					k = j;
			if (abs(in[k][i]) < EPS) {
				det = 0;
				break;
			}
			swap (in[i], in[k]);
			if (i != k)
				det = -det;
			det *= in[i][i];
			for (int j=i+1; j< this->n; j++)
				in[i][j] /= in[i][i];
			for (int j=0; j< this->n; j++)
				if (j != i && abs(in[j][i]) > EPS)
					for (int k=i+1; k< this->n; k++)
						in[j][k] -= in[i][k] * in[j][i];
		}

		arr[thread_number] = det;
		pthread_exit(NULL);
	}

	double getArr(int index) { // возвращает минор
        	return this->arr[index];
	}

	double getFromFirstRow(int index) { // возвращает элемент нулевой строки
        	return this->_mat[0][index];
	}

};
