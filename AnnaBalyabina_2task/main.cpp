#include "matrix2.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

    int N; // Enter a size of matrix from keyboard
    cout << "Enter a size of matrix" << endl;
	cin >> N;

    int k; // Enter a number of threads from keyboard
    cout << "Enter a number of threads" << endl;
    cin >> k;

    srand(int(time(NULL))); // fill matrix with random
    //Matrix M = new Matrix(N, k);
	Matrix M(N, k);
    M.print(); // print the matrix

    double det = 0;

	for(int i = 0; i < N; i++) { // last formula for calculating the determinant
		det = (M.getFromFirstRow(i))*(M.getArr(i))*((int)pow(-1,k));
	}

    cout << det; // display the answer

    return 0;

}
