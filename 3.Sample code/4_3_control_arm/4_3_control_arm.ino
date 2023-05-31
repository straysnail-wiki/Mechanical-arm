#include <Servo.h>  //Add the steering gear library files
Servo myservo1;  // Create a steering gear instance to control
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=90, pos2=130, pos3=90, pos4=90;  //Define variables for four steering gear angles and assign initial values (i.e. the attitude angle values at startup)
const int left_X = A0; //Define the pin of the left X-axis as A0 
const int left_Y = A1; //Define the pin of the left Y-axis as A1 
const int left_key = 11; //Define the pin of the right button as 7 (i.e. the value of Z-axis)

const int right_X = A2; //Define the pin of the right X-axis as A2
const int right_Y = A3;  //Define the pin of the right Y-axis as A3
const int right_key = 12; //Define the pin of the right button as 8 (i.e. the value of Z-axis)

int x1,y1,z1;  //Define variables to store the read rocker values
int x2,y2,z2;
boolean flag = 0;
boolean flag2 = 0;
int count = 0;
int i = 0;


void setup() 
{
  myservo1.attach(7);  //Set the control pin of the steering gear 1 as A1
  myservo2.attach(10);  //Set the control pin of the steering gear 2 as A0
  myservo3.attach(9);   //Set the control pin of the steering gear 3 as D8
  myservo4.attach(8);   //Set the control pin of the steering gear 4 as D9
  //Status at startup
  myservo1.write(pos1);  
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  pinMode(right_key, INPUT);   //Set the left and right buttons to input
  pinMode(left_key, INPUT);
  Serial.begin(9600); //  Set the baud rate as 9600
}

void loop()
{
  x1 = analogRead(left_X); //Read the value of the left X-axis
  y1 = analogRead(left_Y);  //Read the value of the left Y-axis
  z1 = digitalRead(left_key);  //Read the value of the left Z-axis
  
  x2 = analogRead(right_X);  //Read the value of the right X-axis
  y2 = analogRead(right_Y);  //Read the value of the right Y-axis
  z2 = digitalRead(right_key);  //Read the value of the right Z-axis
  //delay(5);  //Reduce the speed of all the steering gears

  //The claw
  claw();
  //Rotates
  base();
  //The right steering gear
  right_ser();
  //The left steering gear
  left_ser();
  //Add the function of button control to release the steering gear to avoid damage caused by prolonged operation
  if(z1 == 1)  //If the left rocker button is pressed
  {
    flag = 1;
    flag2 = 1;
    while(flag == 1)
    {
      release_servo();   //Release the steering gear to avoid damage caused by prolonged operation
      z2 = digitalRead(right_key);  //Read the value of the right Z-axis
      if(z2 == 1) {  //If the right rocker button is pressed
        delay(10); //Eliminate button jitter and reduce errors
        if(z2 == 1) {
          while(flag2 == 1) {
            i++;
            delay(5);
            z2 = digitalRead(right_key);  //Read the value of the right Z-axis
            if(z2 == 0) {  //The right button is released
              flag2 = 0;
            }
            Serial.println(i);
          }
          if(i > 100) {  //If the right button is long pressed
            flag = 0;  //Exit the circle
            i = 0;
            myservo1.attach(7);   //Connect the steering gears
            myservo2.attach(10);
            myservo3.attach(9);
            myservo4.attach(8);
          } else {
            flag2 = 1; //Keep the circle
            flag = 1;  //Keep the circle
            i = 0;
          }
          
        }
      }
    }
  }
}

//The claw
void claw()
{
  //The claw
  if(y2<50) //If the right rocker is moved to the right
  {
    pos4=pos4+1;  //The current angle value of the steering gear 4, self adding 1
    if(pos4>90)  //At 90 degrees, the mechanical claw is fully closed
    {            //（Change the value based on the actual situation）
      pos4=90;  
    }
    Serial.println(pos4);
    myservo4.write(pos4);  //The steering gear 4 executes the action, and the claw gradually closes
    delay(8);  //Adjust the speed of the rotation of the steering gear
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
    delay(8);  //Adjust the speed of the rotation of the steering gear
  }
}

 //Rotate
void base()
{
  if(y1<50)  //If the left rocker is moved to the right
  {
    pos1=pos1-1;  //Pos1 subtracts 1 from itself
    if(pos1<1)   //Limit the angle of right turn
    {
      pos1=1;
    }
    myservo1.write(pos1);  //The steering gear 1 executes the action, and the mechanical arm rotates to the right
    delay(5);  //Adjust the speed of the rotation of the steering gear
  }
  if(y1>1000)  //If the left rocker is moved to the left
  {
    pos1=pos1+1;  //Pos1 adds 1 from itself
    if(pos1>180)  //Limit the angle of left turn
    {
      pos1=180;
    }
    myservo1.write(pos1);  //The mechanical turns left
    delay(5);  //Adjust the speed of the rotation of the steering gear
  }
}

//Right steering gear
void right_ser()
{
  if(x2<50) //If the right rocker is moved to the front
  {
    pos3=pos3+1;
    if(pos3>160)  //Limit the angle
    {
      pos3=160;
    }
    myservo3.write(pos3); //Swing the right steering gear rod forward
    delay(10);  //Adjust the speed of the rotation of the steering gear
  }
  if(x2>1000)  //If the right rocker is moved to the rear
  {
    pos3=pos3-1;  
    if(pos3<60)  //Limit the angle of descent
    {
      pos3=60;
    }
    myservo3.write(pos3);  //Swing the right steering gear rod backward
    delay(10);  //Adjust the speed of the rotation of the steering gear
  }
}

//Left steering gear
void left_ser()
{
  if(x1<50)  //If the left rocker is moved to the front
  {
    pos2=pos2-1;
    if(pos2<90)   //Limit the angle of forward swing
    {
      pos2=90;
    }
    myservo2.write(pos2);  //Swing the left steering gear rod forward
    delay(10);  //Adjust the speed of the rotation of the steering gear
  }
  if(x1>1000)  //If the left rocker is moved to the rear
  {
    pos2=pos2+1;
    if(pos2>170)  //Limit the angle of backward swing
    {
      pos2=170;
    }
    myservo2.write(pos2);  //Swing the left steering gear rod backward
    delay(10);   //Adjust the speed of the rotation of the steering gear
  }
}
//Release the steering gears
void release_servo() {
  delay(500);
  myservo1.detach();  //Release the steering gears
  myservo2.detach();
  myservo3.detach();
  myservo4.detach();
}
