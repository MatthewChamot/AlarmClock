/*
 *  Library for a 7 segment display on a Teensy LC
 *
 *  The display function only lights each digit for 1/8 the time
 *     to ensure 5 mA current limit of GPIO pins is not exceeded.
 *
 *  Created by Matthew Chamot
 * 
 */

 #ifndef Seg7LC_h
 #define Sed7LC_h

 #include "Arduino.h"

class Seg7LC
 {
  public:
    Seg7LC(int a, int b, int c, int d, int e, int f, int g, int dp, int s1, int s2, int s3, int s4);
    void Disp(const char message[], int t);
  private:
    void Light(char seg, int dig);
    void Seg(int num[], int dig);
    int segPins[8];
    int digPins[4];
    int d0[8] = {1,1,1,1,1,1,0,0};
    int d1[8] = {0,1,1,0,0,0,0,0};
    int d2[8] = {1,1,0,1,1,0,1,0};
    int d3[8] = {1,1,1,1,0,0,1,0};
    int d4[8] = {0,1,1,0,0,1,1,0};
    int d5[8] = {1,0,1,1,0,1,1,0};
    int d6[8] = {1,0,1,1,1,1,1,0};
    int d7[8] = {1,1,1,0,0,0,0,0};
    int d8[8] = {1,1,1,1,1,1,1,0};
    int d9[8] = {1,1,1,1,0,1,1,0};
    int da[8] = {1,1,1,0,1,1,1,0};
    int db[8] = {0,0,1,1,1,1,1,0};
    int dc[8] = {1,0,0,1,1,1,0,0};
    int dd[8] = {0,1,1,1,1,0,1,0};
    int de[8] = {1,0,0,1,1,1,1,0};
    int df[8] = {1,0,0,0,1,1,1,0};
    int space[8] = {0,0,0,0,0,0,0,0};
    int under[8] = {0,0,1,0,0,0,0,0};
    int dash[8]  = {0,0,0,0,0,0,1,0};
    int dot[8]   = {0,0,0,0,0,0,0,1};
    
    
 };

 #endif

