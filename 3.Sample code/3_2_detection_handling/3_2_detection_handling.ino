#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1=100, pos2=120, pos3=90, pos4=90;  //Angle values at the initial state of the mechanical arm

#define trigPin 4
#define echoPin 12
long duration, distance; //Variable

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Initialize the mechanical arm
  myservo1.attach(7);
  myservo2.attach(10);
  myservo3.attach(9);
  myservo4.attach(8);
  //Initialize the angle value of the mechanical arm
  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1000);
}

void loop() 
{
  int val = distance_value(); //Read the distance value detected by the ultrasonic module
  Serial.println(val);
  // If nearby goods is detected
  if(val < 11) {
    pos4 = myservo4.read();
    for(; pos4>0; pos4--) {
      myservo4.write(pos4); //Open the mechanical claw
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos2 = myservo2.read();
    for(; pos2>95; pos2--) {
      myservo2.write(pos2); //Swing the rod connecting the left steering gear forward
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3<140;pos3++) {
      myservo3.write(pos3); //Swing the rod connecting the right steering gear forward
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos4 = myservo4.read();
    for(; pos4<40; pos4++) {
      myservo4.write(pos4); //Grab
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3>90;pos3--) {
      myservo3.write(pos3); //Lift
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos2 = myservo2.read();
    for(; pos2<120; pos2++) {
      myservo2.write(pos2); //Swing the rod connecting the left steering gear forward

      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos1 = myservo1.read();
    for(;pos1>20;pos1--) {
      myservo1.write(pos1); //Turn to the right
      delay(1);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3<150;pos3++) {
      myservo3.write(pos3); //Swing the rod connecting the right steering gear forward
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos4 = myservo4.read();
    for(; pos4>0; pos4--) {
      myservo4.write(pos4); //Open the mechanical claw
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3>90;pos3--) {
      myservo3.write(pos3); //Lift
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos1 = myservo1.read();
    for(;pos1<100;pos1++) {
      myservo1.write(pos1); //Turn to the middle
      delay(1);  //Adjust the rotation speed of the steering gear
    }
    
  }

  //Detected goods that are relatively far away
  if((val > 11) && (val < 23)) {
    pos4 = myservo4.read();
    for(; pos4>0; pos4--) {
      myservo4.write(pos4); //Open the mechanical claw
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos2 = myservo2.read();
    for(; pos2<160; pos2++) {
      myservo2.write(pos2); //Swing the rod connecting the left steering gear forward
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3<180;pos3++) {
      myservo3.write(pos3); //Swing the rod connecting the right steering gear forward
      delay(10);  //Adjust the rotation speed of the steering gear
    }

    pos4 = myservo4.read();
    for(; pos4<42; pos4++) {
      myservo4.write(pos4); //Grab
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3>90;pos3--) {
      myservo3.write(pos3); //Lift
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos2 = myservo2.read();
    for(; pos2>120; pos2--) {
      myservo2.write(pos2); //Swing the rod connecting the left steering gear forward
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos1 = myservo1.read();
    for(;pos1<150;pos1++) {
      myservo1.write(pos1); //Turn to the left
      delay(1);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3<150;pos3++) {
      myservo3.write(pos3); //Swing the rod connecting the right steering gear forward
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos4 = myservo4.read();
    for(; pos4>0; pos4--) {
      myservo4.write(pos4); //Open the mechanical claw
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos3 = myservo3.read();
    for(;pos3>90;pos3--) {
      myservo3.write(pos3); //Lift
      delay(10);  //Adjust the rotation speed of the steering gear
    }
    pos1 = myservo1.read();
    for(;pos1>96;pos1--) {
      myservo1.write(pos1); //Turn to the middle
      delay(1);  //Adjust the rotation speed of the steering gear
    }
  }
  
}

//Sub function, ultrasonic ranging
int distance_value() {
  //The ultrasonic sensor emits a signal
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //The ultrasonic sensor receives the returned signal, and the time from emitting the signal to receiving the signal is assigned to duration
  duration = pulseIn(echoPin, HIGH);
  //Calculate the distance in centimeters, and the speed of sound is 0.034cm/ms
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
  return distance;  //Return the detected distance value
}
