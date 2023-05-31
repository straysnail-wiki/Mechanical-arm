#include <Servo.h>  //Add the steering gear library file
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=90, pos2=130, pos3=90, pos4=90;  // Arm initialization Angle
const int left_X = A0; //Define the pins for the left rocker module
const int left_Y = A1;
const int left_key = 11;

const int right_X = A2; //Define the pins for the right rocker module
const int right_Y = A3;  
const int right_key = 12;

int x1,y1,z1;  //Defines a variable that holds the remote sensing values that have been read
int x2,y2,z2;
boolean flag = 0;
boolean flag2 = 0;
int count = 0;
int i = 0;
int s1,s2,s3,s4;  //Define four variables to hold the Angle value


void setup() 
{
  //initialization
  myservo1.write(pos1);  
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  pinMode(right_key, INPUT);   //Set the left and right buttons to input status
  pinMode(left_key, INPUT);
  Serial.begin(9600); //  Example Set the baud rate to 9600
}

void loop()
{
  //Connect the steering gear pins
  myservo1.attach(7); 
  myservo2.attach(10);
  myservo3.attach(9);
  myservo4.attach(8);

  //Read the value of the rocker module
  x1 = analogRead(left_X);
  y1 = analogRead(left_Y);
  z1 = digitalRead(left_key);
  x2 = analogRead(right_X);
  y2 = analogRead(right_Y);
  z2 = digitalRead(right_key);
  //delay(5);  //Slow down

  if(z2 == 1) {  //Determine whether the right joystick key is pressed
    delay(10); //Elimination of error
    z2 = digitalRead(right_key);
    if(z2 == 1) {
      flag2 = 1;
      while(flag2 == 1) {
        i++;
        delay(5);
        z2 = digitalRead(right_key);  //Read the value on the right z-axis
        if(z2 == 0) {  //Key release
          flag2 = 0;
        }
        Serial.println(i);
      }
      if(i > 150) {  //The button on the right is long pressed
        Serial.println("action");
        flag = 0;  //Exit loop
        flag2 = 0;
        i = 0;
        myservo1.write(s1);
        myservo2.write(s2);
        myservo3.write(s3);
        myservo4.write(s4);
        delay(1000);
        pos1 = s1;
        pos2 = s2;
        pos3 = s3;
        pos4 = s4;
      } 
      else if((i>10) && (i<150)) {  //Short press
        Serial.println("memory");
        s1=myservo1.read();  //Read the current Angle value of each steering gear
        s2=myservo2.read();
        s3=myservo3.read();
        s4=myservo4.read();
        Serial.print("angle = ");
        Serial.println(pos1);
        flag = 0;  //Exit loop
        flag2 = 0;
        i = 0;
      }
      else {
        flag = 0;  //Exit loop
        flag2 = 0;
        i = 0;
      }
    }
  }

  //Mechanical claw function
  claw();
  //Base rotation
  base();
  //Right-hand steering gear
  right_ser();
  //Left-hand steering gear
  left_ser();
  //Add button control whether to release the steering gear function, 
  //avoid the steering gear for a long time and damage
  if(z1 == 1)  //If the left joystick key is pressed
  {
    flag = 1;
    flag2 = 1;
    while(flag == 1)
    {
      //Release the steering gear to avoid damage caused by long working time
      release_servo();   
      z2 = digitalRead(right_key);  //Read the value on the right z-axis
      if(z2 == 1) {  //The button on the right is pressed
        delay(10); //Elimination of error
        if(z2 == 1) {
          while(flag2 == 1) {
            i++;
            delay(5);
            z2 = digitalRead(right_key);  //Read the value on the right z-axis
            if(z2 == 0) {  //The right button is released
              flag2 = 0;
            }
            Serial.println(i);
          }
          if(i > 100) {  //The button on the right is long pressed
            flag = 0;  //Exit loop
            i = 0;
          } else {
            flag2 = 1; //Maintenance cycle
            flag = 1;  //Maintenance cycle
            i = 0;
          }
          
        }
      }
    }
  }
}

//Mechanical claw function
void claw()
{
  //爪子
  if(y2<50) //If you flip the remote sensing on the right to the right
  {
    pos4=pos4+1;  //The Angle value of the current steering gear 4 is increased by 1
    if(pos4>90)  //At 90 degrees, the mechanical claw is completely closed
    {            //（Change the value according to the actual situation）
      pos4=90;  
    }
    //Serial.println(pos4);
    myservo4.write(pos4);  //Steering gear 4 perform the action and gradually close the claws
    delay(8);  //Adjust the speed of the steering gear
  }
  if(y2>1000)   //If you flip the remote sensing on the right to the left
  {
    pos4=pos4-1;  //Current Angle value of steering gear 4
    if(pos4 < 0)  //0 degrees is the maximum Angle
    {
      pos4=0;
    }
    //Serial.println(pos4);
    myservo4.write(pos4); //Steering gear 4 Perform the action and gradually open the claws
    delay(8);  //Adjust the speed of the steering gear
  }
}

 //A function that controls the rotation of the base
void base()
{
  if(y1<50)  //If you flip the remote sensing on the left to the right
  {
    pos1=pos1-1;  //So pos1 minus 1
    if(pos1<1)   //Limit the Angle of the right turn
    {
      pos1=1;
    }
    myservo1.write(pos1);  //Steering gear 1 performs the action, and the mechanical arm rotates to the right
    delay(5);  //Adjust the speed of the steering gear
  }
  if(y1>1000)  //If you flip the left remote to the left
  {
    pos1=pos1+1;  //So pos1 adds 1 to itself
    if(pos1>180)  //Limit the Angle of left turn
    {
      pos1=180;
    }
    myservo1.write(pos1);  //Mechanical arm to the left
    delay(5);  //Adjust the speed of the steering gear
  }
}

//Right-hand steering gear
void right_ser()
{
  if(x2<50) //If the remote sensing on the right goes to the front
  {
    pos3=pos3+1;
    if(pos3>160)  //Limiting Angle
    {
      pos3=160;
    }
    myservo3.write(pos3); //Right steering gear swing rod forward
    delay(10);  //Adjust the speed of the steering gear
  }
  if(x2>1000)  //If the remote sensing on the right goes to the back
  {
    pos3=pos3-1;  
    if(pos3<60)  //Limit the Angle of descent
    {
      pos3=60;
    }
    myservo3.write(pos3);  //Right steering gear swing back
    delay(10);  //Adjust the speed of the steering gear
  }
}

//Left steering gear
void left_ser()
{
  if(x1<50)  //If the remote sensing on the left goes to the front
  {
    pos2=pos2-1;
    if(pos2<60)   //Limit the Angle of forward swing
    {
      pos2=60;
    }
    myservo2.write(pos2);  //Left steering gear swing forward
    delay(10);  //Adjust the speed of the steering gear
  }
  if(x1>1000)  //If the remote sensing on the left goes back
  {
    pos2=pos2+1;
    if(pos2>170)  //Limit the Angle of swing back
    {
      pos2=160;
    }
    myservo2.write(pos2);  //Left steering gear swing back
    delay(10);   //Adjust the speed of the steering gear
  }
}
//Release steering gear
void release_servo() {
  delay(500);
  myservo1.detach();  //Release steering gear
  myservo2.detach();
  myservo3.detach();
  myservo4.detach();
}
