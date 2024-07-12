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
int16_t raw_angle  ;//没有换算前的整形输出
int  psc_vcal , cal_psc;//速度分频，用2k ， 先
float thetaE , fil_thetaE  ;//电角
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
