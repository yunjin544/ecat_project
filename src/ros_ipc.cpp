#include "IPC.h"
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv)
{
    signal(SIGINT, catch_signal);
    shmInit();
    semInit();
    int i =1;
    while(1)
    {   i++;
        semlock(Rxsemid);
        RxPDO->ch1.VAV_L2 =i;
        RxPDO->ch2.VAV_R2 =i+1;
        RxPDO->ch3.LF_Current =i+2;
        semunlock(Rxsemid);

        semlock(Txsemid);
        printf("CH1: %u  ",TxPDO->ch1.Pressure_2A);
        printf("CH2: %u  ",TxPDO->ch2.Pressure_2A);
        printf("CH3: %u  \n",TxPDO->ch3.Brake_Servo_Current_L);
        semunlock(Txsemid);
        sleep(0.1);
    }
    
    return 0;
}
