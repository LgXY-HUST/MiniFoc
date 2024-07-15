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
int16_t raw_angle  , raw_angle_buffer ;//û�л���ǰ���������
int  psc_vcal , cal_psc;//�ٶȷ�Ƶ����2k �� ��

float thetaE , fil_thetaE  ;//���
int16_t thiserr_pos , exppos , errpos , lasterr , averposerr;//λ��������
//int16_t errpos;
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


#ifndef  __CORGGINGTORQUE_CHECK
#define  __CORGGINGTORQUE_CHECK


//#include "main.h"
//#include "BLDC.h"
//#include "pid.h"
//macro
#define		calibration_step				50//У׼�ڵ㣬50����һ��
#define  calibration_samplenum		16384/50	//ÿ50���ڵ�Уһ�� , 16384/100


//cmd



//struct
typedef struct IqComp_CalStruct
{
	uint32_t If_ThisPointComplete , getcnt;
	int16_t lasterr_pos , thiserr_pos  , lastpos , thispos , exppos;
	float err , lasterr ,averpos;//��κ���һ��ƽ����ƽ��λ��,�о�
	float Iq_this;
}IqComp_CalStruct;


//����
void InitcompIq_calibration(BLDC*B, IqComp_CalStruct* qc);//�ݲ�ת�ز���У׼����
void compIq_calibration(BLDC*B , IqComp_CalStruct* qc);//�ݲ�ת�ز���У׼����
float compIq_out(BLDC*B , IqComp_CalStruct* qc);//�õ��
float err_position_cal(BLDC*B , IqComp_CalStruct* qc);
void If_ThisPointComplete(BLDC*B , IqComp_CalStruct* qc);
//para
extern 	PIDP_Struct  ComIqPidStruct;
extern 	IqComp_CalStruct	ThisIqComp;
//�ݲ۵� q����� 
extern uint8_t __If_compIq_calibration;
extern float  Iq_comp[calibration_samplenum];
#endif
