#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>




#define OUTPUT_PATH "/tmp/data.tmp"

#define BASE 10

#define MAX_NUMBER 1000





int main(int argc, char** argv)
 {


    int matrix_size = 0;

    int elem_count = 0;

    int output_fd = 0;

    int i = 0;

    int element = 0;

    int err = 0;

    int print_matrix = (argv[2]) ? 1 : 0;


    matrix_size = strtol(argv[1], NULL, BASE);


    if(matrix_size <= 0) {

	printf("Incorrect input \n");

	exit(-1);
    }



    output_fd = open(OUTPUT_PATH, O_CREAT | O_RDWR, 0666);


    if(output_fd < 0)

    {

        printf("Open error\n");

        exit(-1);

    }


	

    err = write(output_fd, &matrix_size, sizeof(int));


    if(err < 0)
 
   {

        printf("Write error\n");

        exit(-1);

    }


	

    elem_count = matrix_size * matrix_size * 2;


    srand(time(NULL)); //random to different base



    for(i = 0; i < elem_count; i++)
    {


	element = rand() % MAX_NUMBER; //<= MAX_NUMBER


	err = write(output_fd, &element, sizeof(int));


	if(err <= 0)

    {

        printf("Write error\n");

        exit(-1);

    }


	   

        if(print_matrix) {

	    if(i % matrix_size == 0)

		printf("\n");


	    printf("%10d ", element);

	}
 
   }

 
   printf("\n");

 
   close(output_fd);


    return 0;

}
