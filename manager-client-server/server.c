#include <stdlib.h>

#include <stdio.h>

#include <sys/types.h>

#include <sys/sem.h>

#include <sys/ipc.h>

#include <pthread.h>

#include <fcntl.h>

#include <string.h>

#include <sys/sem.h>

#include <sys/msg.h>

#include <unistd.h>


#include "msg_enum.h"



#define TMP_PATH "/tmp/data.tmp"

#define THREAD_STEP 2


#define PRINT(name, max) \

	for(i = 0; i < max; i++) \

	    printf("%d ", name[i]);



int  size = 0; //размер матрицы

int* data1  = 0; //указатель на данные первой матрицы

int* data2  = 0; //указатель на данные второй матрицы

int* result = 0; //указатель на данные матрицы с результатом

int  msqid = 0; // id очереди



struct thread_info
 { //структура для того, чтобы знать, какая нить к чему относится

    pthread_t id;

    int target; //номер клиента (пид процесса)

};



void* thread_work(long int myid, long int target);



void* thread_init(void* arg)
 { //функция ответ на поздороваться

    int err = 0;

    struct thread_info*
 tinfo = arg; //структура, принадлежащая этому трэду (айди клиента и цель(номер))


    int short_length = sizeof(int) + sizeof(char) * 2;

    struct msg_data short_data = {0};

    long int target = tinfo -> target; //номер куда мы будем отсылать сообщение

    long int myid = (long int)tinfo -> target + INT_MAX; //


    short_data.type = target; //вормируем приветсвенное сообщение

    short_data.subtype = HELLO;

    short_data.data = size;



    err = msgsnd(msqid, &short_data, short_length, 0);

    if(err < 0)

    {

        printf("Msgsnd error");

        exit(-1);

    }



    thread_work(myid, target); //считаем для конечной матрицы

}



void* thread_work(long int myid, long int target)
{

    int i = 0;

    int element = 0;

    int line = 0;

    int column = 0;

    int err = 0;
    int long_length = (size * 2 + 1) * sizeof(int) + sizeof(char);

    int short_length = sizeof(char) * 2 + sizeof(int);


    struct msg_data* data = (struct msg_data*)calloc(long_length + sizeof(long int), 1);


    int* numbers = (int*)(data + 1);
    while(1)
 {


	data -> type = MAIN_ID; //посылает сообщение главному серверу, просит задание

	data -> subtype = GIVETASK;

	data -> data = (int)target;



	err = msgsnd(msqid, data, short_length, 0);

	if(err < 0)

    {

        printf("Msgsnd error");

        exit(-1);

    }



	err = msgrcv(msqid, data, short_length, myid, 0);


	if(err < 0)

    {

        printf("Msgrcv error");

        exit(-1);

    }


	switch(data -> subtype)

 {


	case DOWORK : //начинает формировать сообщение для клиента

			data -> type = target; //куда шлем? в пид


			element = data -> data; //номер элемента, который нам нужно посчитать

			line = element / size; //вычисляем от него строку и столбец

			column = element % size;


			numbers = (void*)data + sizeof(long int) + sizeof(char) + sizeof(int); //указатель на пустое место, которое у нас осталось, лежащее после значения


			memcpy(numbers, &data1[line * size], size * sizeof(int));  //копируем кусок строчки из первой матрицы, ту что мы хотим перемножить


			for(i = 0; i < size; i++)

			    memcpy(&numbers[size + i], &data2[column + i * size], sizeof(int)); //копируем по очереди элементы из столбца



			err = msgsnd(msqid, data, long_length, 0);

			if(err <0)

            {

                printf("Msgsnd error");

                exit(-1);

            }



			err = msgrcv(msqid, data, short_length, myid, 0);


			if(err < 0)

            {

                printf("Msgget error");

                exit(-1);

            }



			if(data -> subtype != WORKDONE) //проверяю валидность. Сделали ли мы свою работу

            {

                printf("Unknow message subtype");

                exit(-1);

            }



			result[element] = data -> data; //записываем в массив результатов

			break;




	case BYE :

			data -> type = target; //перенаправляем это сообщение клиенту


			err = msgsnd(msqid, data, long_length, 0);


			if(err < 0)

            {

                printf("Msgsnd error");

                exit(-1);

            }



			err = msgrcv(msqid, data, short_length, myid, 0);


			if(err < 0)

            {
                printf("Msgrcv error");

                exit(-1);

            }


			if(data -> subtype != BYE)

            {

                printf("Incorrect bye message from client");

                exit(-1);

            }


			   

			return NULL;



	default  :

        {

            printf("Unknow message subtype");

            exit(-1);

        }

		
	}

    }

}




int main()

{


    int thread_limit = 4; //храним максимальное число ног осминога


    struct thread_info** 
tinfo = (struct thread_info**)calloc(thread_limit, sizeof(struct thread_info*)); //храним ноги осьминога


    int client_count = 0; //текущее количство ног осьминога

    int curr_elem  = 0; //текущий элемент, которы мы считаем

    int elem_count = 0; //всего n^2

    int i = 0;

    int err = 0;

    key_t key = 0;

    int semid = 0;
 
    struct msg_data short_data = {0}; //инициализируем нулевым множеством
 
    int short_length = 0; //за исключением тайпа


    struct sembuf sem[SEM_NUM] = {0}; //массив семафоров

    int fd = 0; //файловый дескриптор файла, в котором хранятся данные массива



    key = ftok(FTOK_PATH, 0);  //Key for messages and semaphores


    if(key < 0)

    {

        printf("Ftok error");

        exit(-1);

    }


    
    msqid = msgget(key, 0);	//Identifier of message queue


    if(msqid < 0)

    {

        printf("Msgget error");

        exit(-1);

    }


   
    semid = semget(key, SEM_NUM, 0);	//Identifier of semaphore array


    if(semid < 0)

    {

        printf("Semget error");

        exit(-1);

    }



    SEM_SET(0, 1, 0);

    semop(semid, sem, 1);


    fd = open(TMP_PATH, O_RDONLY);


    if(fd < 0)

    {

        printf("Open error");

        exit(-1);

    }



    err = read(fd, &size, sizeof(int)); //считываем n


    if(err < 0 || size < 0)

    {

        printf("Read n error");

        exit(-1);

    }



    elem_count = size * size; //сколько нам нужно посчитать



    data1 = (int*)calloc(elem_count * 3, sizeof(int)); //выделяем данные под все матрицы

    if(!data1)

    {

        printf("Calloc error");

        exit(-1);

    }



    data2 = data1 + elem_count; //указатель на вторую матрицу

    result = data2 + elem_count; //указательна итоговую матрицу



    err = read(fd, data1, elem_count * 2 * sizeof(int)); //считываем из файла две первые матрицы


    if(err < 0)

    {

        printf("Read data error");

        exit(-1);

    }



    short_length = sizeof(char) * 2 + sizeof(int); //вычисляем длину короткой структуры



    while(curr_elem != elem_count)
 {


	msgrcv(msqid, &short_data, short_length, MAIN_ID, 0);


	switch(short_data.subtype)
 { //типа ифа. выбираем из множества нужное значение



	case HELLO    :

			if(client_count == thread_limit)
 {

			    thread_limit *= THREAD_STEP;

			    tinfo = (struct thread_info**)realloc(tinfo, sizeof(struct thread_info*) * thread_limit);

			}



			tinfo[client_count] = (struct thread_info*)calloc(1, sizeof(struct thread_info));//выдеяем место под одно щупальце, прикрепляем его туда

			tinfo[client_count] -> target = short_data.data; //указатель на щупальце кладем в дырку



			err = pthread_create(&(tinfo[client_count] -> id), 0, thread_init, tinfo[client_count]); //вызываем код щупальца, чтоб оживить его


			if(err < 0)

            {

                printf("Pthread_create error");

                exit(-1);

            }
	
		     

			client_count++; //увеличиваем количество шупалец на 1, так как создали до этого одно щупальце


			break;



	case GIVETASK : //каждое щупальце просит задание

			short_data.subtype = DOWORK; //шортдатадата- пид процесса, за который ухватилось щупальце

			short_data.type    = (long int)short_data.data + INT_MAX; //преобразование в номер треда

			short_data.data    = curr_elem++; // кладем старый получаем новый элемент


			err = msgsnd(msqid, &short_data, short_length, 0);


			if(err < 0)

            {

                printf("Msgsnd error");

                exit(-1);

            }



			break;



	default :

        {

            printf("Received message subtype is invalid");

            exit(-1);

        }

	}

    }



    i = client_count - 1; //счетчик массива. в массиве элементы от 0 до к-1, чтоб получить последний элемент нужно отнять 1



    while(client_count > 0)
 {


	msgrcv(msqid, &short_data, short_length, MAIN_ID, 0);



	if(short_data.subtype == GIVETASK)
 { //пришел повторный раз, просит задание, но уже нет задания((

	    client_count--; // отправлеям назад

	    short_data.type = (long int)short_data.data + INT_MAX;

	}

	else

	    if(short_data.subtype == HELLO) //подключился новый клиент

		short_data.type = short_data.data;

	    else

        {

            printf("Received message subtype is invalid");

            return(-1);

        }

		

	short_data.subtype = BYE;



	err = msgsnd(msqid, &short_data, short_length, 0);


	if(err < 0)

    {

        printf("Msgsnd error");

        return(-1);

    }

    }



    for(; i >= 0; i--) {


	err = pthread_join(tinfo[i] -> id, 0); //ждем пока все треды завершаются. все уже попрощались.

	if(err < 0)

    {

        printf("Pthread_join error");

        return(-1);

    }

    
    }



    for(i = 0; i < elem_count; i++)
 { //распечатываем в консоль

	if(i % size == 0)

	    printf("\n");

	printf(" %10d ", result[i]);

    }


    printf("\n");



    err = msgctl(msqid, IPC_RMID, 0);


    if(err < 0)

    {

        printf("Msgctl error");

        return(-1);

    }


    

    err = semctl(semid, IPC_RMID, 0);

    if(err < 0)

    {

        printf("Shmctl error");

        return(-1);

    }


    return 0;

}
