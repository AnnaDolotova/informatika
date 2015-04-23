#include "matrix2.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

    int N; // вводим с клавиатуры размер матрицы
    cout << "Enter a size of matrix" << endl;
	cin >> N;

    int k; // вводим с клавиатуры число тредов
    cout << "Enter a number of threads" << endl;
    cin >> k;

    srand(int(time(NULL))); // рандомно заполняем матрицу
    //Matrix M = new Matrix(N, k);
	Matrix M(N, k);
    M.print(); // печатаем матрицу

    double det = 0;

	for(int i = 0; i < N; i++) { // конечная формула для вычисления детерминанта
		det = (M.getFromFirstRow(i))*(M.getArr(i))*((int)pow(-1,k));
	}

    cout << det; //  выводим на экран ответ

    return 0;

}
