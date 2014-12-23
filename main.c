/*
 * TubularJackController.c
 *
 * Created: 9/13/2014 9:58:26 AM
 *  Author: baghi
 */ 

#define F_CPU 10000000UL  // 10 MHz
#define Open 1
#define Close 0
#define ActionTime (38*30)
#define FlasherDelay (38*1)
#define AutocloseDelay (38*60)
#define TestCycleTime ((unsigned long long)(34200)) //38*900
#define OffDelay (3000)


#include <avr/io.h>
#include <avr/delay.h>
#include "BoardAbstraction.h"




char RemoteAFlag=0,RemoteBFlag=0,State=0,FlasherFlag=0,FlasherState=0;
unsigned long long Time=0,MotorStartTime,MotorStopTime,LastAction=0;
char TestTrigger=1;




void StopMotor(void)
{
	Relay1Reset;Relay2Reset;
	FlasherFlag=0;	
}






void StartMotor(char dir)
{
	FlasherFlag=1;
	if(dir==Open)
	{
		Relay2Reset;Relay1Set;
	}
	
	if(dir==Close)
	{
		Relay1Reset;Relay2Set;
	}
	
}







void State0(void) // closed
{
	if((RemoteAFlag)||(!OpenKey)||(TestTrigger))
	{
		RemoteAFlag=0;
		LEDSet;
		MotorStartTime=Time;
		StartMotor(Open);
		State=1;
		_delay_ms(500);
	}
}






void State1(void) //openning
{
	if((RemoteAFlag)||(!StopKey)||(!CloseKey))
	{
		RemoteAFlag=0;
		MotorStopTime=Time;
		StopMotor();
		State=2;
		_delay_ms(500);
		TestTrigger=0;
	}
	
	if(Time>(MotorStartTime+ActionTime))
	{
		MotorStopTime=Time;
		StopMotor();
		State=2;
	}
	
	
}






void State2(void) //open
{
	if((RemoteAFlag)||(!CloseKey)||(TestTrigger))
	{
		if(TestTrigger) _delay_ms(OffDelay);
		RemoteAFlag=0;
		MotorStartTime=Time;
		StartMotor(Close);
		State=3;
		_delay_ms(500);
	}
	
	if((MotorStopTime!=0)&&(Key2))
	{
		if(Time>(MotorStopTime+AutocloseDelay))
		{
			TestTrigger=0;
			MotorStartTime=Time;
			StartMotor(Close);
			State=3;
			_delay_ms(500);
		}
	}	
}





void State3(void) //closing
{
	if((RemoteAFlag)||(!OpenKey)||(!StopKey))
	{
		TestTrigger=0;
		RemoteAFlag=0;
		MotorStopTime=Time;
		StopMotor();
		State=2;
		_delay_ms(500);
	}
	
	if(IRSensor)
	{
		TestTrigger=0;
		StopMotor();
		_delay_ms(500);
		MotorStartTime=Time;
		StartMotor(Open);
		_delay_ms(500);
		State=1;
	}
	
	if(Time>(MotorStartTime+ActionTime))
	{
		TestTrigger=0;
		LEDReset;
		MotorStopTime=0;
		StopMotor();
		State=0;
	}
	
}






void StateManager(void)
{
  if(State==0)
    State0();
  
  if(State==1)
	State1();
  
  if(State==2)
	State2();
  
  if(State==3)
	State3();	 	
}






void Flasher(void)
{
	if(FlasherFlag)
	{
			if(FlasherState==0)
				{Relay3Reset;}		
			else
				{Relay3Set;}
	}
	else
	{
		Relay3Reset;FlasherState=0;
	}		
	  
}






void TestSequencer(void)
{
	
	if(Time>=(LastAction+TestCycleTime))
	{
		LastAction=Time;
		TestTrigger=1;
	}
}









int main(void)
{
	
	static char state=0;
    
	Startup();
	LEDReset;
	
	/*
	while(1)
	if(Key2)
	  LEDSet;
	  else
	  LEDReset;
	*/
	
	
	
	while(1)
    {
		Flasher(); 
		StateManager();
		TestSequencer();	
    }
}