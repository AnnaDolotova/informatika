#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h>

#include <fcntl.h>

#include <string.h>

#include <sys/stat.h>

#include "libreadwrite.h"



#define FILES_OF_DIR "list.txt"

#define ls_1 "ls -a "

#define ls_2 " >> "

#define STRING "List of files: \n"

#define FNAME "a.fifo"



int main(int argc, char* argv[])
{


	if (argc < 2) {

		printf("Can't get all arguments\n");

		exit(-1);

	}


	int fd[2];


	if (pipe(fd) < 0) {

		printf("Can't create a pipe\n");

		exit(-1);

	}


	pid_t res = fork();


	if (res < 0)
    {

		printf("Can't fork a child\n");

		exit(-1);


	}
 else if (res > 0) {

		
		pid_t res1 = fork();


		if (res1 < 0) {

			printf("Can't fork a child\n");

			exit(-1);


		}
 else if (res1 > 0) {


			int fd_file = 0;

			if ((fd_file = open(FILES_OF_DIR, O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0) {

				printf("Can't creat a file\n");

				exit(-1);

			}


	
		int length = 0;

			length = strlen(ls_1) + strlen(argv[1]) + strlen(ls_2) + strlen(FILES_OF_DIR) + 1;

			char* ls = 0;

			ls = (char*) calloc(length, sizeof(char));

			strcat(ls, ls_1);

			strcat(ls, argv[1]);

			strcat(ls, ls_2);

			strcat(ls, FILES_OF_DIR);


			size_t nbytes = 0;

			// AP: сделайте запись прямо в пайп - без промежуточного файла
			if ((nbytes = write(fd_file, STRING, strlen(STRING))) < strlen(STRING)) {

				printf("Can't write all bytes\n");

				exit(-1);

			}



			if ((close(fd_file)) < 0) {

				printf("Can't close the file\n");

				exit(-1);

			}



			int result = 0;


			if ((result = execl("/bin/bash", "/bin/bash", "-c", ls, (char*) NULL)) < 0) {

				printf("Can't write a list of the directory\n");

				free(ls);

				exit(-1);

			}


		}

		
int i = 0;

		// AP: с пайпом это не понадобится
		for (i = 0; i < 1000000000; i++);


		(void)umask(0);

		if ((fd[0] = open(FILES_OF_DIR, O_RDONLY, 0666)) < 0) {

			printf("Can't open a file\n");

			exit(-1);

		}


		read_write_buf(fd[0], fd[1]);


		if (close(fd[0]) < 0) {

			printf("Can't close input stream\n");

		}

		if (close(fd[1]) < 0) {

			printf("Can't close output stream\n");

		}


	}
 else {


		if (close(fd[1]) < 0) {

			printf("Can't close output stream\n");

		}


		(void)umask(0);

		if (mknod(FNAME, S_IFIFO | 0666, 0) < 0) {

			printf("Can't create FIFO\n");

			exit(-1);

		}


		int fd_fifo = 0;

		if ((fd_fifo = open(FNAME, O_WRONLY)) < 0) {

			printf("Can't open FIFO for writing\n");

			exit(-1);

		}


		read_write_buf(fd[0], fd_fifo);


		if (close(fd[0]) < 0) {

			printf("Can't close input stream\n");

		}

		if (close(fd_fifo) < 0) {

			printf("Can't close FIFO\n");

		}


	}


	return 0;


}
