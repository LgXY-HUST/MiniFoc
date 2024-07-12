#ifndef __SVPWM_H
#define __SVPWM_H

#include "main.h"
#include "math.h"


//����
#define 	Sqrt3_SVpwm  (float)1.732051f
#define 	Pi_SVpwm  		(float)3.1415927f
extern float 	Sqrt3_D_2;

//�ṹ��
typedef struct SVpwm
{
	float Vd , Vq , Ualpha , Ubeta , sqrt3_Ualpha;
	float Ualpha_d_Ud ,Ubeta_d_Ud ;
	float X , Y , Z;
	float T0 , T1 , T2 , k1 , k2;
	float Ta , Tb , Tc ;//����ռ�ձ�
	float sum ;
	uint32_t N;
}SVpwm;



//����
void SV_PWM_Cal(SVpwm*ThisSV , float Vd , float Vq , float Ud,  float sintheta ,float costheta);



//extern
extern 	SVpwm		ThisSV;


#endif
