/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/


#include <Servo.h>

Servo brasServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo rotationServo;
Servo forwardServo;
Servo liftServo;



int pos; // position du bras

int rotationPosition;

int forwardPosition;

int liftPosition;

// defining the angles of defferents state of every mptor
 
const int openAngle = 90; 
const int closeAngle = 70;

const int extremeLeft = 170;
const int extremeRight = 90;


const int extremeForward = 150;
const int extremeBackward = 60;

const int extremeUp = 150;
const int extremeDown = 70;

boolean isOpen; 
int previous;
int testInt; 

 void rotate(int angle){
  if( angle <= extremeLeft && angle >= extremeRight){
    int rotationStep;
    if(angle > rotationPosition) 
      rotationStep = 1;
    else 
      rotationStep = -1;

    while(rotationPosition != angle){
      rotationPosition = rotationPosition + rotationStep;

      rotationServo.write(rotationPosition);
      delay(15);
    }
  }
 
 }
 

void open_hand()
{

  if(isOpen) 
    return;
 
    for (pos = closeAngle; pos <= openAngle; pos += 1) {
      // in steps of 1 degree
      brasServo.write(pos); 
      //Serial.print("Openning ");
      //Serial.println(pos);
      delay(15);                      
   }

   isOpen = true; 
}

void close_hand()
{
  if(!isOpen) 
    return;
    
    for (pos = openAngle; pos >= closeAngle; pos -= 1) { 
      brasServo.write(pos);
      //Serial.print("Closing "); 
      //Serial.println(pos);
      delay(15);                     
   }

   isOpen = false; 
}

void up_down(int angle)
{
  if( angle <= extremeUp && angle >= extremeDown){
    int rotationStep;
    if(angle > liftPosition) 
      rotationStep = 1;
    else 
      rotationStep = -1;

    while(liftPosition != angle){
      liftPosition = liftPosition + rotationStep;
      liftServo.write(liftPosition);
      delay(15);
    }
  }
}


void forward_backward(int angle)
{
  if( angle <= extremeForward && angle >= extremeBackward){
    int rotationStep;
    if(angle > forwardPosition) 
      rotationStep = 1;
    else 
      rotationStep = -1;

    while(forwardPosition != angle){
      forwardPosition = forwardPosition + rotationStep;
      forwardServo.write(forwardPosition);
      delay(15);
    }
  }
}

void switchHandState()
{
  if(isOpen) 
  {
    close_hand();
 
  }else 
  {
    open_hand();

  }

  isOpen = !isOpen;
}
void setButton(){
  
}


int laststate = 0;

void movp1(){
  forward_backward(95);
  rotate(125);
  up_down(75);
  close_hand();
}

void movp2(){
  
  up_down(110);
  rotate(144);
  forward_backward(125);
  up_down(90);
  delay(50);
  open_hand();
}

void setup() {
  brasServo.attach(9);  // attaches the servo on pin 9 to the servo object
  rotationServo.attach(8);
  forwardServo.attach(7);
  liftServo.attach(6);

  pinMode(A0,INPUT); 
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  //pinMode(10,INPUT);
  //pinMode(11,INPUT);
  pinMode(12,INPUT);
  digitalWrite(12,HIGH);
  
  Serial.begin(9600);
  rotationPosition = 90;
  liftPosition=120;
  liftServo.write(liftPosition);
  delay(500);
  testInt = rotationPosition;
  forwardPosition = 60;
  
  forwardServo.write(forwardPosition);
  delay(500);
  
  rotationServo.write(rotationPosition);
  delay(500);
  //rotate(130);
  isOpen = false; 
  previous=HIGH;
  open_hand();
  laststate = digitalRead(10);

    Serial.println(isOpen);
    Serial.println(previous);
    Serial.println(digitalRead(12));
    Serial.println();
    movp1();
    movp2();
}



int xAxis = 0; 
int yAxis = 0; 
int zAxis = 0; 
//int zPos = 120;
//int astate = 0;
//bool switchstate = false;

/*
void movp(){
  forward_backward(zAxis);
  rotate(xAxis);
  up_down(yAxis);

}*/

void loop() 
{
  
  if(digitalRead(12)==LOW && previous==HIGH)
  {
    //Serial.println(analogRead(A1));
    //Serial.println(analogRead(A0));
    //Serial.println(analogRead(A2));

    previous=digitalRead(12);
   // open_hand();
   switchHandState();
   isOpen=!isOpen;
  }
  else if (digitalRead(12)==HIGH && previous==LOW){
    //close_hand();
    previous=digitalRead(12);
  }
    
  yAxis = map(analogRead(A1), 0, 1023, extremeUp, extremeDown);
  xAxis = map(analogRead(A0), 0, 1023, extremeRight, extremeLeft);
  zAxis = map(analogRead(A2), 0, 1023, extremeForward, extremeBackward);
 // forward_backward(zAxis);
 // rotate(xAxis);
 // up_down(yAxis);

  Serial.print("xAxis = "); 
  Serial.print(xAxis); 
  Serial.print( ", yAxis = "); 
  Serial.print(yAxis);
  Serial.print(", zAxis = ");
  Serial.println(zAxis);
  


  

  /*
 
  astate= digitalRead(10);
 
  if(astate != laststate){
    if(digitalRead(11) != astate){
      if(zPos < extremeForward)
        zPos += 5;
    }else{
      if(zPos > extremeBackward)
        zPos -= 5;
    }
    
    laststate = astate; 
  }+
   */
   
  //forwardServo.write(zAxis);
  //forward_backward(zPos);
  

}









