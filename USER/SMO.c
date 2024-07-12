#include "SMO.h"


//void Init_SMO
SMO ThisS;


void Init_SMO(SMO*s , float Ts_p_Rs_d_Ls , float Ts_d_Ls , float K_slid , float threshold_slid)
{
	memset(s , 0 , sizeof(SMO));
	s->K_slid=K_slid;
	s->threshold_slid=threshold_slid;
	s->k_linear=K_slid/threshold_slid;
	s->Ts_d_Ls=Ts_d_Ls;
	s->Ts_p_Rs_d_Ls=Ts_p_Rs_d_Ls;
}


void EMF_Estimation(SMO*s , float U_alpha, float U_beta , float I_alpha, float I_beta  )//��͹��
{

//����һ�μ�����ε�Ԥ�����

	s->Est_Ialpha= s->Est_Ialpha-s->Ts_p_Rs_d_Ls*s->Est_Ialpha+s->Ts_d_Ls*(U_beta - s->Z_alpha);
	s->Est_Ibeta=s->Est_Ibeta-s->Ts_p_Rs_d_Ls*s->Est_Ibeta+s->Ts_d_Ls*(U_beta - s->Z_beta);
	
//�Ƚ�ʵ��ֵ	

	s->delta_Ialpha=s->Est_Ialpha-I_alpha;
	s->delta_Ibeta=s->Est_Ibeta-I_beta;
	
//���������
	//alpha
	if(s->delta_Ialpha>s->threshold_slid)	//������
	{
		s->Z_alpha=-s->K_slid;
	}
	else if(s->delta_Ialpha<-s->threshold_slid)	
	{
		s->Z_alpha=s->K_slid;		
	}
	else
	{
		s->Z_alpha=s->k_linear*s->delta_Ialpha;
	}
	//beta
	if(s->delta_Ibeta>s->threshold_slid)	//������
	{
		s->Z_beta=-s->K_slid;
	}
	else if(s->delta_Ibeta<-s->threshold_slid)	
	{
		s->Z_beta=s->K_slid;		
	}
	else
	{
		s->Z_beta=s->k_linear*s->delta_Ibeta;
	}	
	
//����ֵ�˲� 0.9 , 0.1
	s->V_alpha= 0.9f*s->V_alpha +0.1f*s->Z_alpha;
	s->V_beta= 0.9f*s->V_beta +0.1f*s->Z_beta;	
	
//�ȷ����������	
	s->theta_est=atan2f(s->V_beta, s->V_alpha );
}
