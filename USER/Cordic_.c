#include "Cordic_.h"



Cordic_Struct thisCordic;

//��ʼ��
void InitCordic(void)
{
	LL_CORDIC_Config	(CORDIC,LL_CORDIC_FUNCTION_COSINE,\
									LL_CORDIC_PRECISION_10CYCLES, \
									LL_CORDIC_SCALE_0, \
									LL_CORDIC_NBWRITE_1, \
									LL_CORDIC_NBREAD_2,  \
									LL_CORDIC_INSIZE_32BITS,    \
									LL_CORDIC_OUTSIZE_32BITS		\
									); 	
}
//����		
void TypeAssign_Cordic(void)
{
		LL_CORDIC_Config	(CORDIC,LL_CORDIC_FUNCTION_COSINE,\
										LL_CORDIC_PRECISION_10CYCLES, \
										LL_CORDIC_SCALE_0, \
										LL_CORDIC_NBWRITE_1, \
										LL_CORDIC_NBREAD_2,  \
										LL_CORDIC_INSIZE_32BITS,    \
										LL_CORDIC_OUTSIZE_32BITS		\
										); 	
}
//��ʽת��
int32_t value_to_cordic31(float value, float coeff)
{
	int32_t cordic31;
	cordic31 = (int32_t)((value/coeff)*0x80000000);		//value��coeff��һ����Ȼ������2^31����ȡ���õ�Q31��������
	return cordic31;
}
float cordic31_to_value(int cordic31)
{
	if(cordic31&0x80000000)			//Ϊ����
	{
		cordic31 = cordic31&0x7fffffff;
		return ((float)(cordic31)-0x80000000)/0x80000000;
	}
	else							//Ϊ����
	{
		return (float)(cordic31)/0x80000000;
	}
}
//����
void Cordic_SinCosCal_Input( float angle )//��pi����pi , ����sincos
{
	while (!LL_CORDIC_FLAG_RRDY);
	LL_CORDIC_WriteData(CORDIC, value_to_cordic31(angle  , Pi_Cordic));
	
}
//���
void Cordic_SinCosCal_Acquire( Cordic_Struct* C )
{

	while (!LL_CORDIC_FLAG_RRDY){};
	C->cosq32=(int32_t)LL_CORDIC_ReadData(CORDIC);
	C->sinq32=(int32_t)LL_CORDIC_ReadData(CORDIC);
	C->costheta=cordic31_to_value(C->cosq32);
	C->sintheta=cordic31_to_value(C->sinq32);	
}
		
float angleanaloging( float angle)
{
	if(angle>0)
	{
		if(angle<3.13159)
		{
			angle+=0.2;
		}
		else
		{
			angle=-3.14159;
		}
	}
	else//С��0
	{
			angle+=0.2;	
	}
	
	return angle;
}		
