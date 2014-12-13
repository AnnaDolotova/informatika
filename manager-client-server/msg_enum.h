#define FTOK_PATH "/bin/sh"

#define SEM_NUM 1

#define MAIN_ID 1

#define INT_MAX 0xFFFFFFFF

#define LOG_PATH "./logfile"


#define SEM_SET(NUM, OP, FLAG) \

	sem[NUM].sem_num = NUM; \

	sem[NUM].sem_op  = OP;   \

	sem[NUM].sem_flg = FLAG;

enum subtype_t

 {
    HELLO,
    GIVETASK,
    DOWORK,
    WORKDONE,
    BYE
};


struct msg_data
 {
    long type;
    char subtype;
    int data;
    char wtf;
}
;
