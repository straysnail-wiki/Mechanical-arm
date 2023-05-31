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
int i = 0;
int s1,s2,s3,s4;  //Define four variables to hold the Angle value
int angle_storage1[10];  //Define four arrays to hold each of the four steering gear angles
int angle_storage2[10];  //（The array length is 10, that is, 0~10 steering gear Angle data can be saved）
int angle_storage3[10];  //If you need to save more data, just change 10 to a larger number
int angle_storage4[10];
int count=0;
int num=0;
boolean cycle_flag = 0;

void setup() 
{
  //initialization
  myservo1.write(pos1);  
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  pinMode(right_key, INPUT);
  pinMode(left_key, INPUT);
  Serial.begin(9600);
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
        cycle_flag = 1;
        while(cycle_flag == 1) {  //Loop, performing instructional actions over and over again
          z1 = digitalRead(left_key);  //Read the value of the left z-axis
          if(z1 == 1) {
            delay(10);
            z1 = digitalRead(left_key);  //Read the value of the left z-axis
            if(z1 == 1) {
              cycle_flag = 0;  //Exit loop
              // Assign coount to 0 in preparation for storing Angle values in the array next time
              count = 0;
            }
          }
          Serial.println("action");
          flag = 0;  //Exit loop
          flag2 = 0;
          i = 0;
          count = 0;
          pos1 = myservo1.read();   // Read the Angle values of the four steering gear in the current position
          pos2 = myservo2.read();
          pos3 = myservo3.read();
          pos4 = myservo4.read();
  
          for(int k=0;k<num;k++)    //Loop j times, performing all saved actions
          {
            //If the current Angle of steering gear 1 is less than the value stored in array 1
            if(pos1<angle_storage1[k]) 
            {
              while(pos1<angle_storage1[k]) //The while loop, in order to get the steering gear to the position of the array saved value
              {
                myservo1.write(pos1);  //Steering gear 1 Perform the action
                delay(5);    //Control speed
                pos1++;
                //Serial.println(pos1);
              }
             }
             else    // If the current Angle of steering gear 1 is greater than the value stored in array 1
             {
              while(pos1>angle_storage1[k])
               {
                myservo1.write(pos1);
                delay(5);
                pos1--;
                //Serial.println(pos1);
               }
             }
  
            if(pos2<angle_storage2[k])
            {
              while(pos2<angle_storage2[k])
              {
                myservo2.write(pos2);
                delay(5);
                pos2++;
                //Serial.println(pos1);
              }
            }
            else
            {
             while(pos2>angle_storage2[k])
              {
                myservo2.write(pos2);
                delay(5);
                pos2--;
                //Serial.println(pos1);
              }
            }
  
            if(pos3<angle_storage3[k])
            {
              while(pos3<angle_storage3[k])
              {
                myservo3.write(pos3);
                delay(5);
                pos3++;
                //Serial.println(pos1);
              }
            }
            else
            {
             while(pos3>angle_storage3[k])
              {
                myservo3.write(pos3);
                delay(5);
                pos3--;
                //Serial.println(pos1);
              }
            }
    
            if(pos4<angle_storage4[k])
            {
              while(pos4<angle_storage4[k])
              {
                myservo4.write(pos4);
                delay(5);
                pos4++;
                //Serial.println(pos1);
              }
            }
            else
            {
             while(pos4>angle_storage4[k])
              {
                myservo4.write(pos4);
                delay(5);
                pos4--;
                //Serial.println(pos1);
              }
            }
          }
        }
        
      } 
      else if((i>10) && (i<150)) {        //Short press
        Serial.println("memory");
        s1=myservo1.read();  //Read the current Angle value of each steering gear
        s2=myservo2.read();
        s3=myservo3.read();
        s4=myservo4.read();
//        Serial.print("angle = ");
//        Serial.println(pos1);
        //Save the read steering gear values to the array one by one in sequence
        angle_storage1[count]=s1;
        angle_storage2[count]=s2;
        angle_storage3[count]=s3;
        angle_storage4[count]=s4;
        count++;
        num=count;   //Assign the last value of i to num
        flag = 0;
        flag2 = 0;
        i = 0;
      }
      else {
        flag = 0;
        flag2 = 0;
        i = 0;
      }
    }
  }

  //Mechanical claw
  claw();
  //base
  base();
  //Right-hand steering gear
  right_ser();
  //Left-hand steering gear
  left_ser();
  //Add button control whether to release the steering gear function, avoid the steering gear for a long time and damage
  if(z1 == 1)  //If the left joystick key is pressed
  {
    flag = 1;
    flag2 = 1;
    while(flag == 1)
    {
      release_servo();   //Release the steering gear to avoid damage caused by long working time
      z2 = digitalRead(right_key);  //Read the value on the right z-axis
      if(z2 == 1) {  //The button on the right is pressed
        delay(10); //Eliminate keystrokes and reduce errors
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
