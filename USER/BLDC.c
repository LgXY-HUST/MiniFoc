#include "BLDC.h"

//当前安装 365是原点


BLDC ThisBLDC;
int16_t raw_angle_buffer=0;
//ADC&&Timer
//float adcA =0 ;
//float adcB =0 ;
//float adcC =0 ;
//float I_alpha ,I_beta  ;
//float _d_sqrt3=0.57735f;

//Clark
void ClarkTransform(BLDC*B)//BC相
{
	B->Ialpha=-B->Ib-B->Ic;
	B->Ibeta= _d_sqrt3 * B->Ib - _d_sqrt3 * B->Ic;
}

//Park
void ParkTransform(BLDC*B)//BC相
{
	B->Id=B->Ialpha*B->costhetaE+B->Ibeta*B->sinthetaE;
	B->Iq=-B->Ialpha*B->sinthetaE+B->Ibeta*B->costhetaE;
}

//void 
void InitBLDC(BLDC*B)//  初始化+开定时器
{
	memset(B , 0 ,sizeof(BLDC));
	B->Vbus=12;		 //母线12V
	B->kt=0.2;		 //Nm/A
	B->ke=45;			 //45rpm/V	
	B->polpairs=11;//11对极
	B->Ts=0.00005;
	B->J=0.0000081;	//81gcm^2
	B->Id_exp=0;		//Id=0控制
	B->psc_vcal=20;	//速度计算分频
	B->kvcal=1/B->Ts/B->psc_vcal;

//补第一次测得的位置
	ThisBLDC.raw_angle=MT6816_ReadVal();
	anglehandler(B);//换算
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
	
	//等一段时间
	HAL_Delay(1500);
	//	initPIDP(&(B->pid_v) ,0.0486f,19.44f*B->Ts*B->psc_vcal,0 ,-0.6 , 0.6 );
//	initPIDP(&(B->pid_id) ,1.975f,4750.f*B->Ts,0 ,-(B->Vbus-1)/Sqrt3_BLDC , (B->Vbus-1)/Sqrt3_BLDC );	
//	initPIDP(&(B->pid_iq) ,1.975f,4750.f*B->Ts,0 ,-(B->Vbus-1)/Sqrt3_BLDC , (B->Vbus-1)/Sqrt3_BLDC );	

//	initPIDP(&(B->pid_v) ,0.0001f,0.0001,0 ,-0.8 , 0.8 );
	initPIDP(&(B->pid_v) ,0.05f,0.00005f,0 ,-0.8 , 0.8 );
	initPIDP(&(B->pid_id) ,7.9f,1.9f,0 ,-5 , 5 );	
	initPIDP(&(B->pid_iq) ,7.9f,1.9f,0 ,-5 , 5 );	

	//test

}
//位置校对
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


//位置换算
void anglehandler(BLDC*B)
{
	//取机械角
	//B->theta=0.05f*cnt2mechangle*B->raw_angle+0.95f*B->theta;
	B->theta=cnt2mechangle*B->raw_angle;
	//B->fil_thetaE=B->raw_angle/10+9*B->fil_thetaE/10;
	//分段
	if(B->raw_angle<400)//365原先是
	{
		B->raw_angle+=16384;
	}
	B->raw_angle=(ThisBLDC.raw_angle-400)%1489;//取模//365原先是
	//映射-pi - pi
	if(B->raw_angle>744)
	{
		B->raw_angle=B->raw_angle-1489;
	}
	//取电角
	//B->thetaE=0.01f*cnt2Eangle*B->raw_angle+0.99f*B->thetaE;
	B->thetaE=cnt2Eangle*B->raw_angle;
}
//速度计算
void velocitycal(BLDC*B)
{
	//static int cal_psc=1;
	
	//第一次测的时候就算了
	
  if(B->psc_vcal<=B->cal_psc)
	{
		//试差值
		B->delta_theta=B->theta-B->theta_last;		
		
		//处理可能的溢出	
		
		if(B->delta_theta<=-1)//向上溢出，差值为负， 补偿回正
		{
			B->delta_theta=B->delta_theta+Pi2_BLDC;
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_9 , GPIO_PIN_SET);	
			//B->delta_theta=0;				
		}
		else if(B->delta_theta>=1)//向下溢出，差值为正
		//else
		{
			B->delta_theta=B->delta_theta-Pi2_BLDC;	
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_9 , GPIO_PIN_SET);		
			//B->delta_theta=0;			
		}
		//求差，换算速度		
		B->w_mec=0.995f*B->w_mec+0.005f*B->delta_theta*B->kvcal;
		ThisBLDC.Iq_exp=PIDP(&(ThisBLDC.pid_v) , ThisBLDC.w_mecexp-ThisBLDC.w_mec);

//		if(fabsf(B->w_mec)>10)
//		{
//			HAL_UART_Transmit(&huart2,0x01,1,10);
//		}
		//存数据
		B->theta_last=B->theta;
	
		B->cal_psc=1;
	}
	else
	{
		B->cal_psc++;
	}
	
}

//test ？
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
			raw_angle_buffer=MT6816_ReadVal();ThisBLDC.raw_angle=MT6816_ReadVal();
			//ThisBLDC.raw_angle=MT6816_ReadVal();
			anglehandler(&ThisBLDC);//换算
			//velocity cal
			velocitycal(&ThisBLDC);
			//electrical angle
			while(!(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC));
			while(!(HAL_ADC_GetState(&hadc2), HAL_ADC_STATE_REG_EOC));
			ThisBLDC.Ib=-0.3f*(0.00048828f*((int)HAL_ADC_GetValue(&hadc2)-1980))+0.7f*ThisBLDC.Ib;//在这里滤波了
			ThisBLDC.Ic=-0.3f*(0.00048828f*((int)HAL_ADC_GetValue(&hadc1)-1980))+0.7f*ThisBLDC.Ic;//在这里滤波了
			ThisBLDC.Ia=-ThisBLDC.Ib-ThisBLDC.Ic;
			//sim&cos theta
			Cordic_SinCosCal_Input(ThisBLDC.thetaE);
			//Cordic_SinCosCal_Input(theta);//开环给速度用
			Cordic_SinCosCal_Acquire(&(ThisBLDC.cordic));
			ThisBLDC.sinthetaE=ThisBLDC.cordic.sintheta ;
			ThisBLDC.costhetaE=ThisBLDC.cordic.costheta ;			
			//clark
			ClarkTransform(&ThisBLDC);
			//park
			ParkTransform(&ThisBLDC);
			//SMO
			//EMF_Estimation(&ThisS , ThisSV.Ualpha , ThisSV.Ubeta , ThisBLDC.Ialpha, ThisBLDC.Ibeta);//无凸极	
			//PID
			//ThisBLDC.Iq_exp=0.05;
			//ThisBLDC.Id_exp=tagId;
			//ThisBLDC.Iq_exp=tagIq;
			ThisBLDC.Iq_exp=PIDP(&(ThisBLDC.pid_v) , ThisBLDC.w_mecexp-ThisBLDC.w_mec);
			ThisBLDC.Vq=PIDP(&(ThisBLDC.pid_iq) , ThisBLDC.Iq_exp-ThisBLDC.Iq);	//暂时不加前馈		
			ThisBLDC.Vd=PIDP(&(ThisBLDC.pid_id) , ThisBLDC.Id_exp-ThisBLDC.Id);					
			//SV
			SV_PWM_Cal(&ThisSV , ThisBLDC.Vd, ThisBLDC.Vq,  ThisBLDC.Vbus , ThisBLDC.sinthetaE , ThisBLDC.costhetaE  );
		  //SV_PWM_Cal(&ThisSV , 0.5 , 0, 10 , arm_sin_f32(theta) , arm_cos_f32(theta)  );		 
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 ,(uint16_t)(arr_tim*ThisSV.Ta));
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_2 ,(uint16_t)(arr_tim*ThisSV.Tb));//下限700
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_3 ,(uint16_t)(arr_tim*ThisSV.Tc));	
			
    	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_9 , GPIO_PIN_RESET);		
		}
}