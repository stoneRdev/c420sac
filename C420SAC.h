
 
#ifndef _C420SAC_H
#define _C420SAC_H

#include <Arduino.h>


const byte PIN_SAMPLE = A0;
#define PIN_0_MASK B01000000
#define PIN_1_MASK B00100000
#define PIN_2_MASK B00010000
#define PIN_3_MASK B00001000
#define PIN_OE_MASK B00000100
#define SHADOW_MASK B01111100
#define LIGHT_MASK B10000011


class C420SAC {
public:
	inline void init() {
		DDRD = DDRD | SHADOW_MASK;
		PORTD = PORTD & LIGHT_MASK;
	}
	inline void setEnabled(bool en = true) {
		if(en) {
			PORTD = PORTD | PIN_OE_MASK;
		} else {
			PORTD = PORTD & (~PIN_OE_MASK);
		}
	}
	inline void setChannel(uint8_t channel_mask) {
		channel_mask = min(channel_mask,15 );
		channel_mask = (channel_mask << 4) >> 1;
		PORTD = PORTD | channel_mask;
		delayMicroseconds(1);
	}
	inline int sampleChannel() {
		return analogRead(PIN_SAMPLE);
	}
	inline int sampleChannel(uint8_t mask) {
		setChannel(mask);
		return sampleChannel();
	}

};

//analogRead @ 274




#endif _C420SAC_H