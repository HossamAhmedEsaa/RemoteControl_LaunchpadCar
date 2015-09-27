/*
 * Joystick_Mode.c
 *
 *  Created on: Sep 10, 2015
 *      Author: LuisRA
 */

#include "main.h"


void _Update_Screen_BaseSpeed();

int Y_Value, X_Value, SpeedAxis_Value;
float OffSet;
volatile int STOP = 0;

void Joystick1_Mode(){
        detachInterrupt(Joystick_Button);
        attachInterrupt(Joystick_Button,Standby_ISR,FALLING);
	Joystick1_Starting();
//while(1);
        myScreen.clear();
	while(1){
	  Joystick1_Interface();
	  radio.print(str_packet);
	  radio.flush();  // Force transmit (don't wait for any more data)

	  radio.deepsleep();

	  //delay(40);
	}
}

void Joystick1_Interface(){

	if(STOP == 1){
		Joystick1_Standby();
	}

	/*
	 * Get ADC Values
	 */


	Base_Speed = Get_Pot_Speed(1);


	if(Base_Speed==0){
			RightMotor = 255;
			LeftMotor = 255;
	}
	else{


		OffSet = Get_JoyX_Percentage();
		if(OffSet > 0){
			RightMotor = Base_Speed * OffSet;
			LeftMotor = Base_Speed;
		}
		else{
			RightMotor = Base_Speed ;
			LeftMotor = Base_Speed  * (1-(OffSet-1))	;
		}
	}


	LoadBuffer(LeftMotor,RightMotor);

	update_counter++;
	if(update_counter > 5){
		_Update_Screen_BaseSpeed();
		update_counter = 0;
	}
}


void Joystick1_Standby(){
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
	myScreen.gText(0, 10, "pressed!");
	myScreen.gText(0, 20, "Wait!");
	delay(1000);
	STOP = 2;
	  
	myScreen.clear();
	myScreen.gText(0, 0, "Standing by");
	myScreen.gText(0, 10, "Press the");
	myScreen.gText(0, 20, " button again");
        myScreen.gText(0, 40, "Speed:");
	while(STOP == 2){
		    Base_Speed = Get_Pot_Speed(1);

			update_counter++;
			if(update_counter > 5){
				  
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
					 myScreen.gText(0, 50, a);
				 update_counter = 0;
			}
			delay(50);

	  }
          myScreen.clear();
	  delay(500);
	    
	  STOP = 0;
}

void _Update_Screen_BaseSpeed(){
	 // myScreen.clear();

	  
	// myScreen.gText(0, 0, "Base speed:");


	 char a[] = "+999";
	 if(Base_Speed <0){
		 Base_Speed = Base_Speed * (-1);
		 a[0] = '-';
		 //myScreen.gText(0, 1, "Backwards");
	 }
	 else{
		 a[0] = '+';
		// myScreen.gText(0, 1, "Forward");
	 }
	// myScreen.gText(0, 5, "-120 to 120");
	   
	 for(int i=3; i >= 1; i--){
		a[i]= (Base_Speed%10)+48;
		Base_Speed = Base_Speed /10;
	 }
	 myScreen.gText(0, 50, a);
}

void Joystick1_Starting(){

	 int _temp = Get_Pot_Speed(1);
         myScreen.gText(0, 0, "Set to 0");
	 while(_temp != 0){
		  
		
		 char a[] = "+999";
			 if(_temp <0){
				 _temp = _temp * (-1);
				 a[0] = '-';
			 }
			 else{
				 a[0] = '+';
			 }
			   
			 for(int i=3; i >= 1; i--){
				a[i]= (_temp%10)+48;
				_temp = _temp /10;
			 }
			 myScreen.gText(0, 20, a);
			 delay(100);
			 _temp = Get_Pot_Speed(1);
	 }
}
void Standby_ISR(){
     

	  if(STOP == 2){
		  STOP = 3;
	  }
	  else
		  STOP = 1;

}

