/*
 * Joystick_Mode.c
 *
 *  Created on: Sep 10, 2015
 *      Author: LuisRA
 */

#include "main.h"
void _Update_Screen_MaxSpeed();

int Y_Value2, X_Value2, SpeedAxis_Value2;
float OffSet2;
int Max_Speed2;
//volatile int STOP = 0;

void Joystick2_Mode(){
	STOP=0;
        detachInterrupt(Joystick_Button);
        attachInterrupt(Joystick_Button,Standby_ISR,FALLING);
	/*MAP_Interrupt_disableInterrupt(INT_PORT3|INT_PORT4|INT_PORT5);
        MAP_GPIO_registerInterrupt(GPIO_PORT_P4,Standby_ISR);
	MAP_Interrupt_enableInterrupt(INT_PORT4);*/
        myScreen.clear();
        myScreen.gText(0, 0, "Max Speed:");
	while(1){
	  Joystick2_Interface();
	  radio.print(str_packet);
	  radio.flush();  // Force transmit (don't wait for any more data)

	  radio.deepsleep();

	  delay(40);
	}
}

void Joystick2_Interface(){

	/*if(STOP == 1){
		Joystick2_Standby();
	}*/

	/*
	 * Get ADC Values
	 */


	Max_Speed2 = Get_Pot_Speed(0);
	Base_Speed = Get_Joy_Radius_Speed(Max_Speed2);


	if(Base_Speed==0){
			RightMotor = 255;
			LeftMotor = 255;
	}
	else{


		OffSet2 = Get_JoyX_Percentage();
		if(OffSet2 > 0){
			RightMotor = Base_Speed * OffSet2;
			LeftMotor = Base_Speed;
		}
		else{
			RightMotor = Base_Speed ;
			LeftMotor = Base_Speed  * (1-(OffSet2-1))	;
		}
	}


	LoadBuffer(LeftMotor,RightMotor);

	update_counter++;
	if(update_counter > 5){
		_Update_Screen_MaxSpeed();
		update_counter = 0;
	}
}


void Joystick2_Standby(){
	RightMotor = 255;
	LeftMotor = 255;
	LoadBuffer(LeftMotor,RightMotor);
	for(int i=0; i <30; i++){
		radio.print(str_packet);
		radio.flush();  // Force transmit (don't wait for any more data)
	}
	radio.deepsleep();
	myScreen.clear();
	 
	myScreen.gText(0, 0, "Stop button");
	myScreen.gText(0, 1, "pressed!");
	myScreen.gText(0, 3, "Wait!");
	delay(1000);
	STOP = 2;
	  
	myScreen.clear();
	myScreen.gText(0, 0, "Standing by");
	myScreen.gText(0, 2, "Press the");
	myScreen.gText(0, 3, " button again");
	while(STOP == 2){
		    Base_Speed = Get_Pot_Speed(1);

			update_counter++;
			if(update_counter > 5){
				  myScreen.clear();
				  myScreen.gText(0, 0, "Standing by");
				  myScreen.gText(0, 2, "Press the");
				  myScreen.gText(0, 3, " button again");
				  myScreen.gText(0, 4, "Max Speed:");
					 char a[] = "+999";
					 if(Base_Speed <0){
						 Base_Speed = Base_Speed * (-1);
						 a[0] = '-';
					 }
					 else{
						 a[0] = '+';
					 }

					 for(int i=3; i >= 1; i--){
						a[i]= (Base_Speed%10)+48;
						Base_Speed = Base_Speed /10;
					 }
					 myScreen.gText(0, 5, a);
				 update_counter = 0;
			}
			delay(50);

	  }
	  delay(500);
	    
	  STOP = 0;
}

void _Update_Screen_MaxSpeed(){

	Base_Speed = Get_Pot_Speed(0);
	//myScreen.clear();

	  
	 

	 char a[] = "999";
	 //myScreen.gText(0, 5, "0 to 120");
	   
	 for(int i=2; i >= 0; i--){
		a[i]= (Base_Speed%10)+48;
		Base_Speed = Base_Speed /10;
	 }
	 myScreen.gText(0, 30, a);
}

/* In Joystick 1 */
//void PortFIntHandler(){

/*
 *
 *  Pot controls maximum top speed
 *  Joystick x controls direction
 *  Joystick y controls current speed
 */
//
//int Y_Value2, X_Value2, RightMotor, LeftMotor, Base_Speed, SpeedAxis_Value2;
//float OffSet2;
//const int X_OffSet2 = 54;
//const int Y_OffSet2 = 24;
//const int SpeedAxis_OffSet2 = 44;
//const int MAXIMUM_SPEED = 120;
//void Joystick_Interface(){
//
//
//
//	/*
//	 * Get ADC Values
//	 */
//	X_Value2 = analogRead(Xaxis_pin);
//	Y_Value2 = analogRead(Yaxis_pin);
//	SpeedAxis_Value2 = analogRead(SpeedAxis_pin);
//
//	X_Value2 = X_Value2 - 2047;
//	Y_Value2 = Y_Value2 - 2047; // convert to a scale of -2047 to 2048
//	//SpeedAxis_Value2 = SpeedAxis_Value2 -2047;
//
//	if(Y_Value2 < Y_OffSet2+20 && Y_Value2 > Y_OffSet2-20 && X_Value2 < X_OffSet2+20 && X_Value2 > X_OffSet2-20){
//		//if(X_Value2 < X_OffSet2+20 && X_Value2 > X_OffSet2-20){
//			RightMotor = 255;
//			LeftMotor = 255;
//		//}
//		/*else{
//			Base_Speed =  X_Value2 * MaxSpeed / 2048;
//			RightMotor = -Base_Speed;
//			LeftMotor = Base_Speed;
//		}*/
//	}
//	else{
//
//		if(SpeedAxis_Value2-SpeedAxis_OffSet2 > 0)
//			MaxSpeed = (SpeedAxis_Value2-SpeedAxis_OffSet2)*MAXIMUM_SPEED/4095;
//		else
//			MaxSpeed=0;
//
//		if(Y_Value2-Y_OffSet2 < 0)
//			Base_Speed = (-1)*( sqrtf(powf(Y_Value2,2) + powf(X_Value2,2)) ) *MaxSpeed/2048; // Convert to the motor speed scale
//		else
//			Base_Speed = ( sqrtf(powf(Y_Value2,2) + powf(X_Value2,2)) ) *MaxSpeed/2048; // Convert to the motor speed scale
//
//
//		OffSet2 = 1-( (X_Value2-X_OffSet2) / 2048.0);
//
//		if(X_Value2 > 0){
//			RightMotor = Base_Speed * OffSet2;
//			LeftMotor = Base_Speed;
//		}
//		else{
//			RightMotor = Base_Speed ;
//			LeftMotor = Base_Speed  * (1-(OffSet2-1))	;
//		}
//	}
//
//
//	LoadBuffer(LeftMotor,RightMotor);
//
//}
