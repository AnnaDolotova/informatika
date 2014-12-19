#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define STRING "List of files: \n"
#define FNAME "a.fifo"
#define Size_of_Buf 1024

char* read_buf(int fd) {
	char buf[Size_of_Buf] = {0};
	char* whole_str = NULL;
	int readed = 0;

	while((readed = read(fd, buf, Size_of_Buf)) > 0) {
		if (whole_str == NULL) {
			whole_str = (char*)calloc(readed + sizeof(char), 1);
		} else {
			whole_str = realloc(whole_str, (strlen(whole_str) + 1) * sizeof(char) + readed);
		}

		strncat(whole_str, buf, readed);

		if(readed != Size_of_Buf)
		    break;
	}

	if (readed < 0) {
		printf("Can't read string\n");
		exit(-1);
	}
	return whole_str;
}

void write_into_buf(void* source, int length, int dest) // Новая функция
{
    int i = 0;
    int err = 0;

    for(i = 0; i < length; i += Size_of_Buf) {
	err = write(dest, source + i, Size_of_Buf);
	if(err < 0)
	    printf("Write error \n");
	    exit(-1);
	}
    }
    i -= Size_of_Buf;
    err = write(dest, source + i, length - Size_of_Buf);

    if(err < 0)
	printf("Write error \n");
	exit(-1);
    }
}

void read_write_buf(int fd0, int fd1) {
    char buf[Size_of_Buf] = {0};
    int readed = 0;
    int err = 0;

    while((readed = read(fd0, buf, Size_of_Buf)) > 0) {
	err = write(fd1, buf, readed);

	if(err < 0) {
	    printf("Write error");
	    exit(-1);
	}

	if (readed != Size_of_Buf)
	    break;
    }
    if(readed < 0) {
        printf("Can't read string\n");
        exit(-1);
    }
    return;
}


int main(int argc, char* argv[])
{
	int err = 0;
	if (argc < 2) {
		printf("Can't get all arguments\n");
		exit(-1);
	}

	int fd[2] = {0};
	if (pipe(fd) < 0) {
		printf("Can't create a pipe\n");
		exit(-1);
	}

	err = write(fd[1], STRING, sizeof(STRING) - 1);
	if(err < 0) {
	    printf("Write into fd[1] failed");
	    exit(-1);
	}

	err = dup2(fd[1], STDOUT_FILENO);
	if(err < 0) {
	    printf("Dup2 error \n");
	    exit(-1);
	}

	pid_t res = fork();

	if (res < 0)
	{
		printf("Can't fork a child\n");
		exit(-1);
	}
	else if (res > 0) {
		close(fd[0]);

		// AP: сделайте запись прямо в пайп - без промежуточного файла

		execl("/bin/ls", "/bin/ls", "-a", argv[1], NULL);
		printf("Exec error \n");
		exit(-1);
	}
	else {
		if (close(fd[1]) < 0) {
			printf("Can't close output stream\n");
		}

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