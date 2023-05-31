/*
 * create by straysnail
 * 2023/2/21
 */
#define door_servoPin 7  //define servo pin
int pulsewidth = 0; //Used to calculate the pulse value of steering gear

void setup() {
  pinMode(door_servoPin,OUTPUT); //Set the pin to output state
}

void loop() {
  procedure(door_servoPin, 0);  //Turn the steering gear to 0 degrees
  delay(300);      //Give the steering gear time to run
  procedure(door_servoPin, 90);  //90 degrees
  delay(300);
  procedure(door_servoPin, 180);  //180 degrees
  delay(300);
  procedure(door_servoPin, 90);  //90 degrees
  delay(300);
}

//The function of controlling the steering gear Angle according to the steering gear principle
//The function takes two arguments, serPin is the steering gear pin and myangle is the steering gear Angle
void procedure(int serPin, int myangle)
{
  for(int i=0; i<10; i++)
  {
    pulsewidth = myangle * 11 + 500;  
    digitalWrite(serPin,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(serPin,LOW);
    delay((20 - pulsewidth / 1000));
  }
  
}
