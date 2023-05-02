#include "KITECH_CoE_TEST.h"

void ecat_init(char *ifname)
{

   if (ec_init(ifname))    // State Machine : Init
   {
      printf("Starting Ecat DRCL Master Test\n");

      if (ec_config_init(FALSE) > 0) // State Machine : PRE_OP
      {
        printf("%d slaves found and configured.\n", ec_slavecount);

      if (strcmp(ec_slave[1].name,"Netbridge")==0)
      {
        ec_slave[1].PO2SOconfig = KITECHsetup;
      } 
      

      ec_config_map(&IOmap); // State Machine : SAFE_OP
      printf("Slaves mapped, state to SAFE_OP.\n");
      ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE * 4);

         oloop = ec_slave[0].Obytes;
         if ((oloop == 0) && (ec_slave[0].Obits > 0)) oloop = 1;
         if (oloop > 8) oloop = 8;
         iloop = ec_slave[0].Ibytes;
         if ((iloop == 0) && (ec_slave[0].Ibits > 0)) iloop = 1;
         if (iloop > 8) iloop = 8;

      printf("segments : %d : %d %d %d %d\n", ec_group[0].nsegments, ec_group[0].IOsegment[0], ec_group[0].IOsegment[1], ec_group[0].IOsegment[2], ec_group[0].IOsegment[3]);
      expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
      printf("Calculated workcounter %d\n", expectedWKC);
      ec_slave[0].state = EC_STATE_OPERATIONAL;
      ec_send_processdata();
      ec_receive_processdata(EC_TIMEOUTRET);
      ec_writestate(0);
      chk = 200;
      ec_send_processdata();
      ec_receive_processdata(EC_TIMEOUTRET);
      ec_statecheck(0, EC_STATE_OPERATIONAL, 50000);
      while (chk-- && (ec_slave[0].state != EC_STATE_OPERATIONAL)) // State Machine : OP
         ;
      }
      else
      {
          printf("No slave founded!\n");
      }
   }
   else
   {
      printf("No socket connection on %s\nExecute as root\n",ifname);
   }

}


void Ecatcheck(void *ptr)
{
   int slave;
   (void)ptr; /* Not used */

   while (1)
   {
      if (inOP && ((wkc < expectedWKC) || ec_group[currentgroup].docheckstate))
      {
         if (needlf)
         {
            needlf = FALSE;
            printf("\n");
         }
         /* one ore more slaves are not responding */
         ec_group[currentgroup].docheckstate = FALSE;
         ec_readstate();
         for (slave = 1; slave <= ec_slavecount; slave++)
         {
            if ((ec_slave[slave].group == currentgroup) && (ec_slave[slave].state != EC_STATE_OPERATIONAL))
            {
               ec_group[currentgroup].docheckstate = TRUE;
               if (ec_slave[slave].state == (EC_STATE_SAFE_OP + EC_STATE_ERROR))
               {
                  printf("ERROR : slave %d is in SAFE_OP + ERROR, attempting ack.\n", slave);
                  ec_slave[slave].state = (EC_STATE_SAFE_OP + EC_STATE_ACK);
                  ec_writestate(slave);
               }
               else if (ec_slave[slave].state == EC_STATE_SAFE_OP)
               {
                  printf("WARNING : slave %d is in SAFE_OP, change to OPERATIONAL.\n", slave);
                  ec_slave[slave].state = EC_STATE_OPERATIONAL;
                  ec_writestate(slave);
               }
               else if (ec_slave[slave].state > EC_STATE_NONE)
               {
                  if (ec_reconfig_slave(slave, EC_TIMEOUTMON))
                  {
                     ec_slave[slave].islost = FALSE;
                     printf("MESSAGE : slave %d reconfigured\n", slave);
                  }
               }
               else if (!ec_slave[slave].islost)
               {
                  /* re-check state */
                  ec_statecheck(slave, EC_STATE_OPERATIONAL, EC_TIMEOUTRET);
                  if (ec_slave[slave].state == EC_STATE_NONE)
                  {
                     ec_slave[slave].islost = TRUE;
                     printf("ERROR : slave %d lost\n", slave);
                  }
               }
            }
            if (ec_slave[slave].islost)
            {
               if (ec_slave[slave].state == EC_STATE_NONE)
               {
                  if (ec_recover_slave(slave, EC_TIMEOUTMON))
                  {
                     ec_slave[slave].islost = FALSE;
                     printf("MESSAGE : slave %d recovered\n", slave);
                  }
               }
               else
               {
                  ec_slave[slave].islost = FALSE;
                  printf("MESSAGE : slave %d found\n", slave);
               }
            }
         }
         if (!ec_group[currentgroup].docheckstate)
            printf("OK : all slaves resumed OPERATIONAL.\n");
      }
   }
}

int KITECHsetup(uint16 slave)
{
    int retval = 0;
    uint8 u8val = 0;
    uint16 u16val = 0;

    retval += ec_SDOwrite(slave, 0x1c12, 0x00, FALSE, sizeof(u8val), &u8val, EC_TIMEOUTRXM);
    u16val = 0x1601;
    retval += ec_SDOwrite(slave, 0x1c12, 0x01, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM);
    u16val = 0x1602;
    retval += ec_SDOwrite(slave, 0x1c12, 0x02, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM);
    u16val = 0x1603;
    retval += ec_SDOwrite(slave, 0x1c12, 0x03, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM);
    u16val = 0x1604;
    retval += ec_SDOwrite(slave, 0x1c12, 0x04, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM);
    u8val = 4;
    retval += ec_SDOwrite(slave, 0x1c12, 0x00, FALSE, sizeof(u8val), &u8val, EC_TIMEOUTRXM);
    printf("Netbridge 0x1c12:00, retval = %d\n", retval);

    u8val = 0;
    retval += ec_SDOwrite(slave, 0x1c13, 0x00, FALSE, sizeof(u8val), &u8val, EC_TIMEOUTRXM);
    u16val = 0x1a01;
    retval += ec_SDOwrite(slave, 0x1c13, 0x01, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM); 
    u16val = 0x1a02;
    retval += ec_SDOwrite(slave, 0x1c13, 0x02, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM);
    u16val = 0x1a03;
    retval += ec_SDOwrite(slave, 0x1c13, 0x03, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM);
    u16val = 0x1a04;
    retval += ec_SDOwrite(slave, 0x1c13, 0x04, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTRXM);
    u8val = 4;
    retval += ec_SDOwrite(slave, 0x1c13, 0x00, FALSE, sizeof(u8val), &u8val, EC_TIMEOUTRXM);
    printf("Netbridge 0x1c13:00, retval = %d\n", retval);

   while(EcatError) printf("%s", ec_elist2string());

   printf("Slave num: %d set , retval = %d\n",slave,retval);

   return 1;
}

