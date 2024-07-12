#ifndef __MT6816_H
#define __MT6816_H

#include "main.h"
#include "cordic.h"
#include "spi.h"
#define 	Pi_MT6816  		(float)3.1415927f

//MT6816
#define reg03 0x8300
#define reg04 0x8400
#define reg05 0x8500


extern float getmagval;

float MT6816_ReadVal(void);
void MT6816_Init(void);


#endif