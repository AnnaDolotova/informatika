#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include "libbuffer.h"



#define FILE "matrix.txt"



int main(int argc, char* argv[]) {


	if(argc < 2) {

		printf("Can't get all arguments\n");

		exit(-1);

	}



	int fd = 0;

	(void)umask(0); // Umask became NULL to open file


	if((fd = open(FILE, O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0) { // Open file
		printf("Can't create a file\n");

		exit(-1);

	}



	srand(time(NULL));

 // Generation random number on time base

	int i, j, k, n = 0;


	n = atoi(argv[1]); // Conversion string argv[1] to int
 
	int number_int = 0;



	for(i = 0; i < 2 * n; i++) {

		for(j = 0; j < n; j++) {


			rand();

			number_int = rand() % 100; // Random number from 0 to 99

			char* number_char = (char*)calloc(1, sizeof(char));
  // Returns a pointer to the first byte of the allocated memory
			sprintf(number_char, "%d", number_int); // Printf to number_char
			write_buf(number_char, fd);

			write_buf(" ", fd);


			free(number_char);

		}

	}



	if(close(fd) < 0) {

		printf("Can't close a file\n");

	}


	return 0;


}
