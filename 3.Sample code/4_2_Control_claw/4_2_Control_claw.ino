#include <Servo.h>  //Import the steering gear library files
Servo myservo4;     //Create a steering gear instance to control

#define right_Y A3   //Define the pin of the Y-axis of rocker 2
int pos4 = 90;  //Variable, used to control the steering gear angle of the mechanical claw
int y2 = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(right_Y, INPUT);
  myservo4.attach(8);
  myservo4.write(pos4);  //The mechanical claw closes
}

void loop() {  
  y2 = analogRead(right_Y); //Read the value of the rocker
//  Serial.print("y2 = ");
//  Serial.println(y2Val);
  
  if(y2<50) //If the right rocker is moved to the right
  {
    pos4=pos4+1;  //The current angle value of the steering gear 4, self adding 1
    if(pos4>90)  //At 90 degrees, the mechanical claw is fully closed
    {            //（Change the value according to the actual situation）
      pos4=90;  
    }
    Serial.println(pos4);
    myservo4.write(pos4);  //The steering gear 4 executes the action, and the claw gradually closes
    delay(8);  //Adjust the rotation speed of the steering gear
  }
  if(y2>1000)   //If the right rocker is moved to the left
  {
    pos4=pos4-1;  //The current angle value of the steering gear 4
    if(pos4 < 0)  //At 0 degrees, it is the maximum angle
    {
      pos4=0;
    }
    Serial.println(pos4);
    myservo4.write(pos4); //The steering gear 4 executes the action, and the claw gradually opens
    delay(8);  //Adjust the rotation speed of the steering gear
  }
}
