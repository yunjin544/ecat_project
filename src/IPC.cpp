#include "IPC.h"

KITECH::BridgeRx *Rxshmem;
KITECH::BridgeTx *Txshmem;
KITECH::BridgeRx *RxPDO;
KITECH::BridgeTx *TxPDO;
int Rxshmid, Txshmid;
int Rxsemid, Txsemid;

int shmInitMaster()
{
    
    if((Rxshmid = shmget(KEY_RX,SHARED_SIZE,IPC_CREAT|0666))==-1) return -1;
    void *void_ptr = shmat(Rxshmid, NULL, 0);
    if (void_ptr == (void *) -1) {
    return 1;
    }
    Rxshmem = (KITECH::BridgeRx *)(void_ptr);

    if((Txshmid = shmget(KEY_TX,SHARED_SIZE,IPC_CREAT|0666))==-1) return -1;
    void_ptr = shmat(Txshmid, NULL, 0);
    if (void_ptr == (void *) -1) {
    return 1;
    }
    Txshmem = (KITECH::BridgeTx *)(void_ptr);

    return 1;
}

int shmInit()
{
    
    if((Rxshmid = shmget(KEY_RX,SHARED_SIZE,IPC_CREAT|0666))==-1) return -1;
    void *void_ptr = shmat(Rxshmid, NULL, 0);
    if (void_ptr == (void *) -1) {
    return 1;
    }
    RxPDO = (KITECH::BridgeRx *)(void_ptr);

    if((Txshmid = shmget(KEY_TX,SHARED_SIZE,IPC_CREAT|0666))==-1) return -1;
    void_ptr = shmat(Txshmid, NULL, 0);
    if (void_ptr == (void *) -1) {
    return 1;
    }
    TxPDO = (KITECH::BridgeTx *)(void_ptr);

    return 1;
}



int shmClearMaster(void){
    
    (Rxshmid = shmget(KEY_RX,SHARED_SIZE,IPC_CREAT|0666));
    if (shmctl(Rxshmid,IPC_RMID,NULL)==-1) return -1;

    (Txshmid = shmget(KEY_TX,SHARED_SIZE,IPC_CREAT|0666));
    if (shmctl(Txshmid,IPC_RMID,NULL)==-1) return -1;
    
    return 0;

}

int shmClear(void){
    
    (Rxshmid = shmget(KEY_RX,SHARED_SIZE,IPC_CREAT|0666));
    if (shmctl(Rxshmid,IPC_RMID,NULL)==-1) return -1;

    (Txshmid = shmget(KEY_TX,SHARED_SIZE,IPC_CREAT|0666));
    if (shmctl(Txshmid,IPC_RMID,NULL)==-1) return -1;
    
    return 0;

}

int semInit()
{
    union semun arg;
    arg.val = 1;
    int status = 0;

    Rxsemid = semget(KEY_SEM_RX, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(Rxsemid == -1){
        if(errno==EEXIST)
            Rxsemid = semget(KEY_SEM_RX,1,0);
    } else{
        status = semctl(Rxsemid,0,SETVAL,arg);
    }

    Txsemid = semget(KEY_SEM_TX, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(Txsemid == -1){
        if(errno==EEXIST)
            Txsemid = semget(KEY_SEM_RX,1,0);
    } else{
        status = semctl(Txsemid,0,SETVAL,arg);
    }

    if( Txsemid==-1 || Rxsemid ==-1)
    {
        return -1;
    }

    return 1;
}

int semlock(int semid){

    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;
    if(semop(semid, &buf, 1) == -1) {
        exit(1);
    }
    return 0;
}

int semunlock(int semid) {

    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;
    if(semop(semid, &buf, 1) == -1) {
        exit(1);
    }
    return 0;
}

int semClear()
{
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    };

    union semun arg;
    arg.val = 1;

   if (semctl(Rxsemid, 0, IPC_RMID, arg) == -1) return -1;
   if (semctl(Txsemid, 0, IPC_RMID, arg) == -1) return -1;

    return 1;
}

void catch_signal(int sig)
{
    shmClearMaster();
    semClear();
    shmClear();
    exit(1);
}