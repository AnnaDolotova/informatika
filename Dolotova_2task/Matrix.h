#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Matrix {
	private:
		int number1;
		int number2;
		char* matrix;

	public:
		Matrix(int count1, int count2) {
			number1 = count1;
			number2 = count2;
			matrix = (char*)calloc(sizeof(char), number1*number2);
		}

		char* fill_matrix(int number1, int number2) { 
			srand(time(0));
			for (int i=0; i<number1; i++) {
				for (int j=0; j<number2; j++) 
					matrix[i*number1+j] = rand();
			}
			return matrix;
		}

		void print_matrix() { 
			for (int i=0; i<number1; i++) {
				for (int j=0; j<number2; j++) 
					cout << (int)matrix[i*number1+j] << " ";
					cout << " " << endl;
			};
		}

		~Matrix() {  // destructor
			free(matrix);
			cout << "Memory of matrix was deleted. Good bye!" << endl;
		}   
	};

class Multiplication {
	private:
		int number1;
		int number2;
		int number_mix;
		char* matrix1;
		char* matrix2;
		char* result;
		int threads;

		int result_element(int i, int j) {
			result[i*number2+j]=0;
			for (int k=0; k<number_mix; k++){
				result[i*number2+j] = result[i*number2+j] + matrix1[i*number_mix+k]*matrix2[k*number_mix+j];
			}
		}

	public:
		Multiplication(char* matrix1, int columns1, int lines1, char*matrix2, int columns2, int lines2, int number_of_threads) {
			number1 = lines1;
			number2 = columns2;
			number_mix = lines2;
			threads = number_of_threads;
			result = (char*)calloc(sizeof(char), number1*number2);
			if (lines2 != columns1) {
				cout << "Matrixes cannot be multiplicated" << endl;
				free(result);
			}
		}

		void print_matrix() { 
			for (int i=0; i<number1; i++) {
				for (int j=0; j<number2; j++) 
					cout << (int)result[i*number1+j] << " ";
					cout << " " << endl;
			};
		}

		void thread_job(int thread_number) {
			int d = (number1*number2/threads)*thread_number;
			for (int t=0; t<((number1*number2/threads)+1); t++) { //количество посчитанных элементов
				int i = (d+t)/number2;
				int j = (d+t)%number2;
				result_element(i, j);
			}
		}

		~Multiplication() {  
			free(result);
			cout << "Memory of multiplication was deleted. Good bye!" << endl;
		} 
};