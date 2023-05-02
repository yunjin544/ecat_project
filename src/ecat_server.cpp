#include "KITECH_CoE_TEST.h"

char IOmap[4096];
OSAL_THREAD_HANDLE ecatcheck;
RT_TASK rttask;
boolean needlf;
boolean inOP;
uint8 currentgroup = 0;
boolean forceByteAlignment = FALSE;
cpu_set_t set;
int oloop, iloop, chk;
volatile int wkc;
int expectedWKC;

KITECH::BridgeRx *rxPDO;
KITECH::BridgeTx *txPDO;


int main(int argc, char** argv)
{
    signal(SIGINT, catch_signal);

    mlockall(MCL_CURRENT|MCL_FUTURE); //메모리 lock.

    CPU_ZERO(&set);
	CPU_SET(0,&set);
    rt_task_create(&rttask, "Ecat Loop", 0, 99, 0);
    rt_task_set_affinity(&rttask,&set);
    rt_print_init(0,"debug");

    ecat_init(argv[1]);
    shmInitMaster();
    semInit();
    osal_thread_create(&ecatcheck, 128000, (void*)&Ecatcheck, NULL);

    rt_task_start(&rttask, &ecatthread, 0);

    pause();



   return 0;

}

void ecatthread(void *arg)
{
    printf("Starting KITECH CoE test\n");   
    int flag=0;
    rt_task_set_periodic(NULL, TM_NOW, LOOP_PERIOD);
   while(true)
    {
        ec_send_processdata();
        wkc = ec_receive_processdata(EC_TIMEOUTRET);
        
        if(wkc >= expectedWKC)
            {
                semlock(Rxsemid);
                rxPDO = (KITECH::BridgeRx *)(ec_slave[1].outputs);
                *rxPDO = *Rxshmem;
                semunlock(Rxsemid);

                semlock(Txsemid);
                txPDO = (KITECH::BridgeTx *)(ec_slave[1].inputs);
                *Txshmem = *txPDO;
                semunlock(Txsemid);

                rt_printf("   CH1 : %d ",rxPDO->ch1.VAV_L2);
                rt_printf("   CH2 : %d ",rxPDO->ch2.VAV_R2);
                rt_printf("   CH3 : %d\n",rxPDO->ch3.LF_Current);
                
            }
        rt_task_wait_period(NULL);
    }
    inOP = FALSE;
}
