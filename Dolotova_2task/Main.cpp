#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "Matrix.h"

using namespace std;

int main () {
	int a, b, c, d;
	cout << "Enter number of columns of 1st matrix" << endl;
	cin >> a;

	cout << "Enter number of lines of 1st matrix" << endl;
	cin >> b;

	Matrix *first = new Matrix(a,b);

	char* matrix1 = first -> fill_matrix(a,b);
	first -> print_matrix();

	cout << "Enter number of columns of 2nd matrix" << endl;
	cin >> c;

	cout << "Enter number of lines of 2nd matrix" << endl;
	cin >> d;

	Matrix *second = new Matrix(c,d);

	char* matrix2 = second -> fill_matrix(c,d);
	second -> print_matrix();

	int k;
	cout << "Enter number of threads" << endl;
	cin >> k;

	Multiplication *object = new Multiplication(matrix1, a, b, matrix2, c, d, k);

	pthread_t* pthreads = (pthread_t*)calloc(k, sizeof(pthread_t));

	srand(time(0));

	for(int i = 0; i < k; i++) {
		if(pthread_create(pthreads + i, NULL, object->thread_job, i) > 0) {
			printf("Can't creat a thread\n");
			exit(-1);
		}
	}

	for(int i = 0; i < k; i++) {
		if(pthread_join(pthreads[i], NULL) > 0) {
			printf("Can't block a thread\n");
			exit(-1);
		}
	}

	object->print_matrix();

	delete first;
	delete second;
	delete object;

	return 0;
}