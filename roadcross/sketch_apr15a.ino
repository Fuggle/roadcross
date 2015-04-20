

  int greenLed=8;
  int redLed=9;
  
  int redTime=10;
  int greenTime=5;
  
  int buttonPin=2;
  int buttonPin2=3;
  int buttonLed2=11;
  int buttonLed=10;
  int buttonState = 0;
  int buttonState2 = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(buttonPin,INPUT);
  pinMode(buttonLed,OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  // red light on
  while(redTime >= 0)
  {
    digitalWrite(greenLed,LOW);
    digitalWrite(redLed,HIGH);
    buttonState = digitalRead(buttonPin);
    buttonState2 = digitalRead(buttonPin2);
    //button1
    if (buttonState == HIGH)
    {
      digitalWrite(buttonLed,HIGH);
    }else
    {
      digitalWrite(buttonLed,LOW);
    }
    //button2
     if (buttonState2 == HIGH)
    {
      digitalWrite(buttonLed2,HIGH);
    }else
    {
      digitalWrite(buttonLed2,LOW);
    }
    if(redTime == 0)
    {
      greenTime = 5;
    }
  }
  //green light on
  while(greenTime >= 0)
  {
    digitalWrite(redLed,LOW);
    greenTime--;
    if(greenTime<3)
    {
      digitalWrite(greenLed, HIGH);
      delay(500);
      digitalWrite(greenLed, LOW);
      delay(500);
    }else
    {
      digitalWrite(greenLed, HIGH);
      delay(1000);
    }
    if(greenTime == 0)
    {
      redTime = 10;
    }
  }
  /*digitalWrite(greenLed, LOW);
  delay(redTime);
  digitalWrite(redled,LOW);
  digitalWrite(greenLed, HIGH);
  delay(greenTime);*/
}
