#include <Servo.h>
Servo myservo1;  // Create 4 steering gear instance to control
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1=90, pos2=120, pos3=90, pos4=90;  //Angle value at the initial state of the mechanical arm

void setup()
{
  myservo1.attach(7);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
  myservo3.attach(9);
  myservo4.attach(8);
  //Initialize the mechanical arm
  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1000);
}

void loop() 
{
  //Rotate to the right
  for(pos1;pos1>0;pos1--)
  {
    myservo1.write(pos1);  //Step by step, turn the steering gear to the specified angle
    delay(5);              //Delay to control the rotation speed of the steering gear
  }
  delay(500);
  
  // Open the claw
  for(pos4;pos4>0;pos4--)
  {
    myservo4.write(pos4);
  }
    delay(500);

  //Swing the steering gear on the left back to lift the mechanical claw up
  for(pos2;pos2<140;pos2++)
  {
    myservo2.write(pos2);
    delay(5);
  }
  // Swing the steering gear on the right forward to extend and lower the mechanical claw
  for(pos3;pos3<150;pos3++)
  {
    myservo3.write(pos3);
    delay(5);
  }
  delay(500);
  
  // Grasp the goods
  for(pos4;pos4<50;pos4++)
  {
    myservo4.write(pos4);
  }
  delay(500);
  
  // Swing the right steering gear back, lift and retract the mechanical claw
  for(pos3;pos3>90;pos3--)
  {
    myservo3.write(pos3);
    delay(5);
  }
  delay(500);

  // Rotate to the left
  for(pos1;pos1<180;pos1++)
  {
    myservo1.write(pos1);
    delay(5);
  }
  delay(500);

  //Swing the steering gear on the left forward to bring the goods closer
  for(pos2;pos2>120;pos2--)
  {
    myservo2.write(pos2);
    delay(5);
  }

  // Swing the steering gear on the right forward to extend and lower the mechanical claw
  for(pos3;pos3<140;pos3++)
  {
    myservo3.write(pos3);
    delay(5);
  }
  delay(500);

    // Open the mechanical claw and lower the goods
  for(pos4;pos4>0;pos4--)
  {
    myservo4.write(pos4);
  }
    delay(500);

// Swing the right steering gear back, lift and retract the mechanical claw
  for(pos3;pos3>90;pos3--)
  {
    myservo3.write(pos3);
    delay(5);
  }
  delay(500);
  // Mechanical claw closes
  for(pos4;pos4<90;pos4++)
  {
    myservo4.write(pos4);
  }
  delay(500);

}
