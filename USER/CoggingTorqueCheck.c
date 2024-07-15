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
////初始化
//void InitcompIq_calibration(BLDC*B, IqComp_CalStruct* qc)
//{
//	initPIDP(&(ComIqPidStruct) ,0.01f,0.00005f,0 ,-0.8 , 0.8 );//初始化PID

//}
////计算误差，返回期望Iq
//float compIq_out(BLDC*B , IqComp_CalStruct* qc)
//{
//	if(!qc->If_ThisPointComplete)
//	{
//		qc->thiserr_pos=qc->exppos-B->raw_angle_buffer;
//		//处理溢出
//		if(qc->thiserr_pos > 8192)//下溢出
//		{
//			qc->thiserr_pos -=16484;
//		}
//		else if(qc->thiserr_pos < -8192)//上溢出
//		{
//			qc->thiserr_pos +=16484;		
//		}
//		//误差滤波,更新误差
//		qc->err=0.1f*	qc->thiserr_pos*cnt2mechangle+0.9f*qc->lasterr;
//		qc->lasterr=qc->err;
//		//更新平均位置，用于到达判断
//		qc->averpos=0.1f*qc->thiserr_pos+0.9f*qc->averpos;
//		//返回期望q轴电流
//		return PIDP(&ComIqPidStruct , qc->err);
//	}
//	else
//	{
//		return 0;
//	}
//}
////判断是否到达
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
//				qc->If_ThisPointComplete=1;//这一点完成			
//				qc->getcnt=0;				
//			}
//		}
//	}
//}



////校准函数前台
//void compIq_calibration(BLDC*B , IqComp_CalStruct* qc)//齿槽转矩补偿校准函数
//{
//	qc->exppos=0;
//	for(int i=0 ; i<calibration_samplenum ; i++)
//	{

//		while(!qc->If_ThisPointComplete)
//		{
//			HAL_Delay(1);//等运动到			
//		}
//		Iq_comp[i]=qc->Iq_this;
//		qc->exppos+=calibration_step;
//		qc->If_ThisPointComplete=0;//下一个点
//	}



//}


