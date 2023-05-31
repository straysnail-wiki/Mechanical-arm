#include <Servo.h>   //Add the steering gear library file
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=90, pos2=130, pos3=90, pos4=90; // Arm initialization Angle

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
    String bleVal1 = Serial.readStringUntil('*');
    if(bleVal1[0] == '$') //Determines whether the start value is $
    {
      bleVal = bleVal1[1];
      //Serial.println(bleVal);
      //If the second character received is 'c'
      if(bleVal1[1] == 'c') {
        //Converts the beginning of the second character to the last character of the string to an integer and assigns it to pos4
        pos4 = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        pos4 = map(pos4, 0, 180, 90, 0);  // Mapping function to convert values from 0~180 to 90~0
        myservo4.write(pos4);  // Control the steering gear execution of the mechanical claw
        //Serial.println(pos4);
      }
    }
  }
  if(bleVal == 'L') {
    pos1=pos1+1;  //pos1 adds 1 to itself
    if(pos1>180)  // Limit the left turn Angle
    {
      pos1=180;
    }
    myservo1.write(pos1);  // Mechanical arm to the left
    delay(5);  // Adjust the speed of the steering gear
  }
  if(bleVal == 'R') {
    pos1=pos1-1;  // Subtract 1 from pos1
    if(pos1<1)   // Limit the right turn Angle
    {
      pos1=1;
    }
    myservo1.write(pos1);  // Steering gear 1 perform the action, and the mechanical arm rotates to the right
    delay(5); // Adjust the speed of the steering gear
  }
}
