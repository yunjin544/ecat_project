#include <inttypes.h>

struct TxPDO_CH0
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

struct TxPDO_CH1
{   //L_Thigh(JCU1)
    uint16_t Pressure_2A;
    uint16_t Pressure_2B;
    uint16_t Pressure_3A;
    uint16_t Pressure_3B;
    uint16_t Pressure_4A;
    uint16_t Pressure_5A;
    uint16_t Pressure_6A;
    uint16_t POT_0;
    uint16_t POT_1;
    uint16_t Empty1[23];

    //L_Calf(JCU2)
    uint16_t LoadCell0;
    uint16_t LoadCell1;
    uint16_t LoadCell2;
    uint16_t LoadCell3;
    uint16_t Angle_X;
    uint16_t Angle_Y;
    uint16_t Angle_Z;
    uint16_t Velocity_X;
    uint16_t Velocity_Y;
    uint16_t Velocity_Z;
    uint16_t Accelerometer_X;
    uint16_t Accelerometer_Y;
    uint16_t Accelerometer_Z;
    uint16_t L_Calf_POT_0;
    uint16_t L_Calf_POT_1;
    uint16_t Empty2[17];

    
};

struct TxPDO_CH2
{
    //R_Thigh(JCU1)
    uint16_t Pressure_2A;
    uint16_t Pressure_2B;
    uint16_t Pressure_3A;
    uint16_t Pressure_3B;
    uint16_t Pressure_4A;
    uint16_t Pressure_5A;
    uint16_t Pressure_6A;
    uint16_t L_Thigh_POT_0;
    uint16_t L_Thigh_POT_1;
    uint16_t Empty1[23];

    //R_Calf(JCU2)
    uint16_t LoadCell0;
    uint16_t LoadCell1;
    uint16_t LoadCell2;
    uint16_t LoadCell3;
    uint16_t Angle_X;
    uint16_t Angle_Y;
    uint16_t Angle_Z;
    uint16_t Velocity_X;
    uint16_t Velocity_Y;
    uint16_t Velocity_Z;
    uint16_t Accelerometer_X;
    uint16_t Accelerometer_Y;
    uint16_t Accelerometer_Z;
    uint16_t R_Calf_POT_0;
    uint16_t R_Calf_POT_1;
    uint16_t Empty2[17];
};

struct TxPDO_CH3
{
    //Power Pack(PCU)
    uint16_t Tank_Temp;
    uint16_t MOT_Temp;
    uint16_t PreP;
    uint16_t Reserved_1;
    uint16_t Reserved_2;
    uint16_t Reserved_3;
    uint16_t Empty1[26];

    //Driving(DCU)
    int16_t	Brake_Servo_Current_L;
    int16_t	Brake_Servo_Current_R;
    int16_t	Steering_Servo_Current;
    int16_t	Wheel_MOT_Current_LF;
    int16_t	Wheel_MOT_Current_LH;
    int16_t	Wheel_MOT_Current_RF;
    int16_t	Wheel_MOT_Current_RH;
    int16_t	Wheel_MOT_Velocity_LF;
    int16_t	Wheel_MOT_Velocity_LH;
    int16_t	Wheel_MOT_Velocity_RF;
    int16_t	Wheel_MOT_Velocity_RH;
    uint8_t Reserved_4;
    uint8_t Reserved_5;
    uint8_t Reserved_6;
    uint8_t Reserved_7;
    uint16_t Empty2[17];
};

struct TxPDO_CH4
{   //Pelvis(JCU0)
    uint16_t POT_L0;
    uint16_t POT_L1;
    uint16_t POT_R0;
    uint16_t POT_R1;
    uint16_t Pressure_L0A;
    uint16_t Pressure_L0B;
    uint16_t Pressure_L1A;
    uint16_t Pressure_L1B;
    uint16_t Pressure_R0A;
    uint16_t Pressure_R0B;
    uint16_t Pressure_R1A;
    uint16_t Pressure_R1B;
    uint16_t Angle_X;
    uint16_t Angle_Y;
    uint16_t Angle_Z;
    uint16_t Velocity_X;
    uint16_t Velocity_Y;
    uint16_t Velocity_Z;
    uint16_t Accelerometer_X;
    uint16_t Accelerometer_Y;
    uint16_t Accelerometer_Z;
    uint16_t Empty1[11];

    //Battery(BMS)
    uint16_t Current;
    uint16_t Voltage;
    uint16_t Temp;
    uint16_t Remain;
    uint16_t Empty2[28];

};