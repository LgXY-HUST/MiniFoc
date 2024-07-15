#include "BLDC.h"

//��ǰ��װ 365��ԭ��


BLDC ThisBLDC;
int16_t raw_angle_buffer=0;
//ADC&&Timer
//float adcA =0 ;
//float adcB =0 ;
//float adcC =0 ;
//float I_alpha ,I_beta  ;
//float _d_sqrt3=0.57735f;

//Clark
void ClarkTransform(BLDC*B)//BC��
{
	B->Ialpha=-B->Ib-B->Ic;
	B->Ibeta= _d_sqrt3 * B->Ib - _d_sqrt3 * B->Ic;
}

//Park
void ParkTransform(BLDC*B)//BC��
{
	B->Id=B->Ialpha*B->costhetaE+B->Ibeta*B->sinthetaE;
	B->Iq=-B->Ialpha*B->sinthetaE+B->Ibeta*B->costhetaE;
}

//void 
void InitBLDC(BLDC*B)//  ��ʼ��+����ʱ��
{
	memset(B , 0 ,sizeof(BLDC));
	B->Vbus=12;		 //ĸ��12V
	B->kt=0.2;		 //Nm/A
	B->ke=45;			 //45rpm/V	
	B->polpairs=11;//11�Լ�
	B->Ts=0.00005;
	B->J=0.0000081;	//81gcm^2
	B->Id_exp=0;		//Id=0����
	B->psc_vcal=20;	//�ٶȼ����Ƶ
	B->kvcal=1/B->Ts/B->psc_vcal;

//����һ�β�õ�λ��
	B->raw_angle=MT6816_ReadVal();
	anglehandler(B);//����
	B->theta_last=B->theta;
//PWM	&& TIMERit
	HAL_TIM_PWM_Start(&htim1 , TIM_CHANNEL_1 );
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,0);
	
	HAL_TIM_PWM_Start(&htim1 , TIM_CHANNEL_2 );
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,0);
	
	HAL_TIM_PWM_Start(&htim1 , TIM_CHANNEL_3 );
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_3 ,0);	
		
	__HAL_TIM_SetCompare(&htim1,    TIM_CHANNEL_4   , 4250-2);
	HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_4);	
	
	//��һ��ʱ��
	HAL_Delay(1500);
	//	initPIDP(&(B->pid_v) ,0.0486f,19.44f*B->Ts*B->psc_vcal,0 ,-0.6 , 0.6 );
//	initPIDP(&(B->pid_id) ,1.975f,4750.f*B->Ts,0 ,-(B->Vbus-1)/Sqrt3_BLDC , (B->Vbus-1)/Sqrt3_BLDC );	
//	initPIDP(&(B->pid_iq) ,1.975f,4750.f*B->Ts,0 ,-(B->Vbus-1)/Sqrt3_BLDC , (B->Vbus-1)/Sqrt3_BLDC );	

//	initPIDP(&(B->pid_v) ,0.0001f,0.0001,0 ,-0.8 , 0.8 );
//�����ǳݲ�ת������
//	initPIDP(&(B->pid_v) ,0.05f,0.000005f,0 ,-0.8 , 0.8 );
//	initPIDP(&(B->pid_id) ,7.9f,1.9f,0 ,-5 , 5 );	
//	initPIDP(&(B->pid_iq) ,7.9f,1.9f,0 ,-5 , 5 );
	
//���ǳݲ�ת������ �� ����λ��
	initPIDP(&(B->pid_p) ,0.0011f,0.0000011f,0.002f ,-0.3 , 0.3 );
	initPIDP(&(B->pid_v) ,0.05f,0.000005f,0 ,-0.8 , 0.8 );
	
//����λ��-�ٶȻ�	
	initPIDP(&(B->pid_p) ,0.00001f,0.00001f,0 ,-0.5 , 0.5 );	
	initPIDP(&(B->pid_id) ,7.9f,1.9f,0 ,-5 , 5 );	
	initPIDP(&(B->pid_iq) ,7.9f,1.9f,0 ,-5 , 5 );	

	//test

}





//λ��У��
void Org_E_Calibration(int flag_cmd , uint16_t SetVal)
{
		switch(flag_cmd)
		{			
			case 1 :{
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,SetVal);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,0);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_3 ,0);
								break;
							}
			case 2 :{
							__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,SetVal);
							__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,SetVal);
							__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_3 ,0);
							break;
						}								
			case 3 :{
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,0);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,SetVal);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_3 ,0);
								break;
							}
			case 4 :{
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,0);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,SetVal);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_3 ,SetVal);
								break;
							}				

			case 5 :{
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,0);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,0);
								__HAL_TIM_SET_COMPARE	(&htim1 , TIM_CHANNEL_3 ,SetVal);		
								break;
							}	
			case 6 :{
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,SetVal);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,0);
								__HAL_TIM_SET_COMPARE	(&htim1 , TIM_CHANNEL_3 ,SetVal);		
								break;
							}	
			case 7 :{
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,0);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,0);
								__HAL_TIM_SET_COMPARE	(&htim1 , TIM_CHANNEL_3 ,0);		
								break;
							}										
			default : {
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,0);
								__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,0);
								__HAL_TIM_SET_COMPARE	(&htim1 , TIM_CHANNEL_3 ,0);						
								break;
							}
		}		
}


//λ��������
void positionerror_cal(BLDC*B )
{

		B->thiserr_pos=B->exppos-B->raw_angle_buffer;
		//�������
		if(B->thiserr_pos > 8192)//�����
		{
			B->thiserr_pos -=16484;
		}
		else if(B->thiserr_pos < -8192)//�����
		{
			B->thiserr_pos +=16484;		
		}
		//����˲�,�������
		B->errpos=0.1f*	B->thiserr_pos*cnt2mechangle+0.9f*B->lasterr;
		B->lasterr=B->errpos;
		//����ƽ��λ�ã����ڵ����ж�
		B->averposerr=0.1f*B->thiserr_pos+0.9f*B->averposerr;
		//��������q�����
		//return PIDP(&ComIqPidStruct , qc->err);
}

//λ�û���
void anglehandler(BLDC*B)
{
	//ȡ��е��
	//B->theta=0.05f*cnt2mechangle*B->raw_angle+0.95f*B->theta;
	B->theta=cnt2mechangle*B->raw_angle;
	//B->fil_thetaE=B->raw_angle/10+9*B->fil_thetaE/10;
	//����λ�ò�
	
	
	//�ֶ�
	if(B->raw_angle<400)//365ԭ����
	{
		B->raw_angle+=16384;
	}
	B->raw_angle=(ThisBLDC.raw_angle-400)%1489;//ȡģ//365ԭ����
	//ӳ��-pi - pi
	if(B->raw_angle>744)
	{
		B->raw_angle=B->raw_angle-1489;
	}
	//ȡ���
	//B->thetaE=0.01f*cnt2Eangle*B->raw_angle+0.99f*B->thetaE;
	B->thetaE=cnt2Eangle*B->raw_angle;
}



//�ٶȼ���
void velocitycal(BLDC*B)
{
	//static int cal_psc=1;
	
	//��һ�β��ʱ�������
	
  if(B->psc_vcal<=B->cal_psc)
	{
		//�Բ�ֵ
		B->delta_theta=B->theta-B->theta_last;		
		
		//������ܵ����	
		
		if(B->delta_theta<=-1)//�����������ֵΪ���� ��������
		{
			B->delta_theta=B->delta_theta+Pi2_BLDC;
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_9 , GPIO_PIN_SET);	
			//B->delta_theta=0;				
		}
		else if(B->delta_theta>=1)//�����������ֵΪ��
		//else
		{
			B->delta_theta=B->delta_theta-Pi2_BLDC;	
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_9 , GPIO_PIN_SET);		
			//B->delta_theta=0;			
		}
		//�������ٶ�		
		B->w_mec=0.995f*B->w_mec+0.005f*B->delta_theta*B->kvcal;
		ThisBLDC.Iq_exp=PIDP(&(ThisBLDC.pid_v) , ThisBLDC.w_mecexp-ThisBLDC.w_mec);

//		if(fabsf(B->w_mec)>10)
//		{
//			HAL_UART_Transmit(&huart2,0x01,1,10);
//		}
		//������
		B->theta_last=B->theta;
	
		B->cal_psc=1;
	}
	else
	{
		B->cal_psc++;
	}
	
}

//test ��
float tagId=0;
float tagIq=0;
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
    {
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_9 , GPIO_PIN_SET);
			
			//current&&position
			HAL_ADC_Start(&hadc1);
			HAL_ADC_Start(&hadc2);
			//mechanical angle
			ThisBLDC.raw_angle_buffer=MT6816_ReadVal();ThisBLDC.raw_angle=ThisBLDC.raw_angle_buffer;
			//ThisBLDC.raw_angle=MT6816_ReadVal();
			anglehandler(&ThisBLDC);//����
			//velocity cal
			velocitycal(&ThisBLDC);
			//electrical angle
			while(!(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC));
			while(!(HAL_ADC_GetState(&hadc2), HAL_ADC_STATE_REG_EOC));
			ThisBLDC.Ib=-0.3f*(0.00048828f*((int)HAL_ADC_GetValue(&hadc2)-1980))+0.7f*ThisBLDC.Ib;//�������˲���
			ThisBLDC.Ic=-0.3f*(0.00048828f*((int)HAL_ADC_GetValue(&hadc1)-1980))+0.7f*ThisBLDC.Ic;//�������˲���
			ThisBLDC.Ia=-ThisBLDC.Ib-ThisBLDC.Ic;
			//sim&cos theta
			Cordic_SinCosCal_Input(ThisBLDC.thetaE);
			//Cordic_SinCosCal_Input(theta);//�������ٶ���
			Cordic_SinCosCal_Acquire(&(ThisBLDC.cordic));
			ThisBLDC.sinthetaE=ThisBLDC.cordic.sintheta ;
			ThisBLDC.costhetaE=ThisBLDC.cordic.costheta ;			
			//clark
			ClarkTransform(&ThisBLDC);
			//park
			ParkTransform(&ThisBLDC);
			//SMO
			//EMF_Estimation(&ThisS , ThisSV.Ualpha , ThisSV.Ubeta , ThisBLDC.Ialpha, ThisBLDC.Ibeta);//��͹��	
			//PID
			//ThisBLDC.Iq_exp=0.05;
			//ThisBLDC.Id_exp=tagId;
			//ThisBLDC.Iq_exp=tagIq;
			//ThisBLDC.Iq_exp=compIq_out(&ThisBLDC , &ThisIqComp);
			positionerror_cal(&ThisBLDC);
			//����λ��-�ٶȻ�
			//ThisBLDC.w_mecexp=PIDP(&(ThisBLDC.pid_p) , ThisBLDC.averposerr);
			//ThisBLDC.Iq_exp=PIDP(&(ThisBLDC.pid_v) , ThisBLDC.w_mecexp-ThisBLDC.w_mec);
			//������ѹ��
			ThisBLDC.Iq_exp=PIDP(&(ThisBLDC.pid_p) , ThisBLDC.averposerr);
			ThisBLDC.Vq=PIDP(&(ThisBLDC.pid_iq) , ThisBLDC.Iq_exp-ThisBLDC.Iq);	//��ʱ����ǰ��		
			ThisBLDC.Vd=PIDP(&(ThisBLDC.pid_id) , ThisBLDC.Id_exp-ThisBLDC.Id);					
			//SV
			SV_PWM_Cal(&ThisSV , ThisBLDC.Vd, ThisBLDC.Vq,  ThisBLDC.Vbus , ThisBLDC.sinthetaE , ThisBLDC.costhetaE  );
		  //SV_PWM_Cal(&ThisSV , 0.5 , 0, 10 , arm_sin_f32(theta) , arm_cos_f32(theta)  );		 
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,(uint16_t)(arr_tim*ThisSV.Ta));
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,(uint16_t)(arr_tim*ThisSV.Tb));//����700
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_3 ,(uint16_t)(arr_tim*ThisSV.Tc));	
			
    	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_9 , GPIO_PIN_RESET);		
		}
}

//�ݲ�ת�ز�������



//
float  Iq_comp[calibration_samplenum]={0};//�ݲ�ת��q�����������ÿ164����
uint8_t __If_compIq_calibration=0;//�Ƿ�ִ�е���������1ִ��
		PIDP_Struct  ComIqPidStruct;
	IqComp_CalStruct	ThisIqComp;
//tool func	
int16_t absint16(int16_t absint16_t)
{
	if(absint16_t>=0) {return absint16_t;}
	else{return -absint16_t;}
}
	
//��ʼ��
void InitcompIq_calibration(BLDC*B, IqComp_CalStruct* qc)
{
	initPIDP(&(ComIqPidStruct) ,0.01f,0.00005f,0 ,-0.8 , 0.8 );//��ʼ��PID

}
//��������������Iq
float compIq_out(BLDC*B , IqComp_CalStruct* qc)
{
	if(!qc->If_ThisPointComplete)
	{
		qc->thiserr_pos=qc->exppos-B->raw_angle_buffer;
		//�������
		if(qc->thiserr_pos > 8192)//�����
		{
			qc->thiserr_pos -=16484;
		}
		else if(qc->thiserr_pos < -8192)//�����
		{
			qc->thiserr_pos +=16484;		
		}
		//����˲�,�������
		qc->err=0.1f*	qc->thiserr_pos*cnt2mechangle+0.9f*qc->lasterr;
		qc->lasterr=qc->err;
		//����ƽ��λ�ã����ڵ����ж�
		qc->averpos=0.1f*qc->thiserr_pos+0.9f*qc->averpos;
		//��������q�����
		return PIDP(&ComIqPidStruct , qc->err);
	}
	else
	{
		return 0;
	}
}
//�ж��Ƿ񵽴�
void If_ThisPointComplete(BLDC*B , IqComp_CalStruct* qc)
{
	if(__If_compIq_calibration)
	{
		if(!qc->If_ThisPointComplete)
		{
			while(!qc->If_ThisPointComplete)
			{
				if(absint16(qc->thiserr_pos)<5)
				{
					qc->getcnt+=1;
				}
				else
				{
					qc->getcnt=0;
				}
				if(qc->getcnt==20)
				{
					qc->If_ThisPointComplete=1;//��һ�����			
					qc->getcnt=0;				
				}
			}
		}
		__If_compIq_calibration=0;//У׼���
	}
}



//У׼����ǰ̨
void compIq_calibration(BLDC*B , IqComp_CalStruct* qc)//�ݲ�ת�ز���У׼����
{
	qc->exppos=0;
	for(int i=0 ; i<calibration_samplenum ; i++)
	{

		while(!qc->If_ThisPointComplete)
		{
			HAL_Delay(1);//���˶���			
		}
		Iq_comp[i]=qc->Iq_this;
		qc->exppos+=calibration_step;
		qc->If_ThisPointComplete=0;//��һ����
	}



}



