/*
 * main.h
 *
 *  Created on: Sep 10, 2015
 *      Author: LuisRA
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "Energia.h"
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>
#include "Screen_HX8353E.h"

#include "LCD_Helper.h"

#include <stdio.h>
//#include "driverlib/driverlib.h"




#define Button1_pin 33 // P5_1
#define Button2_pin 32 // P3_5

#define NRF24_CE_PIN 30 //P5_5
#define NRF24_CSN_PIN 29 //P5_4
#define NRF24_IRQ_PIN 28 //P4_7

#define Xaxis_pin 2
#define Yaxis_pin 26
#define SpeedAxis_pin A4
#define Joystick_Button 5 // P4_1
#define X_Offset -54
#define Y_Offset -40
#define SpeedAxis_Offset  0
#define MAXIMUM_SPEED  120

#define Tilt_Xpin 23
#define Tilt_Ypin 24
#define Tilt_Zpin 25
#define Tilt_X_Calibrate 2070
#define Tilt_Y_Calibrate 2040
#define Tilt_Z_Calibrate 2475
#define Tilt_X_MaxVariation 800
#define Tilt_Y_MaxVariation 800
#define Tilt_Z_MaxVariation 400
#define  Tilt_MaxSpeed 50
#define Tilt_X_Invert -1



extern Enrf24 radio;  // P2.0=CE, P2.1=CSN, P2.2=IRQ
const uint8_t txaddr[] = { 0x17, 0x08, 0x07, 0xDE, 0x01 };

/* Global variables */
extern int Base_Speed, RightMotor, LeftMotor;
extern int update_counter;

/* Array of chars holding the packet to be sent */
extern char str_packet[];

/* Important volatile variable that signals the main code when the stop button is pressed */
extern volatile int STOP;

/* LCD object */
extern Screen_HX8353E myScreen;

/*
 * Pot controls current speed
 * Joystick x controls direction
 * Joystick y does nothing
 * Joystick button stops and re-starts robot.
 */
void dump_radio_status_to_serialport(uint8_t);
void LoadBuffer(int _LeftMotor, int _RightMotor);
void Standby_ISR();
//void Timer_Init();

/* Joystick1_Mode.cpp functions */
void Joystick1_Mode();
void Joystick1_Interface();
void Joystick1_Standby();
void _Update_Screen_BaseSpeed();

/* Tilt_Mode.cpp functions */
void Tilt_Mode();
void Tilt_Control();
void Update_Screen_Tilt();

/* Joystick2_Mode.cpp functions */
void Joystick2_Mode();
void Joystick2_Interface();
void Joystick2_Standby();
void Joystick1_Starting();

/* Tilt2_Mode.cpp functions */
void Tilt2_Mode();
void Tilt2_Control();
void Update_Screen_Tilt2();

int32_t Get_Pot_Speed(int _HalfScale);
float Get_JoyX_Percentage();
int32_t Get_JoyY_Speed(int _MaxSpeed);
int32_t Get_Joy_Radius_Speed(int _MaxSpeed);
int32_t Get_Tilt_Speed();
float Get_TiltX_Percentage();

#endif /* MAIN_H_ */
