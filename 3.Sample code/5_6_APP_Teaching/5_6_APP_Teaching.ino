/*
 * create by straysnail
 * 2023/3/13
 */
#include <Servo.h>  //Add the steering gear library file
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=90, pos2=130, pos3=90, pos4=90;  // Arm initialization Angle
int s1,s2,s3,s4;  // Define four variables to hold the Angle value
int angle_storage1[20];  // Define four arrays for each of the four steering gear angles
int angle_storage2[20];  // (Array length is 20, that is, 0~20 steering gear Angle data can be saved)
int angle_storage3[20];  // If you need to save more data, just change 20 to a larger number
int angle_storage4[20];
int count=0; // for the for loop
int num=0; // Used to hold the last value of i
boolean cycle_flag = 0;

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
    if(bleVal1[0] == '$')  //Determines whether the start value is $
    {
      bleVal = bleVal1[1];
      Serial.println(bleVal);
      //If the second character received is 'c'
      if(bleVal1[1] == 'c') {  // Control the mechanical claw steering gear
        //Converts the beginning of the second character to the last character of the string to an integer and assigns it to pos4
        pos4 = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        pos4 = map(pos4, 0, 180, 90, 0);  // Mapping function to convert values from 0~180 to 90~0
        myservo4.write(pos4);
        Serial.println(pos4);
      }
      if(bleVal1[1] == 'l') {  // Control the left steering gear
        pos2 = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        pos2 = map(pos2, 0, 180, 160, 90);  // Mapping function to convert values from 0~180 to 160~90
        myservo2.write(pos2);
        Serial.println(pos2);
      }
      if(bleVal1[1] == 'r') {   // Control the right steering gear
        pos3 = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        pos3 = map(pos3, 0, 180, 20, 160);  // Mapping function that converts values from 0 to 180 to 0 to 90
        myservo3.write(pos3);
        Serial.println(pos3);
      }
      if(bleVal1[1] == 'b') {   // Control the right steering gear
        pos1 = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        pos1 = map(pos1, 0, 180, 180, 0); // Mapping function, the greater the drag value, the robot arm turns to the right
        myservo1.write(pos1);
        Serial.println(pos1);
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
    delay(5);  // Adjust the speed of the steering gear
  }
  if(bleVal == 'Q') {
    pos2=pos2-1;
    if(pos2<90)   // Limit the Angle of forward swing
    {
      pos2=90;
    }
    myservo2.write(pos2);  // Swing the left steering gear pendulum forward
    delay(10);  // Adjust the speed of the steering gear
  }
  if(bleVal == 'Z') {
    pos2=pos2+1;
    if(pos2>170)  // Limit the Angle of swing back
    {
      pos2=170;
    }
    myservo2.write(pos2);  // Swing the left steering gear pendulum back
    delay(10);  // Adjust the speed of the steering gear
  }
  if(bleVal == 'E') {
    pos3=pos3+1;
    if(pos3>180)  // Limit the Angle
    {
      pos3=180;
    }
    myservo3.write(pos3); // Right steering gear pendulum forward
    delay(10);  // Adjust the speed of the steering gear
  }
  if(bleVal == 'C') {
    pos3=pos3-1;  
    if(pos3<60) // Limit the Angle of descent
    {
      pos3=60;
    }
    myservo3.write(pos3);  // Right steering gear swing back
    delay(10);  // Adjust the speed of the steering gear
  }
  if(bleVal == 'F') {
    pos3=pos3+1;
    pos2=pos2+1;
    if(pos3>160)  // Limit the Angle
    {
      pos3=160;
    }
    if(pos2>160)  // Limit the Angle of swing back
    {
      pos2=160;
    }
    myservo3.write(pos3); // Right steering gear pendulum forward
    myservo2.write(pos2);  // Swing the left steering gear pendulum back
    delay(10);   // Adjust the speed of the steering gear
  }

  if(bleVal == 'B') {
    pos3=pos3-1;
    pos2=pos2-1;
    if(pos3<90)  // Limit the Angle of descent
    {
      pos3=90;
    }
    if(pos2<120)   // Limit the Angle of forward swing
    {
      pos2=120;
    }
    myservo3.write(pos3); // Right steering gear pendulum forward
    myservo2.write(pos2);  // Swing the left steering gear pendulum back
    delay(10);   // Adjust the speed of the steering gear
  }

  if(bleVal == 't') {
    myservo1.detach();
    myservo2.detach();
    myservo3.detach();
    myservo4.detach();
  }
  if(bleVal == 'y') {
    myservo1.attach(7);
    myservo2.attach(10);
    myservo3.attach(9);
    myservo4.attach(8);
  }
  if(bleVal == 'u') {
    Serial.println("memory");
    s1=myservo1.read();  // Read the current Angle value of each steering gear
    s2=myservo2.read();
    s3=myservo3.read();
    s4=myservo4.read();
//        Serial.print("angle = ");
//        Serial.println(pos1);
    angle_storage1[count]=s1; // Save the read steering gear values to the array one by one in sequence
    angle_storage2[count]=s2;
    angle_storage3[count]=s3;
    angle_storage4[count]=s4;
    count++;     //count is incremented by 1
    num=count;     //Assign the last value of i to num
    bleVal = 's';
  }
  if(bleVal == 'i') {
    cycle_flag = 1;
    while(cycle_flag == 1) {  //Loop, performing instructional actions over and over again     
      if(Serial.available() > 0)
      {
        String bleVal1 = Serial.readStringUntil('*');
        if(bleVal1[0] == '$')  // If the first character received is '$'
        {
          bleVal = bleVal1[1];
        }
        if(bleVal == 'o') {
          cycle_flag = 0; // Exit the loop
          count = 0;  //clear
          break;
        }
      }
      Serial.println("action");
      count = 0;
      pos1 = myservo1.read();   // Record the Angle values of the 4 steering gear in the current position
      pos2 = myservo2.read();
      pos3 = myservo3.read();
      pos4 = myservo4.read();

      for(int k=0;k<num;k++) // Loop j times, performing all saved actions
      {
        if(pos1<angle_storage1[k])   // If the current Angle of steering gear 1 is less than the value stored in array 1
        {
          while(pos1<angle_storage1[k])  // The while loop, in order to get the steering gear to the position of the array saved value
          {
            myservo1.write(pos1);  // Steering gear 1 Perform the action
            delay(5);   // Delay 5ms to control the rotation speed of the steering gear
            pos1++;  //pos1 adds 1 to itself
            //Serial.println(pos1);
          }
         }
         else   // If the current Angle of steering gear 1 is greater than the value stored in array 1
         {
          while(pos1>angle_storage1[k]) // The while loop, in order to get the steering gear to the position of the array saved value
           {
            myservo1.write(pos1);  // Steering gear 1 Perform the action
            delay(5);   // Delay 5ms to control the rotation speed of the steering gear
            pos1--;    //pos1 adds or subtracts 1 from itself
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
}
