

// the setup function runs once when you press reset or power the board
#include <Servo.h>

#define DELTA_T 100
#define MAX_STEP 1

Servo servo8;
Servo servo9;
int incomingByte = 0,goalAngle=0;
int currentAngle;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  servo8.attach(8);
  servo9.attach(9);
}


// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {

    // read the incoming byte:
    incomingByte = Serial.parseInt();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);

    if (incomingByte >= 7000 && incomingByte < 8000) {
      Serial.print("I receivedBis7: ");
      Serial.println(incomingByte);
      digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
    }


    if (incomingByte >= 8000 && incomingByte < 9000) {
      Serial.print("I receivedBis8: ");
      Serial.println(map(incomingByte%100,0,100,0,180));
      goalAngle=map(incomingByte%100,0,100,0,180);
      currentAngle=servo8.read(); 
      
      while(currentAngle!=goalAngle){
        //step
        if ( incomingByte < 8100){ 
           servo8.write(goalAngle);
           currentAngle=goalAngle;
        }
        //linear
        if (incomingByte >= 8100 && incomingByte < 8200){                        
          if(currentAngle > goalAngle - MAX_STEP && currentAngle < goalAngle + MAX_STEP ){
            servo8.write(goalAngle);
            currentAngle=goalAngle;
          }
          else if(currentAngle > goalAngle + MAX_STEP){
            servo8.write(currentAngle-MAX_STEP);
            currentAngle=currentAngle-MAX_STEP;
          }
          else{
            servo8.write(currentAngle+MAX_STEP);
            currentAngle=currentAngle+MAX_STEP;
          }
          delay(DELTA_T);
        
        }
        //square TO BE DONE
        /*if (incomingByte >= 8200 && incomingByte < 8300){                        
          if(currentAngle > goalAngle - MAX_STEP && currentAngle < goalAngle + MAX_STEP ){
            servo8.write(goalAngle);
            currentAngle=goalAngle;
          }
          else if(currentAngle > goalAngle + MAX_STEP){
            servo8.write(currentAngle-MAX_STEP);
            currentAngle=currentAngle-MAX_STEP;
          }
          else{
            servo8.write(currentAngle+MAX_STEP);
            currentAngle=currentAngle+MAX_STEP;
          }
          delay(DELTA_T);
        
        }*/
      }
    }
    
    if (incomingByte >= 9000 && incomingByte <= 9999) {
      Serial.print("I receivedBis9: ");
      Serial.println(map(incomingByte%100,0,100,0,180));
      servo9.writeMicroseconds(map(incomingByte%100,0,100,0,180));
    }



  }
  // wait for a second
}
