/*
 * Tilt_Mode.c
 *
 *  Created on: Sep 10, 2015
 *      Author: LuisRA
 */


#include "main.h"

int Tilt_Y_Speed = 0;
float Tilt_X_OffSet=0;
int  Tilt_X_Value=0;



void Tilt_Mode(){
	//MAP_Interrupt_disableInterrupt(INT_PORT3|INT_PORT4|INT_PORT5);
detachInterrupt(Joystick_Button);
myScreen.clear();
	while(1){
		Tilt_Control();
		radio.print(str_packet);
		radio.flush();  // Force transmit (don't wait for any more data)

		radio.deepsleep();

		delay(40);
	}
}


void Tilt_Control(){

	if(digitalRead(Button1_pin) !=0){
		RightMotor = 255;
		LeftMotor = 255;
		LoadBuffer(LeftMotor,RightMotor);
		for(int i=0; i <10; i++){
			radio.print(str_packet);
			radio.flush();  // Force transmit (don't wait for any more data)
		}
		radio.deepsleep();
		myScreen.clear();

		 
		myScreen.gText(0, 0, "Button");
		myScreen.gText(0, 10, "not pressed!");
		myScreen.gText(0, 20, "Waiting...");
		while(digitalRead(Button1_pin) !=0);
		myScreen.clear();

		return;
	}



	Tilt_Y_Speed = Get_Tilt_Speed();

	Tilt_X_OffSet =  Get_TiltX_Percentage();

	if(Tilt_X_OffSet > (1.0) )
		Tilt_X_OffSet=1.0;
	else if(Tilt_X_OffSet < (-1.0) )
		Tilt_X_OffSet=-1.0;


        Tilt_X_Value = Tilt_X_Value*Tilt_X_Invert;
	if(Tilt_X_Value > 0){
		RightMotor = Tilt_Y_Speed * (1 - Tilt_X_OffSet) ;
		LeftMotor = Tilt_Y_Speed;
	}
	else{
		RightMotor = Tilt_Y_Speed ;
		LeftMotor = Tilt_Y_Speed  * (1-Tilt_X_OffSet)	;
	}

	LoadBuffer(LeftMotor,RightMotor);

	update_counter++;
	if(update_counter > 5){
		Update_Screen_Tilt();
		update_counter = 0;
	}
}

void Update_Screen_Tilt(){
	//  myScreen.clear();

	   

	/* if(Tilt_X_Value > 50){
		 myScreen.gText(0, 0, "<--");
	 }
	 else if(Tilt_X_Value < -50)
		 myScreen.gText(0, 0, "    -->");
	 else if(Tilt_Y_Speed > 0){
		 myScreen.gText(0, 0, "   /\\");
	 }
	 else if(Tilt_Y_Speed < 0){
		 myScreen.gText(0, 0, "   \\/");
	 }*/

	 char a[] = "+999";
	 if(Tilt_Y_Speed <0){
		 Tilt_Y_Speed = Tilt_Y_Speed * (-1);
		 a[0] = '-';
	 }
	 else{
		 a[0] = '+';
	 }
	 for(int i=3; i >= 1; i--){
		a[i]= (Tilt_Y_Speed%10)+48;
		Tilt_Y_Speed = Tilt_Y_Speed /10;
	 }
	 //itoa(Base_Speed,a,10);
	 //sprintf(a,"Speed: %d",Base_Speed);
	 myScreen.gText(0, 30, a);

	  
// myScreen.gText(0, 5, "-120 to 120");
}
