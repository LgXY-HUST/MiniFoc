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
#define 	Sqrt3_BLDC_d_2  (float)0.866025f//����3��2
#define		_d_sqrt3				(float)0.57735f//3/sqrt3
#define   arr_tim					(uint16_t)4249//pwm�Ƚ�ֵ����
#define   cnt2mechangle		(float)0.0003834952f//���㵽��е�ǵ�ϵ��
#define   cnt2Eangle			(float)0.004218447f//���㵽��ǵ�ϵ��
#define 	Pi_BLDC  			(float)3.1415927f
#define 	Pi2_BLDC  		(float)6.28318f
//struct
typedef struct BLDC
{
float Ia, Ib , Ic;
float Ialpha , Ibeta;
float Id , Iq , Id_exp ,  Iq_exp ;
float Vd , Vq , Vbus;
int16_t raw_angle  ;//û�л���ǰ���������
int  psc_vcal , cal_psc;//�ٶȷ�Ƶ����2k �� ��
float thetaE , fil_thetaE  ;//���
float theta ,theta_last , delta_theta ,  theta_exp;//��ǰλ�� �� ����λ�ã�
float w_mec , w_mecexp ;//��ǰ��е�ٶ� �� ��е���ٶ� rad/s
float costhetaE , sinthetaE;//sin cos
float Rs , Ls , Ts , polpairs , J;
float kt , ke  ; //���ء������Ƴ���
float kvcal    ;//�ٶȻ���ϵ��
Cordic_Struct cordic;//���ǵ�Ԫ
PIDP_Struct pid_p , pid_v ,  pid_id , pid_iq ;//λ��-�ٶ� �� �ٶ�-���� �� ����-��ѹ 
}BLDC;


//func
void Org_E_Calibration(int flag_cmd , uint16_t SetVal);//У��ԭ��
void InitBLDC(BLDC*B);

void anglehandler(BLDC*B);//λ�û���
//extern

extern BLDC ThisBLDC;
extern int16_t raw_angle_buffer;
#endif
