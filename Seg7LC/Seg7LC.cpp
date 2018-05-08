#include "Arduino.h"
#include "Seg7LC.h"

// Define all pins for the seven segment display
Seg7LC::Seg7LC(int a, int b, int c, int d, int e, int f, int g, int dp, int s1, int s2, int s3, int s4)
{
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  segPins[0] = a;
  segPins[1] = b;
  segPins[2] = c;
  segPins[3] = d;
  segPins[4] = e;
  segPins[5] = f;
  segPins[6] = g;
  segPins[7] = dp;
  digPins[0] = s1;
  digPins[1] = s2;
  digPins[2] = s3;
  digPins[3] = s4;

}

// Display a 4 character string (message) for t milliseconds
void Seg7LC::Disp(const char message[], int t)
{
	int step = 2479;
	for(int i=0; i<(t/20); i++){
		Light(message[0],0);
		delayMicroseconds(step);
		Light(' ',0);
		delayMicroseconds(step);
		Light(message[1],1);
		delayMicroseconds(step);
		Light(' ',1);
		delayMicroseconds(step);
		Light(message[2],2);
		delayMicroseconds(step);
		Light(' ',2);
		delayMicroseconds(step);
		Light(message[3],3);
		delayMicroseconds(step);
		Light(' ',3);
		delayMicroseconds(step);
	}
}

// Light up one character in a certain position
void Seg7LC::Light(char seg, int dig)
{
	switch(seg){
		case '0': Seg(d0, dig); break;
		case '1': Seg(d1, dig); break;
		case '2': Seg(d2, dig); break;
		case '3': Seg(d3, dig); break;
		case '4': Seg(d4, dig); break;
		case '5': Seg(d5, dig); break;
		case '6': Seg(d6, dig); break;
		case '7': Seg(d7, dig); break;
		case '8': Seg(d8, dig); break;
		case '9': Seg(d9, dig); break;
		case 'a': Seg(da, dig); break;
		case 'b': Seg(db, dig); break;
		case 'c': Seg(dc, dig); break;
		case 'd': Seg(dd, dig); break;
		case 'e': Seg(de, dig); break;
		case 'f': Seg(df, dig); break;
		case ' ': Seg(space, dig); break;
		case '_': Seg(under, dig); break;
		case '-': Seg(dash, dig); break;
		case '.': Seg(dot, dig); break;
		default: Seg(space, dig);
	}

}

// Light a character based on position and number array
void Seg7LC::Seg(int num[], int dig)
{
	for(int i=0; i<8; i++){
		if(num[i] == 0){
			digitalWrite(segPins[i], LOW);
		}
		else{
			digitalWrite(segPins[i], HIGH);
		}
	}

   	if(dig == 0){
   		digitalWrite(digPins[1], HIGH);
   		digitalWrite(digPins[2], HIGH);
   		digitalWrite(digPins[3], HIGH);	
   	}
   	else if(dig == 1) {
   		digitalWrite(digPins[0], HIGH);
   		digitalWrite(digPins[2], HIGH);
   		digitalWrite(digPins[3], HIGH);	
    }
    else if(dig == 2) {
   		digitalWrite(digPins[0], HIGH);
   		digitalWrite(digPins[1], HIGH);
   		digitalWrite(digPins[3], HIGH);		
    }
    else if(dig == 3) {
   		digitalWrite(digPins[0], HIGH);
   		digitalWrite(digPins[1], HIGH);
   		digitalWrite(digPins[2], HIGH);		
    }

    digitalWrite(digPins[dig], LOW);
}

