int playerBlue = 5;
int playerRed = 5;

int playerOneButton = 8; //pin no for player button
int playerTwoButton = 9; //pin no for player button
int ledPin1 = 13; //pin no for LED output
int ledPin2 = 12;
int ledPin3 = 11;

int playerOneVal = 0; //to be the value of the input button
int playerTwoVal = 0; //to be the value of the input button

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
 
  pinMode(playerOneButton, INPUT);
  pinMode(playerTwoButton, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  //turn them all off to begin with
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  playerOneVal = digitalRead(playerOneButton);
  playerTwoVal = digitalRead(playerTwoButton);
  
  //check the input and count a press if pressed.
  //pass to keypress function.
  //Serial.println(playerOneVal);
  //Serial.println(playerTwoVal);
 
  //drawObjects code from lua example will become output to LEDs.
  if (playerOneVal != 0) {
    digitalWrite(ledPin1, HIGH);
    Serial.println("Red");
  } else {
    digitalWrite(ledPin1, LOW);
  }
  if (playerTwoVal != 0) {
    digitalWrite(ledPin2, HIGH);
    Serial.println("Blue");
  } else {
    digitalWrite(ledPin2, LOW);
  }
 
  delay(200);
  
}

//checks that the player score does not exceed boundaries, and the sum of both is 10
//returns true or false if the score is able to be incremented
/*boolean checkScore(player) {
  if (playerBlue + playerRed == 10 && player >= 0 && player < 10 ) {
    return true;
  } else { 
    return false;
  }
}*/
