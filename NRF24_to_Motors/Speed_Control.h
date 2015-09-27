/*
 * Speed_Control.h
 *
 *  Created on: Sep 6, 2015
 *      Author: LuisRA
 */

#ifndef SPEED_CONTROL_H_
#define SPEED_CONTROL_H_

#include <stdint.h>

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"

#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"

#include "drv8833.h"



extern int32_t Target_Dir;
extern int32_t Error_Dir;
extern int32_t LastError_Dir;

extern int32_t Kp_Dir;
extern int32_t Ki_Dir;
extern int32_t Kd_Dir;

extern int32_t P_Dir;
extern int32_t I_Dir;
extern int32_t D_Dir;
extern int32_t PID_Dir;


extern int32_t Target_Esq;
extern int32_t Error_Esq;
extern int32_t LastError_Esq;

extern int32_t Kp_Esq;
extern int32_t Ki_Esq;
extern int32_t Kd_Esq0;

extern int32_t P_Esq;
extern int32_t I_Esq;
extern int32_t D_Esq;
extern int32_t PID_Esq;

//int32_t time;


extern void SpeedControl_Init();
extern void SpeedControl_Set(int32_t _left, int32_t _right);

#endif /* SPEED_CONTROL_H_ */
