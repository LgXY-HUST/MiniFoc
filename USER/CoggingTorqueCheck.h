//#ifndef  __CORGGINGTORQUE_CHECK
//#define  __CORGGINGTORQUE_CHECK


//#include "main.h"
//#include "BLDC.h"
//#include "pid.h"
////macro
//#define		calibration_step				50//У׼�ڵ㣬50����һ��
//#define  calibration_samplenum		16384/50	//ÿ50���ڵ�Уһ�� , 16384/100


////cmd
//uint8_t __If_compIq_calibration=0;//�Ƿ�ִ�е���������1ִ��


////struct
//typedef struct IqComp_CalStruct
//{
//	uint32_t If_ThisPointComplete , getcnt;
//	int16_t lasterr_pos , thiserr_pos  , lastpos , thispos , exppos;
//	float err , lasterr ,averpos;//��κ���һ��ƽ����ƽ��λ��,�о�
//	float Iq_this;
//}IqComp_CalStruct;


////����
//void InitcompIq_calibration(BLDC*B, IqComp_CalStruct* qc);//�ݲ�ת�ز���У׼����
//void compIq_calibration(BLDC*B , IqComp_CalStruct* qc);//�ݲ�ת�ز���У׼����
//float compIq_out(BLDC*B , IqComp_CalStruct* qc);//�õ��
//float err_position_cal(BLDC*B , IqComp_CalStruct* qc);
//void If_ThisPointComplete(BLDC*B , IqComp_CalStruct* qc);
////para
//extern 	PIDP_Struct  ComIqPidStruct;
//extern 	IqComp_CalStruct	ThisIqComp;
////�ݲ۵� q����� 
//float  Iq_comp[calibration_samplenum]={0};//�ݲ�ת��q�����������ÿ164����

//#endif
