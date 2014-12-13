#include <unistd.h>

#include <stdlib.h>

#include <errno.h>

#include <stdio.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/sem.h>

#include <sys/msg.h>

#include "msg_enum.h"



#define BASE 10



int main(int argc, char** argv)
{

    int msqid=0;

    int semid=0;

    int i = 0;

    key_t key = 0;
    int fork_res = 0;

    

    int count = strtol(argv[1], NULL, BASE);


    if(count < 1 || errno != 0)
 {

	printf("Incorrect output \n");

	exit(-1);

    }

    
    
    key = ftok(FTOK_PATH, 0);


    if(key < 0)

    {

        printf("Ftok error");

        return(-1);

    }


    
    msqid = msgget(key, IPC_CREAT | 0666);


    if(msqid < 0)

    {

        printf("Msgget error");
        return(-1);

    }
 

    
    semid = semget(key, SEM_NUM, IPC_CREAT | 0666);


    if(semid < 0)

    {

        printf("Semget error");

        return(-1);

    }



    fork_res = fork();


    if(fork_res == 0)
 {

	execlp("./server.o", "./server.o", NULL);

	printf("Exec error");

	exit(-1);

    }
 else if (fork_res == -1)
 {

	perror("fork_error \n");

	exit(-1);

    }




    for(i = 0; i < count; i++)

    {

	fork_res = fork();


	if(fork_res == 0)
 {

	    execlp("./client.o", "./client.o", NULL);

	    printf("Exec error \n");

	    exit(-1);

	}

 else if(fork_res == -1)
 {

	    perror("fork error /n");

	    exit(-1);

	}
 
   }


    return 0;

}
