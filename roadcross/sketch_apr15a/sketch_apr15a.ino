#include <MsTimer2.h>

  int greenLed=7;
  int redLed=9;
  
  int greenStatus;
  int redStatus;
  int count = 0;
  
  int buttonPin=8;
  int buttonPin2=3;
  int buttonLed2=11;
  int buttonLed=10;
  int buttonState = 0;
  int buttonState2 = 0;
  
  boolean buttonPressed = LOW;
  
//signal light function 
void signalLight()
{
  count++;
   /*********************** the green light is on **************************/
  if(greenStatus)
  {
    if (count > 2)
    {
     digitalWrite(greenLed,LOW);
     digitalWrite(redLed,HIGH);
     redStatus = HIGH;
     greenStatus = LOW;
     count = 0;
     buttonPressed = LOW;
    }
  }
  /*********************** the red light is on **************************/
  else if (redStatus && buttonPressed)
  {
    if (count > 5)
    {
      digitalWrite(greenLed,HIGH);
      digitalWrite(redLed,LOW);
      redStatus = LOW;
      greenStatus = HIGH;
      count = 0;
    }
  }
}
void setup() {
   Serial.begin(9600);
  // put your setup code here, to run once:
  //light
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  //buttons
  pinMode(buttonPin,INPUT);
  pinMode(buttonPin2,INPUT);
  pinMode(buttonLed,OUTPUT); 
  /*********************** inistial the signal light **************************/
  digitalWrite(greenLed,HIGH);
  digitalWrite(redLed,LOW);
  greenStatus = HIGH;
  redStatus = LOW;
  //set the timer
  MsTimer2::set(1000, signalLight);// run every sec
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  
    buttonState = digitalRead(buttonPin);
    buttonState2 = digitalRead(buttonPin2);
    //button1
    if (buttonState == HIGH)
    {
      digitalWrite(buttonLed,HIGH);
      Serial.println("UP");
      if (!buttonPressed)
      {
        count = 0;
      }
      buttonPressed = HIGH;
    }else
    {
      Serial.println("DOWN");
      digitalWrite(buttonLed,LOW);
    }
    //button2
     if (buttonState2 == HIGH)
    {
      digitalWrite(buttonLed2,HIGH);
      if (!buttonPressed)
      {
        count = 0;
      }
      buttonPressed = HIGH;
    }else
    {
      digitalWrite(buttonLed2,LOW);
    }
}
