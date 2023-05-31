#include <Servo.h>
Servo myservo;

void setup() {
  myservo.attach(8);  // 连接舵机引脚为8
}

void loop() {
    myservo.write(90); //舵机转到90度
}
