char bleStr;

void setup() {
  Serial.begin(9600);

}

void loop() {
  while(Serial.available() > 0)  // Check whether the serial port area receives a value
  {
    bleStr = Serial.read();  // Read the value in the serial port area
    Serial.println(bleStr);
  }
}
