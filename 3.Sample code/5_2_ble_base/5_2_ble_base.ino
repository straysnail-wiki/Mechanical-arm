#include <Servo.h>  //Add the steering gear library file
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=90, pos2=130, pos3=90, pos4=90;   // Arm initialization Angle
char bleVal;

void setup() {
  Serial.begin(9600);
  //Connect the steering gear pins
  myservo1.attach(7); 
  myservo2.attach(10);
  myservo3.attach(9);
  myservo4.attach(8);
  //initialization
  myservo1.write(pos1);  
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1000);

}

void loop() {
  if(Serial.available() > 0)
  {
    //The serial port cache is read until it hits *, which is when all characters except * are assigned to bleVal1
    String bleVal1 = Serial.readStringUntil('*'); 
    if(bleVal1[0] == '$') //Determines whether the start value is $
    {
      bleVal = bleVal1[1];  //Assign a valid command value to bleVal
      Serial.println(bleVal);
    }
  }
  //When the virtual stick is dragged to the left, the command value sent is L
  if(bleVal == 'L') {
    pos1=pos1+1;  //So pos1 adds 1 to itself
    if(pos1>180)  //Limit the Angle of left turn
    {
      pos1=180;
    }
    myservo1.write(pos1);  //Mechanical arm to the left
    delay(5);  //Adjust the speed of the steering gear
  }
  //When the virtual stick is dragged to the right, the command value sent is R
  if(bleVal == 'R') {
    pos1=pos1-1;  //So pos1 minus 1
    if(pos1<1)   //Limit the Angle of the right turn
    {
      pos1=1;
    }
    myservo1.write(pos1);  //Steering gear 1 performs the action, and the mechanical arm rotates to the right
    delay(5);  //Adjust the speed of the steering gear
  }
}
