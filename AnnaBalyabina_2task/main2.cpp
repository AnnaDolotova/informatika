#include "matrix2.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

    int N;
    cout << "Enter a size of matrix" << endl;
	cin >> N;

    int k;
    cout << "Enter a number of threads" << endl;
    cin >> k;

    srand(int(time(NULL)));
    //Matrix M = new Matrix(N, k);
	Matrix M(N, k);
    M.print();

    double det = 0;

	for(int i = 0; i < N; i++) {
		det = (M.getFromFirstRow(i))*(M.getArr(i))*((int)pow(-1,k));
	}

    cout << det;

    return 0;

}
