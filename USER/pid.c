#include"pid.h"

void initPIDP(struct PIDP_Struct *e , float kp,float ki,float kd,float outlow,float outhigh)//初始化pid
{
	e->kp=kp;
	e->ki=ki;
	e->kd=kd;
	e->p=0;
	e->i=0;
	e->d=0;
	e->lastde=0;
	e->thisde=0;
	e->outhigh=outhigh;
	e->outlow=outlow;	
}
float PIDP(struct PIDP_Struct *e,float err)//返回pid结果
{
	
	e->thisde=err;
	e->p=e->kp*e->thisde;
	e->i+=e->thisde;//修改了学长的PID函数
	e->d=e->kd*(e->thisde-e->lastde);
	e->lastde=e->thisde;
	e->out=e->p+e->ki*e->i+e->d;
	if(e->out > e->outhigh)	{e->out=e->outhigh ; e->i-=err;}
	if(e->out < e->outlow)		{e->out=e->outlow  ; e->i-=err;}
	return e->out;
}
