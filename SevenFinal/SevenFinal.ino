#include <Seg7LC.h>

IntervalTimer TrebleTime;
IntervalTimer BassTime;


// Setup up pins and global variables
const int tPin = 14;
const int bPin = 15;
int tstate = LOW;
int bstate = LOW;
int tcount = 0;
int bcount = 0;
int tnote = 0;
int bnote = 0;
int phrase = 0;

// Define frequencies in Hz for each note used
const float d2 = 73.42;
const float e2 = 82.41;
const float f2 = 92.50;
const float g2 = 98;
const float a2 = 110;
const float b2 = 123.47;

const float f5 = 739.99;
const float d5 = 587.33;
const float b4 = 493.88;
const float a4 = 440;

// Define a silent tone as 200 Hz
const float na = 200;

const int st = 150;  //Sixtenth note time in ms at 100 bpm
int basscount[24];
int treblecount[24];

// Notes of the song and time played
float basspart[] = {g2,g2,g2,g2,g2,a2,b2,b2,b2,b2,b2,b2,a2,a2,a2,a2,a2,f2,e2,e2,e2,e2,d2,d2};
float basstime[] = { 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2};

float treblepart[] = {na,na,f5,d5,b4,f5,na,f5,d5,a4,f5,na,f5,d5,a4,f5,na,f5,d5,b4,f5,f5,f5,f5};
float trebletime[] = { 2, 4, 3, 3, 2, 4, 4, 3, 3, 2, 4, 4, 3, 3, 2, 4, 4, 3, 3, 2, 1, 1, 1, 1};



Seg7LC panel(0,7,8,3,2,6,9,4,1,10,11,12);

volatile int h = 9;
volatile int m = 30;  
int* alarm = new int(0);  // 0 off 1 on
volatile int ah = 10;
volatile int am = 1;
char charTime[4] = {};
volatile int cycles = 0;
volatile int pushed = 0;
volatile int buCount = 0;
int* playing = new int(0);
int* Cstate = new int(0);


void setup() {
  // Button light always on 
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  // configure button
  pinMode(22, INPUT);
  digitalWrite(22, HIGH);
  attachInterrupt(digitalPinToInterrupt(22), push, FALLING);


  for (int i=0; i<24; i++) {
    basscount[i] = basstime[i]*st*basspart[i]/500;
    treblecount[i] = trebletime[i]*st*treblepart[i]/500;
  }

  pinMode(tPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  digitalWrite(tPin, LOW);
  digitalWrite(bPin, LOW);
  Serial.begin(9600);
}

void loop() {
  Serial.print(*alarm);
  Serial.println(*playing);
  switch(*Cstate) {
    case 0:
      panel.Disp(convertChar(h,m,charTime),100);
      break;
    case 1:
      panel.Disp(convertChar(ah,am,charTime),100);
      break;
    case 2:
      if(*alarm == 0)
        panel.Disp("0ff ",100);
      else
        panel.Disp("0n  ",100);
      break;
    case 3:
      panel.Disp(convertChar(ah,am,charTime),100);
      break;
    case 4:
      panel.Disp(convertChar(ah,101,charTime),100);  // 101 is a special case for nothing
      break;
    case 5:
      panel.Disp(convertChar(101,am,charTime),100);
      break;
    case 6:
      panel.Disp(convertChar(h,m,charTime),80);
      delay(20);
      break;
    case 7:
      panel.Disp(convertChar(h,101,charTime),100);
      break;
    case 8:
      panel.Disp(convertChar(101,m,charTime),100);
      break;
    case 9:
      panel.Disp(convertChar(h,m,charTime),100);
      if(*playing == 0) {
        TrebleTime.begin(twave,500000/treblepart[tnote]);
        BassTime.begin(bwave,500000/basspart[bnote]);
        *playing = 1;
      }
      break;
  }


  // Handle button pushes
  if(pushed == 1){
    if (digitalRead(22) == HIGH && buCount < 1) {
      pushed = 0;
      buCount = 0;
    }
    else {
      buCount++;
    }
  }
  if(buCount == 5 && digitalRead(22) == HIGH){
    Serial.println("SP");
    switchState(0,*Cstate);
    buCount = 0;
    pushed = 0;
  }
  if(buCount > 5) {
    Serial.println("LP");
    switchState(1,*Cstate);
    buCount = 0;
    pushed = 0;
  }
  
  
  
  // Update for time keeping
  cycles++;
  if(cycles == 600){
    cycles = 0;
    m++;
    //Check for alarm
    if(m == am && h == ah && *alarm == 1) {
      *Cstate = 9;
    }
  }
  if(m >= 60){
    m = m-60;
    h++;
      //Check for alarm
    if(m == am && h == ah && *alarm == 1) {
      *Cstate = 9;
    }
  }
  if(h >= 24){
    h = h-24;
      //Check for alarm
    if(m == am && h == ah && *alarm == 1) {
      *Cstate = 9;
  }
  }

  // Do not allow alarm to overflow
  if(am >= 60){
    am = am-60;
    ah++;
  }
  if(ah >= 24){
    ah = ah-24;
  }

  
  

}

void push() {
  pushed = 1;
}

char* convertChar(int h, int m, char* charTime) {
  String sh = String(h);
  String sm = String(m);
  if(h < 10)
    sh = String(" " + sh);
  if(m < 10)
    sm = String("0" + sm);
  if(h == 101)
    sh = String("  ");
  if(m == 101)
    sm = String("  ");  
  String ct = String(sh + sm);
  ct.toCharArray(charTime, 5);
  return charTime;
}

void switchState(int typePress, int currentState) {
  if (typePress == 0) // Short Press
  {
    switch(currentState) {
      case 0:
        *Cstate = 1;
        break;
      case 1:
        *Cstate = 2;
        break;
      case 2:
        *Cstate = 0;
        break;
      case 3:
        *Cstate = 4;
        break;
      case 4:
        ah++;
        break;
      case 5:
        am++;
        break;
      case 6:
        *Cstate = 7;
        break;
      case 7:
        h++;
        break;
      case 8:
        m++;
        break;
      case 9:
        *Cstate = 0;
        TrebleTime.end();
        BassTime.end();
        digitalWrite(tPin, LOW);
        digitalWrite(bPin, LOW);
        tstate = LOW;
        bstate = LOW;
        tcount = 0;
        bcount = 0;
        tnote = 0;
        bnote = 0;
        phrase = 0;
        *playing = 0;
        am = m+5;
        ah = h;
        break;
    }
  }
  
  else if (typePress == 1) // Long Press
  {
    switch(currentState) {
      case 0:
        *Cstate = 6;
        break;
      case 1:
        *Cstate = 4;
        break;
      case 2:
        if(*alarm == 0)
          *alarm = 1;
        else
          *alarm = 0;
        break;
      case 3:
        *Cstate = 6;
        break;
      case 4:
        *Cstate = 5;
        break;
      case 5:
        *Cstate = 0;
        break;
      case 6:
        *Cstate = 0;
        break;
      case 7:
        *Cstate = 8;
        break;
      case 8:
        *Cstate = 0;
        break;
      case 9:
        *Cstate = 0;
        TrebleTime.end();
        BassTime.end();
        digitalWrite(tPin, LOW);
        digitalWrite(bPin, LOW);
        tstate = LOW;
        bstate = LOW;
        tcount = 0;
        bcount = 0;
        tnote = 0;
        bnote = 0;
        phrase = 0;
        *playing = 0;
        *alarm = 0;
        break;
    }
  }
  
  else 
  {
    //Error
  }
  return;
}


// Interrupt Service routine for Treble Part
void twave() {
  if(tcount <= treblecount[tnote]) {
    if(treblepart[tnote] == 200 || tcount >= .8*treblecount[tnote] || phrase < 2) {  // silence
      if(tstate == LOW)
        tstate = HIGH;
      else
        tstate = LOW;
        tcount = tcount + 1;
      digitalWrite(tPin, LOW);
    }
    else {  // tone
      if(tstate == LOW)
        tstate = HIGH;
      else
        tstate = LOW;
        tcount = tcount + 1;
      digitalWrite(tPin, tstate);  
    }
  }
  else { // Move to the next note
    tcount = -7;  // Reset the frequency count for each new note
    if(tnote < 23) {
      tnote = tnote + 1;  // next note
    }
    else {
      tnote = 0;  // repeat
    }
    TrebleTime.begin(twave,500000/treblepart[tnote]);  
  }
}

// Interrupt Service routine for Bass Part
void bwave() {
  if(bcount <= basscount[bnote]) {
    if(basspart[bnote] == 200 || bcount >= .8*basscount[bnote]) {  // silence
      if(bstate == LOW)
        bstate = HIGH;
      else
        bstate = LOW;
        bcount = bcount + 1;
      digitalWrite(bPin, LOW);
    }
    else {  // tone
      if(bstate == LOW)
        bstate = HIGH;
      else
        bstate = LOW;
        bcount = bcount + 1;
      digitalWrite(bPin, bstate);  
    }
  }
  else { // Move to the next note
    bcount = 0;  // Reset the frequency count for each new note
    if(bnote < 23) {
      bnote = bnote + 1;  // next note
    }
    else {
      bnote = 0;  // repeat
      tnote = 0;  // sync with treble
      tcount = 0;
      phrase = phrase + 1;
    }
    BassTime.begin(bwave,500000/basspart[bnote]);  
  }
}




