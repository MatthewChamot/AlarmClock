IntervalTimer TrebleTime;
IntervalTimer BassTime;

const int tPin = 14;
const int bPin = 22;
int tstate = LOW;
int bstate = LOW;
int tcount = 0;
int bcount = 0;
int tnote = 0;
int bnote = 0;
int phrase = 0;

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

const float na = 200;

const int st = 150;  //Sixtenth note time in ms at 100 bpm
int basscount[24];
int treblecount[24];

float basspart[] = {g2,g2,g2,g2,g2,a2,b2,b2,b2,b2,b2,b2,a2,a2,a2,a2,a2,f2,e2,e2,e2,e2,d2,d2};
float basstime[] = { 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2};

float treblepart[] = {na,na,f5,d5,b4,f5,na,f5,d5,a4,f5,na,f5,d5,a4,f5,na,f5,d5,b4,f5,f5,f5,f5};
float trebletime[] = { 2, 2, 3, 3, 2, 4, 4, 3, 3, 2, 4, 4, 3, 3, 2, 4, 4, 3, 3, 2, 1, 1, 1, 1};

void setup() {
  pinMode(tPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  Serial.begin(9600);
  noInterrupts();
  TrebleTime.begin(twave,500000/treblepart[tnote]);
  BassTime.begin(bwave,500000/basspart[bnote]);
      int sumt = 0;
    int sumb = 0;
  for(int i=0; i<24; i++) {
    basscount[i] = basstime[i]*st*basspart[i]/500;
    treblecount[i] = trebletime[i]*st*treblepart[i]/500;
    Serial.print(basscount[i]);
    Serial.print(" ");
    Serial.println(treblecount[i]);
    sumt = sumt + basscount[i];
    sumb = sumb + treblecount[i];
    
  }
  Serial.print(sumt);
  Serial.print(" ");
  Serial.println(sumb);
  interrupts();
  
}

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


void loop() {
  
}


