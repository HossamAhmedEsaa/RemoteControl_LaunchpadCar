/*
 * Tilt_Mode.c
 *
 *  Created on: Sep 10, 2015
 *      Author: LuisRA
 */


#include "main.h"


int Tilt_Y_Speed2 = 0;
float Tilt_X_OffSet2=0;
int  Tilt_X_Value2=0;



void Tilt2_Mode(){
	//MAP_Interrupt_disableInterrupt(INT_PORT3|INT_PORT4|INT_PORT5);
detachInterrupt(Joystick_Button);
myScreen.clear();
	while(1){
		Tilt2_Control();
		radio.print(str_packet);
		radio.flush();  // Force transmit (don't wait for any more data)

		radio.deepsleep();

		delay(40);
	}
}


void Tilt2_Control(){





	Tilt_Y_Speed2 = Get_JoyY_Speed(30);


	if(Tilt_Y_Speed2 == 0){
		LeftMotor=255;
		RightMotor=255;
	}
	else{
		Tilt_X_OffSet2 =  Get_TiltX_Percentage();

		if(Tilt_X_OffSet2 > (1.0) )
			Tilt_X_OffSet2=1.0;
		else if(Tilt_X_OffSet2 < (-1.0) )
			Tilt_X_OffSet2=-1.0;
               Tilt_X_Value2 = Tilt_X_Value2*Tilt_X_Invert;
		if(Tilt_X_Value2 > 0){
			RightMotor = Tilt_Y_Speed2 * (1- Tilt_X_OffSet2) ;
			LeftMotor = Tilt_Y_Speed2;
		}
		else{
			RightMotor = Tilt_Y_Speed2 ;
			LeftMotor = Tilt_Y_Speed2  * (1-Tilt_X_OffSet2)	;
		}
	}
	LoadBuffer(LeftMotor,RightMotor);

	update_counter++;
	if(update_counter > 5){
		Update_Screen_Tilt();
		update_counter = 0;
	}
}

void Update_Screen_Tilt2(){
	  //myScreen.clear();

	   

	/* if(Tilt_X_Value2 > 50){
		 myScreen.gText(0, 0, "<--");
	 }
	 else if(Tilt_X_Value2 < -50)
		 myScreen.gText(0, 0, "    -->");
	 else if(Tilt_Y_Speed2 > 0){
		 myScreen.gText(0, 0, "   /\\");
	 }
	 else if(Tilt_Y_Speed2 < 0){
		 myScreen.gText(0, 0, "   \\/");
	 }*/

	 char a[] = "+999";
	 if(Tilt_Y_Speed2 <0){
		 Tilt_Y_Speed2 = Tilt_Y_Speed2 * (-1);
		 a[0] = '-';
	 }
	 else{
		 a[0] = '+';
	 }
	 for(int i=3; i >= 1; i--){
		a[i]= (Tilt_Y_Speed2%10)+48;
		Tilt_Y_Speed2 = Tilt_Y_Speed2 /10;
	 }
	 myScreen.gText(0, 30, a);

	  
	 //myScreen.gText(0, 5, "-120 to 120");
}
