#include <Seg7LC.h>

Seg7LC panel(0,7,8,3,2,6,9,4,1,10,11,12);

int h = 9;
int m = 29;
char cta[4];

void setup() {
  // Button light always on 
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  // configure button
  pinMode(22, INPUT);
  digitalWrite(22, HIGH);
  attachInterrupt(digitalPinToInterrupt(22), push, FALLING);
}

void loop() {
  
  String sh = String(h);
  String sm = String(m);
  if(h < 10)
    sh = String(" " + sh);
  if(m < 10)
    sm = String("0" + sm);
  String ct = String(sh + sm);
  ct.toCharArray(cta, 5);
  panel.Disp(cta,1000);
  m++;
  if(m >= 60){
    m = 0;
    h++;
    if(h >= 24){
      h = 0;
    }
  }

}

void push() {
  h++;
}

