#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <string.h>

#include <stdio.h>


#define Size_of_Buf 16


char*
 read_buf(int fd) {


	char* buf = (char*)malloc(Size_of_Buf * sizeof(char));

	char* whole_str = NULL;

	int readed = 0;

	while((readed = read(fd, buf, Size_of_Buf)) > 0) {

		if (whole_str == NULL) {

			whole_str = (char*)calloc(readed + sizeof(char), 1);

		} else {

			whole_str = realloc(whole_str, (strlen(whole_str) + 1) * sizeof(char) + readed);

		}

		strncat(whole_str, buf, readed);

	}

	if (readed < 0) {

		printf("Can't read string\n");

		exit(-1);

	}


	free(buf);


	return whole_str;
}

// AP: сделайте отдельно функцию только для записи из строки при этом так же с циклом - с учетом того что может записаться не вся строка сразу
void read_write_buf(int fd0, int fd1) {

    
    char* buf = (char*)malloc(Size_of_Buf * sizeof(char));

    char* whole_str = NULL;

    int readed = 0;

    
    while((readed = read(fd0, buf, Size_of_Buf)) > 0) {

        if (whole_str == NULL) {

            whole_str = (char*)calloc(readed + sizeof(char), 1);

        } else {

            whole_str = realloc(whole_str, (strlen(whole_str) + 1) * sizeof(char) + readed);

        }

        strncat(whole_str, buf, readed);

    }

    if (readed < 0) {

        printf("Can't read string\n");

        exit(-1);

    }

    
    int nbytes = 0;

    if ((nbytes = write(fd1, whole_str, strlen(whole_str))) != strlen(whole_str)) {

        printf("Can't write all string\n");

        exit(-1);

    }

    
    free(buf);

    free(whole_str);

    
    return;

}
