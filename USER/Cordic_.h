#ifndef __Cordic_H
#define __Cordic_H


#include "main.h"
#include "cordic.h"

#define 	Pi_Cordic  		(float)3.1415927f

typedef struct Cordic_Struct
{
	int32_t cosq32;
	int32_t sinq32;
	float costheta;
	float sintheta;
}Cordic_Struct;

extern Cordic_Struct thisCordic;

void InitCordic(void);
int32_t value_to_cordic31(float value, float coeff);
float cordic31_to_value(int cordic31);
void Cordic_SinCosCal_Input( float angle );
void Cordic_SinCosCal_Acquire( Cordic_Struct* C );
float angleanaloging( float angle);


#endif
