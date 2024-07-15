#ifndef __BLDC_H
#define __BLDC_H

#include "main.h"
#include "SVPWM.h"
#include "Cordic_.h"
#include "math.h"
#include "arm_math.h"
#include "MT6816.h"
#include "SMO.h"
#include "pid.h"
#include "string.h"
#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "CoggingTorqueCheck.h"

//constant

#define 	Sqrt3_BLDC  		(float)1.732051f
#define 	Sqrt3_BLDC_d_2  (float)0.866025f//根号3除2
#define		_d_sqrt3				(float)0.57735f//3/sqrt3
#define   arr_tim					(uint16_t)4249//pwm比较值上限
#define   cnt2mechangle		(float)0.0003834952f//换算到机械角的系数
#define   cnt2Eangle			(float)0.004218447f//换算到电角的系数
#define 	Pi_BLDC  			(float)3.1415927f
#define 	Pi2_BLDC  		(float)6.28318f
//struct
typedef struct BLDC
{
float Ia, Ib , Ic;
float Ialpha , Ibeta;
float Id , Iq , Id_exp ,  Iq_exp ;
float Vd , Vq , Vbus;
int16_t raw_angle  , raw_angle_buffer ;//没有换算前的整形输出
int  psc_vcal , cal_psc;//速度分频，用2k ， 先

float thetaE , fil_thetaE  ;//电角
int16_t thiserr_pos , exppos , errpos , lasterr , averposerr;//位置误差计算
//int16_t errpos;
float theta ,theta_last , delta_theta ,  theta_exp;//当前位置 ， 期望位置；
float w_mec , w_mecexp ;//当前机械速度 ， 机械角速度 rad/s
float costhetaE , sinthetaE;//sin cos
float Rs , Ls , Ts , polpairs , J;
float kt , ke  ; //力矩、反电势常数
float kvcal    ;//速度换算系数
Cordic_Struct cordic;//三角单元
PIDP_Struct pid_p , pid_v ,  pid_id , pid_iq ;//位置-速度 ， 速度-电流 ， 电流-电压 
}BLDC;


//func
void Org_E_Calibration(int flag_cmd , uint16_t SetVal);//校对原点
void InitBLDC(BLDC*B);

void anglehandler(BLDC*B);//位置换算
//extern

extern BLDC ThisBLDC;
extern int16_t raw_angle_buffer;
#endif


#ifndef  __CORGGINGTORQUE_CHECK
#define  __CORGGINGTORQUE_CHECK


//#include "main.h"
//#include "BLDC.h"
//#include "pid.h"
//macro
#define		calibration_step				50//校准节点，50个点一次
#define  calibration_samplenum		16384/50	//每50个节点校一次 , 16384/100


//cmd



//struct
typedef struct IqComp_CalStruct
{
	uint32_t If_ThisPointComplete , getcnt;
	int16_t lasterr_pos , thiserr_pos  , lastpos , thispos , exppos;
	float err , lasterr ,averpos;//这次和上一次平均误差，平均位置,判据
	float Iq_this;
}IqComp_CalStruct;


//函数
void InitcompIq_calibration(BLDC*B, IqComp_CalStruct* qc);//齿槽转矩补偿校准函数
void compIq_calibration(BLDC*B , IqComp_CalStruct* qc);//齿槽转矩补偿校准函数
float compIq_out(BLDC*B , IqComp_CalStruct* qc);//用电机
float err_position_cal(BLDC*B , IqComp_CalStruct* qc);
void If_ThisPointComplete(BLDC*B , IqComp_CalStruct* qc);
//para
extern 	PIDP_Struct  ComIqPidStruct;
extern 	IqComp_CalStruct	ThisIqComp;
//齿槽点 q轴电流 
extern uint8_t __If_compIq_calibration;
extern float  Iq_comp[calibration_samplenum];
#endif
