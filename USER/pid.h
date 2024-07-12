#ifndef __PID_H
#define __PID_H



typedef struct PIDP_Struct//λ��ʽPID�ṹ , ���µ�λ���ͷ���
{
	float kp,ki,kd;
	float  p, i, d;
	float thisde,lastde;
	float outhigh , outlow ;
	float out;
}PIDP_Struct;

void initPIDP(struct PIDP_Struct *e , float kp,float ki,float kd,float outhigh,float outlow);
float PIDP(struct PIDP_Struct *e,float err);

#endif
