#include <Servo.h>
Servo redServo;
int redServoReadPin = 8;
int redServoWritePin = 10;

int prevReading = LOW;

void setup() {
  Serial.begin(9600);
  
  pinMode(redServoReadPin, INPUT); //reads input from other board
  redServo.attach(redServoWritePin);
}

void loop() {
  // put your main code here, to run repeatedly:
  //check reading from other board.
  int redServoReading = digitalRead(redServoReadPin);
  Serial.println(redServoReading);
  if (redServoReading != redServoReading) {
    if (redServoReading = LOW ) {
      redServo.write(180);
    } else {
      redServo.write(0);
    }
  }
  prevReading = redServoReading;
  
}
