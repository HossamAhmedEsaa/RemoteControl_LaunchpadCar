/*
 * Readings.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: LuisRA
 */

#include "main.h"


int32_t Get_Pot_Speed(int _HalfScale){
	int32_t SpeedAxis_Value = (int32_t)4095-(int32_t)analogRead(SpeedAxis_pin);
	int32_t _Base_Speed = 0;
	if(_HalfScale == 0){



		if(SpeedAxis_Value < 0+20){
			return _Base_Speed;
		}
		else{

			_Base_Speed = ((int32_t)SpeedAxis_Value-(int32_t)SpeedAxis_Offset)*(int32_t)MAXIMUM_SPEED/(int32_t)4095;
		}
	}
	else{
		 SpeedAxis_Value = (int32_t)SpeedAxis_Value -(int32_t)2047;

		if(SpeedAxis_Value < SpeedAxis_Offset+20 && SpeedAxis_Value > SpeedAxis_Offset-20){
			return _Base_Speed;
		}
		else{

			_Base_Speed = ((int32_t)SpeedAxis_Value-(int32_t)SpeedAxis_Offset)*(int32_t)MAXIMUM_SPEED/(int32_t)2048;
		}
	}
	return _Base_Speed;

}


float Get_JoyX_Percentage(){
	int _X_Value = analogRead(Xaxis_pin)  - 2047;
	float _OffSet = 1-( (_X_Value-X_Offset) / 2048.0);

	return _OffSet;
}

int32_t Get_JoyY_Speed(int _MaxSpeed){
	int _Y = analogRead(Yaxis_pin) -2047;

	int _Speed = 0;
	if(_Y < Y_Offset+20 && _Y > Y_Offset-20){
		return _Speed;
	}
	else{

		_Speed = ((int32_t)_Y-(int32_t)Y_Offset)*(int32_t)_MaxSpeed/(int32_t)2048;
	}
	return _Speed;
}

int32_t Get_Joy_Radius_Speed(int _MaxSpeed){

	int32_t Y_ = (int32_t)analogRead(Yaxis_pin) - 2047;

	int32_t X_ = (int32_t)analogRead(Xaxis_pin)  - 2047;

	int32_t _Radius = (int32_t)sqrtf((Y_*Y_) + (X_*X_));

	int32_t _Speed = 0;
	if(Y_ < Y_Offset+20 && Y_ > Y_Offset-20 && X_ < X_Offset+20 && X_ > X_Offset-20){
		return _Speed;
	}
	else{

		if(Y_ > 0)
			_Speed = (int32_t)(_Radius)*(int32_t)_MaxSpeed/(int32_t)2048;
		else
			_Speed = (int32_t)(-1)*(_Radius)*(int32_t)_MaxSpeed/(int32_t)2048;
	}

	return _Speed;
}

int32_t Get_Tilt_Speed(){

	int32_t _Tilt_Y_Speed = (int32_t)(analogRead(Tilt_Ypin) - (int32_t)Tilt_Y_Calibrate) *  (int32_t)Tilt_MaxSpeed /  (int32_t)Tilt_Y_MaxVariation;
	return _Tilt_Y_Speed;
}

float Get_TiltX_Percentage(){

	int _Tilt_X_Value = (int32_t)Tilt_X_Invert*(int32_t)(analogRead(Tilt_Xpin)-Tilt_X_Calibrate);
	float _Tilt_X_OffSet =  (float)_Tilt_X_Value/(float)Tilt_X_MaxVariation;

	return _Tilt_X_OffSet;
}
