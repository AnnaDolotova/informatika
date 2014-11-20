#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h>

#include <fcntl.h>

#include <string.h>

#include "libreadwrite.h"



#define FNAME "a.fifo"



int main(int argc, char* argv[]) {


	int fd_f;

	
	if ((fd_f = open(FNAME, O_RDONLY)) < 0) {

		printf("Can't open FIFO for reading\n");

		exit(-1);

	}



	printf("%s", read_buf(fd_f));

	
	if (close(fd_f) < 0) {

		printf("Can't close FIFO\n");

	}


	int res = 0;

	if ((res = execl("/bin/rm", "/bin/rm", FNAME, (char*) NULL)) < 0) {

		printf("Can't remove FIFO\n");

		exit(-1);

	}


	return 0;


}
