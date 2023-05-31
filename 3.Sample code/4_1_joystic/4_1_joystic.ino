/*
 * create by straysnail
 * 2023/3/11
 */

//Define the pin of the rocker module
#define x1 A0
#define y1 A1
#define b1 11
#define x2 A2
#define y2 A3
#define b2 12

void setup() {
  Serial.begin(9600);
  //Set pin mode to input
  pinMode(x1, INPUT);
  pinMode(y1, INPUT);
  pinMode(b1, INPUT);
  pinMode(x2, INPUT);
  pinMode(y2, INPUT);
  pinMode(b2, INPUT);

}

void loop() {
  // Read the value of the left rocker module
  int x1Val = analogRead(x1);  //Read the analog value of the X axis
  int y1Val = analogRead(y1);  //Read the analog value of the Y axis
  int b1Val = digitalRead(b1); //Read the digital value of the Z axis
  // Read the value of the right rocker module
  int x2Val = analogRead(x2);
  int y2Val = analogRead(y2);
  int b2Val = digitalRead(b2);
  Serial.print("x1 = ");
  Serial.print(x1Val);
  Serial.print("   ");
  Serial.print("y1 = ");
  Serial.print(y1Val);
  Serial.print("   ");
  Serial.print("b1 = ");
  Serial.print(b1Val);
  Serial.print("       ");
  Serial.print("x2 = ");
  Serial.print(x2Val);
  Serial.print("   ");
  Serial.print("y2 = ");
  Serial.print(y2Val);
  Serial.print("   ");
  Serial.print("b2 = ");
  Serial.println(b2Val);
  delay(100);
}
