#include <sys/mman.h>
#include <signal.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>

#include "ethercat.h"

#include "IPC.h"


#define CLOCK_RES 1e-9 
#define EC_TIMEOUTMON 500
#define LOOP_PERIOD 5e5
#define NSEC_PER_SEC 1000000000

extern char IOmap[4096];
extern int expectedWKC;
extern boolean needlf;
extern volatile int wkc;
extern boolean inOP;
extern uint8 currentgroup;
extern int oloop, iloop, chk;

void ecat_init(char *ifname);
void ecatthread(void *arg);
void Ecatcheck(void *ptr);
int KITECHsetup(uint16 slave);

