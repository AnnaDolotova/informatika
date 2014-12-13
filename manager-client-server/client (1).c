#include <stdlib.h>

#include <stdio.h>

#include <sys/types.h>

#include <sys/sem.h>

#include <sys/ipc.h>

#include <sys/sem.h>

#include <sys/msg.h>

#include "msg_enum.h"




int main()
{

    int size = 0; // size of matrix

    int* data = 0; //pointer to data of matrix

    int retval = 0; //returned value, counted by client

    int i = 0;

    int err = 0;


    key_t key = 0;


    int msqid = 0; //id of queue

    int semid = 0; //id of sem


    struct msg_data short_data = {0}; //"HELLO", "answer to HELLO", answer after counting

    struct msg_data* long_data = 0; // message which send big amount of data (what we count)

    long int employee_id = 0; //number of thread into server

    long int my_id = 0; // number of client

    int short_length = 0; //length of short_data

    int long_length = 0; // length of long_data


    struct sembuf sem[SEM_NUM] = {0}; // array of semaphores

    FILE* stream = 0; //pointer to file


    key = ftok(FTOK_PATH, 0);  //Key for messages and semaphores


    if(key < 0)
    {

        printf("Ftok error");

        return(-1);

    }



    msqid = msgget(key, 0);	//Identifier of message queue

    if(msqid < 0)

    {

        printf("Msgget error");

        return(-1);

    }


	semid = semget(key, SEM_NUM, 0);	//Identifier of semaphore array


    if(semid < 0)

    {

        printf("Semget error");

        return(-1);

    }




    my_id = getpid();

    short_data.type = MAIN_ID; // look into the box, type(номер с которым отправится сообщение)

 inside=main_id; //head of octopus


    short_data.subtype = HELLO; //first message "hand shake"

    short_data.data = (int)my_id; // introduce himself to server


    short_length = sizeof(char) * 2 + sizeof(int); //считаем длину короткой структуры



    err = msgsnd(msqid, &short_data, short_length, 0);	//send a message


    if(err < 0)

    {

        printf("Msgsnd error");

        return(-1);

    }


	err = msgrcv(msqid, &short_data, short_length, my_id, 0);//receive an answer


    if(err < 0)

    {
 
       printf("Msgrcv error");

        return(-1);

    }


	

    if(short_data.subtype == BYE) //Decide if it is an end of the conversation nor the begining
	return 0;

    else

	if(short_data.subtype == HELLO)

    {

    	    size = short_data.data; //передаем размер матрицы

    	    employee_id = my_id + INT_MAX;//вычисляем номер по которому будем передавать сообщения

    }

    else

        {
 
           printf("Unknown message subtype");

            exit(-1);

        }



    long_length = sizeof(char) + size * 2 * sizeof(int) + sizeof(int); //считаем длину данных в длинной структуре

    long_data = (struct msg_data*)calloc(sizeof(long) + long_length, 1);//выделяем память под длинную структуру


    while(1)
 {

	retval = 0; //каждый раз надо заново посчитать произведение строки на столбец, поэтому обнудяем счетчик



	err = msgrcv(msqid, long_data, long_length, my_id, 0);	//Receive a message


	if(err < 0)

    {

        printf("Msgrcv error");

        return(-1);

    }

        

	if(long_data -> subtype == DOWORK);	//Decide if go home nor work

        else if(long_data -> subtype == BYE)

	    break;

	    else

        {

		printf("Unknown message subtype");

		exit(-1);

	    }



	data = (void*)long_data + sizeof(long int) + sizeof(char) + sizeof(int);//jump to elements array



	for(i = 0; i < size; i++)

	    retval += data[i] * data[i + size];


        SEM_SET(0, -1, 0);

	semop(semid, sem, 1);// semaphor operation,1-once used. Синхронизируем запись в файл в порядке выполнения



	stream = fopen(LOG_PATH, "a+");//write to the end of the file. a+ - add

	

fprintf(stream, "Client with pid %ld. Calculated element No%d. The result is %d \n", my_id, long_data -> data, retval); //Write into a file associated with stream



	fclose(stream);
	sync();//sync for writing on drive


	SEM_SET(0, 1, 0);

	semop(semid, sem, 1);


	short_data.type = employee_id; //номер которому мы пошлем сообщение

	short_data.subtype = WORKDONE; //выходим с подтипом сделали работу-радуемся

	short_data.data = retval; //отсылаем обратно то, что насчитали



	err = msgsnd(msqid, &short_data, short_length, 0);

	if(err < 0)

	{

	    printf("Msgsnd error");

	    return(-1);

	}

    }


    long_data -> type = employee_id; //Прощаемся!!


    err = msgsnd(msqid, long_data, short_length, 0);


    if(msgsnd == 0)

    {

	printf("Msgsnd bye error");

	return(-1);

    }


    free(long_data);


    return 0;
 
}

