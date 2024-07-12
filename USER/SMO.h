#ifndef __SMO_H
#define __SMO_H

#include "main.h"
#include "string.h"
#include "arm_math.h"
#include "math.h"
//const

//struct

typedef struct SMO
{
	float K_slid , threshold_slid , k_linear;//��Ĥ���� , ��Ĥ���½�
	float Est_Ialpha , Est_Ibeta;
	float delta_Ialpha , delta_Ibeta;	
//	float U_alpha    , U_beta;
	float Z_alpha		 , Z_beta;//ֱ�ӱ䶯�Ĺ۲�ֵ
	float V_alpha		 , V_beta;//�˲������
	float theta_est;//�۲�Ƕ�
	//para
	float Ts_p_Rs_d_Ls , Ts_d_Ls ; 
}SMO;

//func
void Init_SMO(SMO*s , float Ts_p_Rs_d_Ls , float Ts_d_Ls , float K_slid , float threshold_slid);
void EMF_Estimation(SMO*s , float U_alpha, float U_beta , float I_alpha, float I_beta  );//��͹��


//extern
extern SMO ThisS;


#endif
