int playerBlue = 5;
int playerRed = 5;

int playerOneButton = 13; //pin no for player button
int playerTwoButton = 14; //pin no for player button
int ledPin = 15; //pin no for LED output

int playerOneVal = 0; //to be the value of the input button
int playerTwoVal = 0; //to be the value of the input button

void setup() {
  // put your setup code here, to run once:
  
  pinMode(playerOneButton, INPUT);
  pinMode(playerTwoButton, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  playerOneVal = digitalRead(playerOneButton);
  playerTwoVal = digitalRead(playerTwoButton);
  
  //check the input and count a press if pressed.
  //pass to keypress function.
  
  
  //drawObjects code from lua example will become output to LEDs.
    
}

boolean checkScore(player) {
  if (playerBlue + playerRed == 10 && player >= 0 && player < 10 ) {
    return true;
  } else { 
    return false;
  }
}
