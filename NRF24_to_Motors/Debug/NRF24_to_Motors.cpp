#include "Energia.h"

void SetMotors();
void setup();
void loop();
void dump_radio_status_to_serialport(uint8_t status);

#line 1 "NRF24_to_Motors.ino"
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>


#include "Speed_Control.h"


Enrf24 radio(PF_1, PE_3, PE_2);
const uint8_t rxaddr[] = { 0x17, 0x08, 0x07, 0xDE, 0x01 };

const char *str_on = "ON";
const char *str_off = "OFF";
char inbuf[33];

void dump_radio_status_to_serialport(uint8_t);

int LeftMotor_Speed =0;
int RightMotor_Speed =0;
int left_direction;
int right_direction;

void SetMotors(){

	
		

	if(inbuf[0] != 15)

    if(inbuf[1] == 3)return;
	{
    	 left_direction = inbuf[2];
    	 right_direction = inbuf[4];

    	if(left_direction == 2)
    		left_direction = -1;
		else if(left_direction != 1)
    		return;

    	if(right_direction == 2)
    		right_direction = -1;
		else if(right_direction != 1)
    		return;


        if(inbuf[3] == 255)
        	LeftMotor_Speed=0;
        else
        	LeftMotor_Speed = left_direction * inbuf[3];

        if(inbuf[5] == 255)
        	RightMotor_Speed=0;
        else
        	RightMotor_Speed = right_direction * inbuf[5];

		SpeedControl_Set(LeftMotor_Speed,RightMotor_Speed);
	}

}

int temp=0;
void setup() {
  Serial.begin(9600);
  SPI.setModule(0);
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  radio.begin(1000000,005);  
  dump_radio_status_to_serialport(radio.radioState());

  radio.setRXaddress((void*)rxaddr);

  pinMode(PF_2, OUTPUT);
  digitalWrite(PF_2, LOW);

  radio.enableRX();  

  SpeedControl_Init();


}


void loop() {

  
  

  while (!radio.available(true) && (millis()-temp) < 90)
    ;
 
  if( (millis()-temp) > 90){
	  SpeedControl_Set(0,0);
	  temp = millis();
  }
  else if (radio.read(inbuf)) {
    
    

    SetMotors();
   



    temp = millis();
  }
  radio.deepsleep();

  delay(20);

  radio.enableRX();


}

void dump_radio_status_to_serialport(uint8_t status)
{
  Serial.print("Enrf24 radio transceiver status: ");
  switch (status) {
    case ENRF24_STATE_NOTPRESENT:
      Serial.println("NO TRANSCEIVER PRESENT");
      break;

    case ENRF24_STATE_DEEPSLEEP:
      Serial.println("DEEP SLEEP <1uA power consumption");
      break;

    case ENRF24_STATE_IDLE:
      Serial.println("IDLE module powered up w/ oscillators running");
      break;

    case ENRF24_STATE_PTX:
      Serial.println("Actively Transmitting");
      break;

    case ENRF24_STATE_PRX:
      Serial.println("Receive Mode");
      break;

    default:
      Serial.println("UNKNOWN STATUS CODE");
  }
}


