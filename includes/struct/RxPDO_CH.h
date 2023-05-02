#include <inttypes.h>

struct RxPDO_CH0
{   //Basic Common Info.
    uint8_t Status;
    uint8_t etc_CMD;
    uint32_t Comm_CNT;
    uint8_t Reserved_0;
    uint8_t Reserved_1;
    uint8_t Reserved_2;
    uint8_t Reserved_3;
    uint8_t Reserved_4;
    uint8_t Reserved_5;
    uint8_t Reserved_6;
    uint8_t Reserved_7;
    uint8_t Reserved_8;
    uint8_t Reserved_9;
};

struct RxPDO_CH1
{   //L_Thigh(JCU1)
    uint16_t VAV_L2;
    uint16_t VAV_L3;
    uint16_t VAV_L4;
    uint16_t VAV_L5;
    uint16_t VAV_L6;
    uint16_t Empty[59];
};

struct RxPDO_CH2
{   //R_Thigh(JCU1)
    uint16_t VAV_R2;
    uint16_t VAV_R3;
    uint16_t VAV_R4;
    uint16_t VAV_R5;
    uint16_t VAV_R6;
    uint16_t Empty[59];
};

struct RxPDO_CH3
{   // Power Pack(PCU)
    uint16_t PWRPack_PWM;   
    uint8_t PWRPack_CMD;  
    uint8_t Empty1[61];

    //Driving(DCU)
    int16_t LF_Current;
    int16_t LH_Current;
    int16_t RF_Current;
    int16_t RH_Current;
    int8_t Steering_MOT;
    uint8_t Brake_MOT_L;
    uint8_t Brake_MOT_R;
    uint8_t Hydralic_Brake;
    uint8_t SWITCH;
    uint8_t Reserved_0;
    uint8_t Reserved_1;
    uint8_t Empty2[49];

};

struct RxPDO_CH4
{
    //Pelvis(JCU0)
    uint16_t VAV_L0;      
    uint16_t VAV_L1;   
    uint16_t VAV_R0;   
    uint16_t VAV_R1;
    uint16_t Empty4[60];
        
};