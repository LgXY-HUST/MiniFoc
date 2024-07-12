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
	float K_slid , threshold_slid , k_linear;//滑膜增益 , 滑膜上下界
	float Est_Ialpha , Est_Ibeta;
	float delta_Ialpha , delta_Ibeta;	
//	float U_alpha    , U_beta;
	float Z_alpha		 , Z_beta;//直接变动的观测值
	float V_alpha		 , V_beta;//滤波后输出
	float theta_est;//观测角度
	//para
	float Ts_p_Rs_d_Ls , Ts_d_Ls ; 
}SMO;

//func
void Init_SMO(SMO*s , float Ts_p_Rs_d_Ls , float Ts_d_Ls , float K_slid , float threshold_slid);
void EMF_Estimation(SMO*s , float U_alpha, float U_beta , float I_alpha, float I_beta  );//无凸极


//extern
extern SMO ThisS;


#endif
