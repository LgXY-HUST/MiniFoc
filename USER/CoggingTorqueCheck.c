//#include "CoggingTorqueCheck.h"


////
//	PIDP_Struct  ComIqPidStruct;
//	IqComp_CalStruct	ThisIqComp;
////tool func	
//int16_t absint16(int16_t absint16_t)
//{
//	if(absint16_t>=0) {return absint16_t;}
//	else{return -absint16_t;}
//}
//	
////��ʼ��
//void InitcompIq_calibration(BLDC*B, IqComp_CalStruct* qc)
//{
//	initPIDP(&(ComIqPidStruct) ,0.01f,0.00005f,0 ,-0.8 , 0.8 );//��ʼ��PID

//}
////��������������Iq
//float compIq_out(BLDC*B , IqComp_CalStruct* qc)
//{
//	if(!qc->If_ThisPointComplete)
//	{
//		qc->thiserr_pos=qc->exppos-B->raw_angle_buffer;
//		//�������
//		if(qc->thiserr_pos > 8192)//�����
//		{
//			qc->thiserr_pos -=16484;
//		}
//		else if(qc->thiserr_pos < -8192)//�����
//		{
//			qc->thiserr_pos +=16484;		
//		}
//		//����˲�,�������
//		qc->err=0.1f*	qc->thiserr_pos*cnt2mechangle+0.9f*qc->lasterr;
//		qc->lasterr=qc->err;
//		//����ƽ��λ�ã����ڵ����ж�
//		qc->averpos=0.1f*qc->thiserr_pos+0.9f*qc->averpos;
//		//��������q�����
//		return PIDP(&ComIqPidStruct , qc->err);
//	}
//	else
//	{
//		return 0;
//	}
//}
////�ж��Ƿ񵽴�
//void If_ThisPointComplete(BLDC*B , IqComp_CalStruct* qc)
//{
//	if(!qc->If_ThisPointComplete)
//	{
//		while(!qc->If_ThisPointComplete)
//		{
//			if(absint16(qc->thiserr_pos)<5)
//			{
//				qc->getcnt+=1;
//			}
//			else
//			{
//				qc->getcnt=0;
//			}
//			if(qc->getcnt==20)
//			{
//				qc->If_ThisPointComplete=1;//��һ�����			
//				qc->getcnt=0;				
//			}
//		}
//	}
//}



////У׼����ǰ̨
//void compIq_calibration(BLDC*B , IqComp_CalStruct* qc)//�ݲ�ת�ز���У׼����
//{
//	qc->exppos=0;
//	for(int i=0 ; i<calibration_samplenum ; i++)
//	{

//		while(!qc->If_ThisPointComplete)
//		{
//			HAL_Delay(1);//���˶���			
//		}
//		Iq_comp[i]=qc->Iq_this;
//		qc->exppos+=calibration_step;
//		qc->If_ThisPointComplete=0;//��һ����
//	}



//}


