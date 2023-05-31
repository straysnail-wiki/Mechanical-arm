#include <Servo.h>

Servo myservo;  // Instantiate a steering gear control object

int pos = 0;    // Variable, used for steering gear Angle

void setup() {
  myservo.attach(7);  // Initialize the steering gear
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // The steering gear is going from 0 to 180
    // A revolution of one degree in one step
    myservo.write(pos); // Control the degree of steering gear transfer to pos variable
    delay(15);  // The delay function controls the speed at which the steering gear turns
  }
  for (pos = 180; pos >= 0; pos -= 1) { //Control the steering gear from 180 degrees to 0 degrees
    myservo.write(pos);
    delay(15);
  }
}
