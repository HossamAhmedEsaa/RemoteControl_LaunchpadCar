/*
 * Speed_Control.c
 *
 *  Created on: Sep 6, 2015
 *      Author: LuisRA
 */

#include "Speed_Control.h"

int32_t Target_Dir = 0;
int32_t Error_Dir=0;
int32_t LastError_Dir=0;

int32_t Kp_Dir = 0;
int32_t Ki_Dir = 1;
int32_t Kd_Dir = 0;

int32_t P_Dir = 0;
int32_t I_Dir = 0;
int32_t D_Dir = 0;
int32_t PID_Dir = 0;


int32_t Target_Esq = 0;
int32_t Error_Esq=0;
int32_t LastError_Esq=0;

int32_t Kp_Esq = 0;
int32_t Ki_Esq = 1;
int32_t Kd_Esq = 0;

int32_t P_Esq = 0;
int32_t I_Esq = 0;
int32_t D_Esq = 0;
int32_t PID_Esq = 0;

int32_t Direction_Dir = 0;
int32_t Direction_Esq = 0;
//int32_t time = 1000;

int32_t EncoderDir, EncoderEsq, EncoderDirDirection,EncoderEsqDirection,EncoderDirVel,EncoderEsqVel;
void UpdateSpeed_ISR(){
	 uint32_t status = TimerIntStatus(WTIMER4_BASE,true);
	  TimerIntClear(WTIMER4_BASE,status);


	if(Target_Dir !=0){
		Direction_Dir=QEIDirectionGet(QEI0_BASE);
		EncoderDirVel=( (QEIVelocityGet(QEI0_BASE)*13)/48*12) * Direction_Dir;
		Error_Dir = Target_Dir - EncoderDirVel;
		I_Dir =  (I_Dir+Error_Dir) * Ki_Dir;
		D_Dir = D_Dir * (Error_Dir - LastError_Dir);
		PID_Dir = P_Dir + I_Dir + D_Dir;
		if(PID_Dir > 1022)
			PID_Dir = 1022;
		else if(PID_Dir < -1022)
			PID_Dir = -1022;
	}
	else{
		PID_Dir = 0;
		I_Dir=0;
		Error_Dir=0;
	}

	if(Target_Esq !=0){
		Direction_Esq=QEIDirectionGet(QEI1_BASE);
		EncoderEsqVel=( (QEIVelocityGet(QEI1_BASE)*13)/48*12) *  Direction_Esq;
		Error_Esq = Target_Esq - EncoderEsqVel;
		I_Esq =  (I_Esq+Error_Esq) * Ki_Esq;
		D_Esq = D_Esq * (Error_Esq - LastError_Esq);
		PID_Esq = P_Esq + I_Esq + D_Esq ;
		if(PID_Esq > 1022)
			PID_Esq = 1022;
		else if(PID_Esq < -1022)
			PID_Esq = -1022;
	}
	else{
		PID_Esq = 0;
		I_Esq=0;
		Error_Esq=0;
	}

	DRV8833_MotorB(PID_Dir);
	DRV8833_MotorA(PID_Esq);

	LastError_Dir = Error_Dir;
	LastError_Esq = Error_Esq;
}

void _InitTimer(){

	  //We set the load value so the timer interrupts each 1ms
	  uint32_t Period;
	  Period = 80000000/24; //every 100ms

	  SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER4);
	  SysCtlDelay(3);
	  /*
	    Configure the timer as periodic, by omission it's in count down mode.
	    It counts from the load value to 0 and then resets back to the load value.
	  REMEMBER: You need to configure the timer before setting the load and match
	  */
	  TimerConfigure(WTIMER4_BASE, TIMER_CFG_PERIODIC);
	  TimerLoadSet(WTIMER4_BASE, TIMER_A, Period -1);

	  TimerIntRegister(WTIMER4_BASE, TIMER_A, UpdateSpeed_ISR);

	  /*
	    Enable the timeout interrupt. In count down mode it's when the timer reaches
	  0 and resets back to load. In count up mode it's when the timer reaches load
	  and resets back to 0.
	  */
	  TimerIntEnable(WTIMER4_BASE, TIMER_TIMA_TIMEOUT);

	  TimerEnable(WTIMER4_BASE, TIMER_A);

}

void _EncoderInit(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
	SysCtlDelay(1);

	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;

	//Set Pins to be PHA0 and PHB0
	GPIOPinConfigure(GPIO_PD6_PHA0);
	GPIOPinConfigure(GPIO_PD7_PHB0);

	GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_6 |  GPIO_PIN_7);


	QEIDisable(QEI0_BASE);
	QEIIntDisable(QEI0_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);

	QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET 	| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 1000);
	QEIVelocityConfigure(QEI0_BASE,	QEI_VELDIV_1,80000000/12);
	QEIEnable(QEI0_BASE);
	QEIVelocityEnable(QEI0_BASE);
	//Set position to a middle value so we can see if things are working
	QEIPositionSet(QEI0_BASE, 500);


	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
	SysCtlDelay(1);

	//Set Pins to be PHA0 and PHB0
	GPIOPinConfigure(GPIO_PC5_PHA1);
	GPIOPinConfigure(GPIO_PC6_PHB1);

	GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5 |  GPIO_PIN_6);


	QEIDisable(QEI1_BASE);
	QEIIntDisable(QEI1_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);

	QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET 	| QEI_CONFIG_QUADRATURE | QEI_CONFIG_SWAP), 1000);
	QEIVelocityConfigure(QEI1_BASE,	QEI_VELDIV_1,80000000/12);
	QEIEnable(QEI1_BASE);
	QEIVelocityEnable(QEI1_BASE);
	//Set position to a middle value so we can see if things are working
	QEIPositionSet(QEI1_BASE, 500);
}

void SpeedControl_Init(){

	DRV8833_InitMotorsAB();

	_EncoderInit();

	_InitTimer();

}



void SpeedControl_Set(int32_t _left, int32_t _right){

	if(_right > 1022){
		_right = 1022;
	}
	else if(_right < -1022){
		_right = -1022;
	}
	Target_Dir = _right;


	if(_left > 1022){
		_left = 1022;
	}
	else if(_left < -1022){
		_left = -1022;
	}
	Target_Esq = _left;


}
/*
void RightSpeedSet(){
	EncoderDirVel=(QEIVelocityGet(QEI1_BASE)*13.188)/48*20;
	//EncoderEsqVel=(QEIVelocityGet(QEI0_BASE)*13.188)/48;

	Error_Dir = Target_Dir - EncoderDirVel;

	P_Dir = Error_Dir * Kp_Dir;
	I_Dir =  (I_Dir+Error_Dir) * Ki_Dir;

	PID_Dir = P_Dir + I_Dir + D_Dir;

	if(PID_Dir >= 1023)
		PID_Dir = 1022;

	DRV8833_MotorA(PID_Dir);



}*/

/*
void LeftSpeedSet(){
	EncoderEsqVel=(QEIVelocityGet(QEI0_BASE)*13.188)/48*20;
	//EncoderEsqVel=(QEIVelocityGet(QEI0_BASE)*13.188)/48;

	Error_Esq = Target_Esq - EncoderEsqVel;

	P_Esq = Error_Esq * Kp_Esq;
	I_Esq =  (I_Esq+Error_Esq) * Ki_Esq;

	PID_Esq = P_Esq + I_Esq + D_Esq;

	if(PID_Esq >= 1023)
		PID_Esq = 1022;

	DRV8833_MotorB(PID_Esq);



}
*/
/*
void SpeedControl(){
	DRV8833_InitMotorsAB();

	while(1)
	{

		LeftSpeedSet();
		RightSpeedSet();
		Wait(time);


	}

}
*/

