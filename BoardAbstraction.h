/*
 * BoardAbstraction.h
 *
 * Created: 9/13/2014 10:50:54 AM
 *  Author: baghi
 */ 


#ifndef BOARDABSTRACTION_H_
#define BOARDABSTRACTION_H_


#define OpenKey (PINC&(1<<PINC1))
#define StopKey (PINC&(1<<PINC2))
#define CloseKey (PINC&(1<<PINC3))
#define IRSensor (PIND&(1<<PIND6))

#define Relay3Set PORTD|=(1<<7)
#define Relay3Reset PORTD&=~(1<<7)

#define Relay2Set PORTB|=(1<<0)
#define Relay2Reset PORTB&=~(1<<0)

#define Relay1Set PORTB|=(1<<1)
#define Relay1Reset PORTB&=~(1<<1)

//#define Key1 PIND&(1<<PIND4)
#define LEDReset PORTD|=(1<<PIND4)
#define LEDSet PORTD&=~(1<<PIND4)

#define Key2 (PIND&(1<<PIND5))



#endif /* BOARDABSTRACTION_H_ */