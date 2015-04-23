#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <cmath>

using namespace std;
const double EPS = 1E-9;


class Matrix {
private:
	int n, k;
    vector< vector<double> > _mat;
	vector<double> arr;
    vector<pthread_t> pthreads;
public:
    Matrix(int N = 0, int K = 0) {
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

    ~Matrix() {
        for (int i = 0; i < this->k; i++) {
            pthread_join(this->pthreads[i], NULL);
        }
    }

    void print() {
        for(int i = 0; i < this->n; i++) {
            for(int j = 0; j < this->n; j++) {
                cout << this->_mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    int det() {
        double ans = 1;
        for(int i = 0; i < this->n; i++) {
            for(int j = i + 1; j < this->n; j++) {
                if (this->_mat[i][i] == 0) {
                    return 0;
                }
                double b = this->_mat[j][i] / this->_mat[i][i];
                for (this->k = i; k < this->n; k++) {
                    this->_mat[j][k] = this->_mat[j][k] - this->_mat[i][k] * b;
                }
            }
            ans *= this->_mat[i][i];
        }
        return ans;
    }

    void* thread_job(void* t) {
        int thread_number = *(int*)t;
		vector< vector<double> > in = this->_mat;
		for (int i = 1; i< this->n; i++)
			for (int j = 0; j< this->n; j++)
				in[i-1][j] = in[i][j];

		for (int i = 0; i< this->n; i++)
			for (int j = thread_number+1; j< this->n; j++)
				in[i][j-1] = in[i][j];

		for (int i = 0; i< this->n; i++) in[i].resize((this->n)-1);
    	in.resize((this->n)-1);

		double det = 1;
		for (int i=0; i< this->n; i++) {
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

	double getArr(int index) {
        	return this->arr[index];
	}

	double getFromFirstRow(int index) {
        	return this->_mat[0][index];
	}

};
