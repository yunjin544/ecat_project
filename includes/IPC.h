#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "RxPDO_CH.h"
#include "TxPDO_CH.h"

#define KEY_RX 625
#define KEY_TX 815
#define KEY_SEM_RX 301
#define KEY_SEM_TX 103
#define SHARED_SIZE 600

namespace KITECH
{
    struct BridgeTx
        {   
            TxPDO_CH0 ch0;
            TxPDO_CH1 ch1;
            TxPDO_CH2 ch2;
            TxPDO_CH3 ch3;
            TxPDO_CH4 ch4;
            
        };

        struct BridgeRx
        {
            RxPDO_CH0 ch0;
            RxPDO_CH1 ch1;
            RxPDO_CH2 ch2;
            RxPDO_CH3 ch3;
            RxPDO_CH4 ch4;
        };
}

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


extern int Rxshmid, Txshmid;
extern int Rxsemid, Txsemid;

extern KITECH::BridgeRx *Rxshmem;
extern KITECH::BridgeTx *Txshmem;
extern KITECH::BridgeRx *RxPDO;
extern KITECH::BridgeTx *TxPDO;


int shmInitMaster(void);
int shmClearMaster(void);
int shmInit(void);
int shmClear(void);
int semInit(void);
int semClear(void);
int semunlock(int semid);
int semlock(int semid);
void catch_signal(int sig);


