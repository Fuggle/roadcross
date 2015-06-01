// Sweep
// by BARRAGAN <http://barraganstudio.com>
// This example code is in the public domain.
 
 
#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo
Servo myservo2;                // a maximum of eight servo objects can be created
 
int pos = 0;    // variable to store the servo position
 
void setup()
{
  Serial.begin(9600);
  myservo.attach(45);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(43);
}
 
 
void loop()
{
  //Serial.println(myservo.read());
  
  //myservo.write(5);
  /*Serial.println("waiting 15sec...");
  delay(5000);
  Serial.println("10sec remaining...");
  delay(5000);
  Serial.println("5sec remaining....");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("Finished waiting");*/
  //delay(8000);
  //myservo.write(0);
  Serial.println(myservo.read());
  Serial.println(myservo2.read());
  //myservo.write(180);
  //myservo.detach();
  delay(10000);
  //myservo.attach(45);
  if (pos != 160) {
    pos = 160;
    myservo.write(pos);
    myservo2.write(pos);
  } else {
    pos = 10;
    myservo.write(pos);
    myservo2.write(pos);
  }
  //Serial.println(myservo.read());
  //myservo.write(0);
  //myservo.write(0);
  //myservo.refresh()
  //Serial.println("Looped");
  
  
//  for(pos = 0; pos < 180; pos += 10)  // goes from 0 degrees to 180 degrees
//  {                                  // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
//  {
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}
