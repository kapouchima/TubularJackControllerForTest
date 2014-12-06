/*
 * ISR.c
 *
 * Created: 9/13/2014 11:18:39 AM
 *  Author: baghi
 */ 


#define FlasherDelay (38*1)

#include <avr/interrupt.h>

char RemotePulseA,RemotePulseB,FlasherCounter=0;
extern char RemoteAFlag,RemoteBFlag,FlasherState;
extern unsigned long long Time;
unsigned long long RefreshTime;

ISR(INT0_vect)
{
	if(RemotePulseA==0)
	{
		RemotePulseA++;
		TCNT1H=0;
		TCNT1L=0;
		RefreshTime=Time+50;
	}
	
	if(RemotePulseA>0)
	{
		RemotePulseA++;
		if(RemotePulseA>4)
	{RemoteAFlag=1;RemotePulseA=0;RefreshTime=0;}
	}
}



ISR(INT1_vect)
{
	if(RemotePulseB==0)
	{
		RemotePulseB++;
		TCNT1H=0;
		TCNT1L=0;
		RefreshTime=Time+50;
	}
	
	if(RemotePulseB>0)
	{
		RemotePulseB++;
		if(RemotePulseB>4)
			{RemoteBFlag=1;RemotePulseB=0;RefreshTime=0;}
	}
}



ISR(TIMER0_OVF_vect)
{
	Time++;
	FlasherCounter++;
	if(FlasherCounter>=FlasherDelay)
	{
		FlasherCounter=0;
		FlasherState=!FlasherState;	  
	}
	if((Time>=RefreshTime)&&(RefreshTime))
	  {RemotePulseA=0;RemotePulseB=0;RefreshTime=0;}
}