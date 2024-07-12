#include "SVPWM.h"


SVpwm		ThisSV={0};	
	
	
//const	
float 	Sqrt3_D_2=Sqrt3_SVpwm/2;




//BC相电流重构


//sv	
void SV_PWM_Cal(SVpwm*ThisSV , float Vd , float Vq , float Ud,  float sintheta ,float costheta)
{
		//float 
		ThisSV->Ualpha_d_Ud=ThisSV->Ualpha/Ud;
		ThisSV->Ubeta_d_Ud=ThisSV->Ubeta/Ud;		
    //反park
    ThisSV->Ualpha=Vd*costheta-Vq*sintheta;
    ThisSV->Ubeta=Vd*sintheta+Vq*costheta;
		
    //扇区判断dUq
		ThisSV->sqrt3_Ualpha=Sqrt3_SVpwm*ThisSV->Ualpha;
    if(ThisSV->Ubeta>=0){
        if(fabsf(ThisSV->sqrt3_Ualpha)<ThisSV->Ubeta){
            ThisSV->N=2;
				}
        else
				{
            if (ThisSV->Ualpha>0){
                ThisSV->N=1;
						}
            else{
                ThisSV->N=3;
            }
        }
		}
    else    {
        if(fabsf(ThisSV->sqrt3_Ualpha)<-ThisSV->Ubeta){
            ThisSV->N=5;
				}
        else
				{
            if (ThisSV->Ualpha>0)
						{
                ThisSV->N=6;
						}
            else
						{
                ThisSV->N=4;
            }       
        }
    }    
    //中间量ThisSV->XThisSV->YThisSV->Z
    ThisSV->X = Sqrt3_SVpwm*ThisSV->Ubeta_d_Ud;
    ThisSV->Y = 1.5f*ThisSV->Ualpha_d_Ud + Sqrt3_D_2*ThisSV->Ubeta_d_Ud;
    ThisSV->Z = -1.5f*ThisSV->Ualpha_d_Ud+Sqrt3_D_2*ThisSV->Ubeta_d_Ud;
    
    //Tx ， Ty
    switch (ThisSV->N){
        case 1  :{ThisSV->T1 = -ThisSV->Z; ThisSV->T2 = ThisSV->X;break;}
        case 2	:{ThisSV->T1 = ThisSV->Z; ThisSV->T2 = ThisSV->Y;break;}
        case 3  :{ThisSV->T1 = ThisSV->X; ThisSV->T2 = -ThisSV->Y;break;}
        case 4  :{ThisSV->T1 = -ThisSV->X; ThisSV->T2 = ThisSV->Z;break;}
        case 5  :{ThisSV->T1 = -ThisSV->Y; ThisSV->T2 = -ThisSV->Z;break;}
        case 6  :{ThisSV->T1 = ThisSV->Y; ThisSV->T2 = -ThisSV->X;break;}
        default :{ThisSV->T1 = 0; ThisSV->T2 = 0;break;}          
    }
    if((ThisSV->T1+ThisSV->T2)>1)
		{
        ThisSV->sum=ThisSV->T1+ThisSV->T2;
        ThisSV->k1=ThisSV->T1/ThisSV->sum*1;
        ThisSV->k2=ThisSV->T2/ThisSV->sum*1;
        ThisSV->T1=ThisSV->k1;
        ThisSV->T2=ThisSV->k2;
		}
    ThisSV->T0=1-ThisSV->T1-ThisSV->T2;
    
    //ThisSV->Ta , ThisSV->Tb , ThisSV->Tc 
    switch (ThisSV->N){
        case 1  :{
					ThisSV->Ta = (ThisSV->T1 + ThisSV->T2 + ThisSV->T0/2);
					ThisSV->Tb = (ThisSV->T2 + ThisSV->T0/2);
					ThisSV->Tc = ThisSV->T0/2;
					break;
				}
        case 2  :{
					ThisSV->Ta = 1-(ThisSV->T1 +  ThisSV->T0/2.f);
					ThisSV->Tb = ThisSV->T1 + ThisSV->T2 + ThisSV->T0/2.f;
					ThisSV->Tc = ThisSV->T0/2.f;
					break;
				}
        case 3  :{
					ThisSV->Ta = ThisSV->T0/2.f;
					ThisSV->Tb = ThisSV->T1 + ThisSV->T2 + ThisSV->T0/2.f;
					ThisSV->Tc = ThisSV->T2 + ThisSV->T0/2.f;
					break;
				}
        case 4  :{
					ThisSV->Ta = ThisSV->T0/2.f;
					ThisSV->Tb = 1-(ThisSV->T1+ ThisSV->T0/2.f);
					ThisSV->Tc = (ThisSV->T1 + ThisSV->T2 + ThisSV->T0/2.f);
					break;
				}
        case 5  :{
					ThisSV->Ta = ThisSV->T2 + ThisSV->T0/2.f;
					ThisSV->Tb = ThisSV->T0/2.f;
					ThisSV->Tc = ThisSV->T1 + ThisSV->T2 + ThisSV->T0/2.f;
					break;
				}	
        case 6  :{
					ThisSV->Ta = ThisSV->T1 + ThisSV->T2 + ThisSV->T0/2;
					ThisSV->Tb = ThisSV->T0/2.f;
					ThisSV->Tc = 1-(ThisSV->T1 + ThisSV->T0/2.f);
					break;
				}				
        default   :{
					ThisSV->Ta = 0;
					ThisSV->Tb = 0;
					ThisSV->Tc = 0;
					break;
				}          
    }		
}
