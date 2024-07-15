//#ifndef  __CORGGINGTORQUE_CHECK
//#define  __CORGGINGTORQUE_CHECK


//#include "main.h"
//#include "BLDC.h"
//#include "pid.h"
////macro
//#define		calibration_step				50//校准节点，50个点一次
//#define  calibration_samplenum		16384/50	//每50个节点校一次 , 16384/100


////cmd
//uint8_t __If_compIq_calibration=0;//是否执行电流补偿，1执行


////struct
//typedef struct IqComp_CalStruct
//{
//	uint32_t If_ThisPointComplete , getcnt;
//	int16_t lasterr_pos , thiserr_pos  , lastpos , thispos , exppos;
//	float err , lasterr ,averpos;//这次和上一次平均误差，平均位置,判据
//	float Iq_this;
//}IqComp_CalStruct;


////函数
//void InitcompIq_calibration(BLDC*B, IqComp_CalStruct* qc);//齿槽转矩补偿校准函数
//void compIq_calibration(BLDC*B , IqComp_CalStruct* qc);//齿槽转矩补偿校准函数
//float compIq_out(BLDC*B , IqComp_CalStruct* qc);//用电机
//float err_position_cal(BLDC*B , IqComp_CalStruct* qc);
//void If_ThisPointComplete(BLDC*B , IqComp_CalStruct* qc);
////para
//extern 	PIDP_Struct  ComIqPidStruct;
//extern 	IqComp_CalStruct	ThisIqComp;
////齿槽点 q轴电流 
//float  Iq_comp[calibration_samplenum]={0};//齿槽转矩q轴电流补偿，每164个点

//#endif
