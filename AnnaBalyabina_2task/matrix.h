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
    vector< vector<double> > _mat; // classified bidimensional vector, which will be our matrix
	vector<double> arr; // vector for minors
	vector<pthread_t> pthreads; // vector for threads
public:
    Matrix(int N = 0, int K = 0) { // constructor
        this->n = N;
        this->_mat.resize(N);
        for(int i = 0; i < N; i++) {
            this->_mat[i].resize(N);
            for(int j = 0; j < N; j++) {
                this->_mat[i][j] = rand() % 100; //Random numbers from 0 to 100
            }
        }
        this->pthreads.resize(K);

        for(int i = 0; i < K; i++) {
            if(pthread_create(&(this->pthreads[i]), NULL, this->thread_job, i) > 0) {
                printf("Can't creat a thread\n");
                exit(-1);
            }
        }
    }

    ~Matrix()  { // destructure
        for (int i = 0; i < this->k; i++) {
            pthread_join(this->pthreads[i], NULL);
        }
    }

    void print() { //derive the matrix on the screen
        for(int i = 0; i < this->n; i++) {
            for(int j = 0; j < this->n; j++) {
                cout << this->_mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void* thread_job(void* t) { // function for each thread
        int thread_number = *(int*)t;
		vector< vector<double> > in = this->_mat; // bidimensional vector
		for (int i = 1; i< this->n; i++) //  shift matrix up
			for (int j = 0; j< this->n; j++)
				in[i-1][j] = in[i][j];

		for (int i = 0; i< this->n; i++) //  second shift matrix of left
			for (int j = thread_number+1; j< this->n; j++)
				in[i][j-1] = in[i][j];

		for (int i = 0; i< this->n; i++) in[i].resize((this->n)-1); // change the size of matrix
    	in.resize((this->n)-1);

		double det = 1;
		for (int i=0; i< this->n; i++) {  // Gauss algorithm
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

	double getArr(int index) { // return minor
        	return this->arr[index];
	}

	double getFromFirstRow(int index) { // return an element of zero line
        	return this->_mat[0][index];
	}

};
