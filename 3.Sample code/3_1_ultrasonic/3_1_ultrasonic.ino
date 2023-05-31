#define trigPin 4  //Ultrasonic emission pin
#define echoPin 12 //Ultrasonic receiving pin
long duration, distance; //Variable

void setup() {
  Serial.begin(9600);        //Set the baud rate to 9600
  pinMode(trigPin, OUTPUT);  //Set to output
  pinMode(echoPin, INPUT);   //Set to input
}

void loop() {
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
  delay(500);
}
