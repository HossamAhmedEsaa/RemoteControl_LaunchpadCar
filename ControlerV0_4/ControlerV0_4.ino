/*
 *
 *
 * For the accelerometer http://letsmakerobots.com/node/35484
 */


#include "main.h"
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>
#include "Screen_HX8353E.h"




Screen_HX8353E myScreen;
Enrf24 radio(NRF24_CE_PIN, NRF24_CSN_PIN, NRF24_IRQ_PIN);

int Base_Speed, RightMotor, LeftMotor;
int update_counter = 0;

char str_packet[] = {
  15, 3, 1, 255, 1, 255, '\0' };

volatile int Mode_Set = 0, Mode_Ready = 0;

#define SW_RESET()      WDTCTL = WDT_MRST_0_064; while(1);  // watchdog reset
void Reset_ISR(){
  SW_RESET();
  
}

void setup() {
  
  
  pinMode(P1_1,INPUT_PULLUP);
  attachInterrupt(P1_1, Reset_ISR,FALLING);

  /* Configure acellerometer inputs */
  pinMode(Tilt_Xpin,INPUT);
  pinMode(Tilt_Ypin,INPUT);
  pinMode(Tilt_Zpin,INPUT);

  /*Configure buttons */
  pinMode(Button1_pin, INPUT_PULLUP);
  pinMode(Joystick_Button, INPUT_PULLUP);
  pinMode(Button2_pin, INPUT_PULLUP);
 
  attachInterrupt(Joystick_Button,Select_ISR,FALLING);
  


  /* Configure joystick inputs */
  pinMode(Xaxis_pin,INPUT);
  pinMode(Yaxis_pin,INPUT);
  pinMode(SpeedAxis_pin,INPUT);
  pinMode(18,INPUT);
 // analogReadResolution(12) ;

  /* Start Serial */
  //Serial.begin(9600);

  /* Initialize SPI module 2
   *
   * CLK = 4Mhz (limited by nokia 5510 screen - transceivar max = 30Mhz)
   *
   *  */
  //SPI.setModule(2);
  //SPI.setClockDivider(SPI_CLOCK_DIV128);
 /* SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);*/

  /* Initalize screen */
 // SPI.setModule(2);
  myScreen.begin();
  myScreen.setFontSize(1);
   myScreen.clear(darkGrayColour);

  /* Mode Selection */
  Mode_Select();



  radio.begin(1000000,005);  // Defaults 1Mbps, channel 0, max TX power
  // dump_radio_status_to_serialport(radio.radioState());

  radio.setTXaddress((void*)txaddr);

}


void loop() {

  if(Mode_Set == 0)
    Tilt_Mode();
  else if(Mode_Set == 1)
    Tilt2_Mode();
  else if(Mode_Set == 2)
    Joystick1_Mode();
  else if(Mode_Set == 3)
    Joystick2_Mode();

}



void  Mode_Select(){

  // MAP_Interrupt_enableInterrupt(INT_PORT3|INT_PORT4|INT_PORT5);


  Mode_Ready = 0;
  Mode_Set = 0;

  // myScreen.clear();


  //  myScreen.gText(0, 0, "Hi!");
  //delay(1000);
  myScreen.clear();

  myScreen.gText(0, 0, "Select mode:",orangeColour ); 
  myScreen.gText(StringMode_1_X, StringMode_1_Y, StringMode_1,orangeColour); 
  myScreen.gText(StringMode_2_X, StringMode_2_Y, StringMode_2,orangeColour);
  myScreen.gText(StringMode_3_X, StringMode_3_Y, StringMode_3,orangeColour);
  myScreen.gText(StringMode_4_X, StringMode_4_Y, StringMode_4,orangeColour);


  int toggle = 0;
  int LastMode = Mode_Set;
  while(Mode_Ready == 0){



    if(Mode_Set != LastMode){
      myScreen.gText(0, StringMode_1_Y, StringNoArrow,orangeColour,blackColour ); 
      myScreen.gText(0, StringMode_2_Y, StringNoArrow,orangeColour,blackColour ); 
      myScreen.gText(0, StringMode_3_Y, StringNoArrow,orangeColour,blackColour ); 
      myScreen.gText(0, StringMode_4_Y, StringNoArrow,orangeColour,blackColour ); 
      LastMode = Mode_Set;
    }

    if(Mode_Set == 0)
    {
      if(toggle == 0)
        myScreen.gText(0, StringMode_1_Y, StringArrow,orangeColour,cyanColour ); 
      else
        myScreen.gText(0, StringMode_1_Y, StringNoArrow,orangeColour,cyanColour ); 
      toggle ^= 1;

    }
    else if(Mode_Set == 1)
    {
      if(toggle == 0)
        myScreen.gText(0, StringMode_2_Y, StringArrow,orangeColour,cyanColour ); 
      else
        myScreen.gText(0, StringMode_2_Y, StringNoArrow,orangeColour,cyanColour ); 
      toggle ^= 1;
    }
    else if(Mode_Set == 2)
    {
      if(toggle == 0)
        myScreen.gText(0, StringMode_3_Y, StringArrow,orangeColour,cyanColour ); 
      else
        myScreen.gText(0, StringMode_3_Y, StringNoArrow,orangeColour,cyanColour ); 
      toggle ^= 1;

    }
    else if(Mode_Set == 3)
    {
      if(toggle == 0)
        myScreen.gText(0, StringMode_4_Y, StringArrow,orangeColour,cyanColour ); 
      else
        myScreen.gText(0, StringMode_4_Y, StringNoArrow,orangeColour,cyanColour ); 
      toggle ^= 1;
    }

    int temp = millis();
    while(millis()-temp < 300){
      if(digitalRead(Button2_pin) == 0){
        if(Mode_Set == 3)
          Mode_Set = 0;
        else
          Mode_Set++;
        delay(200);
      }
      else if(digitalRead(Button1_pin) == 0){

        if(Mode_Set == 0)
          Mode_Set = 3;
        else
          Mode_Set--;
        delay(200);
      }
    }
    //delay(500);
  }
  


  /* LCD showing starting sequence */

   myScreen.clear();
   myScreen.gText(0, 1, "Starting in:"); 
     myScreen.setFontSize(3);
   myScreen.gText(50, 50, "3");
   delay(1000);
   myScreen.gText(50, 50, "2");
   delay(1000);
   myScreen.gText(50, 50, "1");
   delay(1000);
   myScreen.gText(0, 1, "            "); 
   myScreen.gText(50, 50, " ");
   myScreen.setFontSize(1);
}


void LoadBuffer(int _LeftMotor, int _RightMotor){
  int direction = 1;
  if(_LeftMotor < 0){
    _LeftMotor = _LeftMotor*(-1);
    direction = 2;
  }
  str_packet[2] = direction;
  str_packet[3] = _LeftMotor;

  direction = 1;
  if(_RightMotor < 0){
    _RightMotor = _RightMotor*(-1);
    direction = 2;
  }
  str_packet[4] = direction;
  str_packet[5] = _RightMotor;

}

//Port3
void DownButton_ISR(){
  if(Mode_Set == 3)
    Mode_Set = 0;
  else
    Mode_Set++;


}
//Port4
void Select_ISR(){


  Mode_Ready=1;

}
//Port5
void UpButton_ISR(){

  if(Mode_Set == 0)
    Mode_Set = 3;
  else
    Mode_Set--;

}















