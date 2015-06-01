//libraries
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <MsTimer2.h>
#include <Servo.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
//altered matrix library is from: https://github.com/protonmaster/RGB-matrix-Panel/commit/b40df07cea6d701f7270e198286b3741622c21fe
#include <pitches.h>


int maxPoints = 20; //change this if you want to change how many points 

//scores
int singleScore = maxPoints / 2; 
int redScore = singleScore;
int blueScore = singleScore;

//Signal light variables
int count = 0;
boolean walkLight;
boolean drawRed = true;
boolean drawBlue = true;
long redPunch;
long bluePunch;
#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

//custom library snippet
#define NUMDISPLAYS 2
#define DOUBLEBUFFER false
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, DOUBLEBUFFER, NUMDISPLAYS);

//the mans...
//stored backwards cos our displays are used in a y,x orientation, rather than the usual x,y
//each pair is a {y, x} coord
//len of this is 64
int stopMan[][2] = {
                          {0, 7}, {0, 8},
                  {1, 6}, {1, 7}, {1, 8}, {1, 9},
                  {2, 6}, {2, 7}, {2, 8}, {2, 9},
                          {3, 7}, {3, 8},
          {4, 5}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 10},
  {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}, {5, 9}, {5, 10}, {5, 11},
  {6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 11},
  {7, 4},         {7, 6}, {7, 7}, {7, 8}, {7, 9},          {7, 11},
  {8, 4},         {8, 6}, {8, 7}, {8, 8}, {8, 9},          {8, 11},
  {9, 4},         {9, 6}, {9, 7}, {9, 8}, {9, 9},          {9, 11},
  {10, 4},        {10, 6},                {10, 9},         {10, 11},
		  {11, 6},                {11, 9},     
	          {12, 6},                {12, 9},
	          {13, 6},                {13, 9},
	          {14, 6},                {14, 9},
	          {15, 6},                {15, 9}
};

//each pair is a {y, x} coord
//len of this is 62
int punchMan[][2] = {
                          {0, 7}, {0, 8},
                  {1, 6}, {1, 7}, {1, 8}, {1, 9},
                  {2, 6}, {2, 7}, {2, 8}, {2, 9},                  {2, 12},
                          {3, 7}, {3, 8},                  {3, 11},
          {4, 5}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 10}, {4, 11}, 
  {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}, {5, 9}, {5, 10}, {5, 11},
  {6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8}, {6, 9}, {6, 10},
  {7, 4},         {7, 6}, {7, 7}, {7, 8}, {7, 9},
  {8, 4},         {8, 6}, {8, 7}, {8, 8}, {8, 9},
  {9, 4},         {9, 6}, {9, 7}, {9, 8}, {9, 9},
  {10, 4},        {10, 6},                {10, 9},
		  {11, 6},                {11, 9},     
	          {12, 6},                {12, 9},
	          {13, 6},                {13, 9},
	          {14, 6},                {14, 9},
	          {15, 6},                {15, 9}
};

//len is 68
int walkMan[][2] = {
                                           {16, 7}, {16, 8},
                                  {17, 6}, {17, 7}, {17, 8}, {17, 9},
                                  {18, 6}, {18, 7}, {18, 8}, {18, 9},
                                           {19, 7}, {19, 8},
                                  {20, 6}, {20, 7}, {20, 8}, {20, 9}, {20, 10}, {20, 11},
                  		  {21, 6}, {21, 7}, {21, 8}, {21, 9}, {21, 10},          {21, 12},
                		  {22, 6}, {22, 7}, {22, 8}, {22, 9}, {22, 10},                    {22, 13},
                        {23, 5},           {23, 7}, {23, 8}, {23, 9}, {23, 10},                    {23, 13},
                {24, 4},		   {24, 7}, {24, 8}, {24, 9}, {24, 10},                    {24, 13},
        {25, 3},			   {25, 7}, {25, 8}, {25, 9}, {25, 10},                    {25, 13},
                	          {26, 6}, {26, 7},          {26, 9}, {26, 10},
                	{27, 5},  {27, 6}, 		    	      {27, 10},
                	{28, 5}, 		 		      {28, 10}, {28, 11},
                        {29, 5},                                      {29, 10}, {29, 11},
                {30, 4},{30, 5}, 		 		                {30, 11}, {30, 12},
        {31, 3},{31, 4}, 		 		    				  {31, 12}
};

//sound variables
int stopMelody[] = { NOTE_DS5, NOTE_DS5 };
int goMelody[] = { NOTE_DS5 };
int noteDurations[] = {
  8,8,4,
};

int soundSpeed = 1450;


//BLUE SIDE INPUTS
int blueButtonPin = 4; //pin no for input BLUE PLAYER
int bluePunchOnePin = 17; //pin for BLUE PLAYER (PUNCHER)
//int contactRawVal = 0; //raw input value from the contact switch
//boolean contactVal = false; //value from contact switch mapped to boolean
int blueButtonState;  //current reading of the input pin
int lastBlueButtonState = LOW; //previous reading for the blue button
int bluePunchOneState; //current state of puncher
int lastBluePunchOneState = LOW; //previous reading of puncher

int bluePunchTwoPin = 18;
int bluePunchTwoState; //current state of puncher
int lastBluePunchTwoState = LOW; //previous reading of puncher

int bluePunchThreePin = 19;
int bluePunchThreeState; //current state of puncher
int lastBluePunchThreeState = LOW; //previous reading of puncher


//RED PLAYER INPUTS
//red button
int redButtonPin = 3; //pin for RED PLAYER
int redButtonState; //current reading of the red button pin;
int lastRedButtonState = LOW; //previous reading for the red button;
//punch inputs
int redPunchOnePin = 16; //red ONE
int redPunchOneState;
int lastRedPunchOneState = LOW;
int redPunchTwoPin = 15; //red TWO
int redPunchTwoState;
int lastRedPunchTwoState = LOW;
int redPunchThreePin = 14; //red THREE
int redPunchThreeState;
int lastRedPunchThreeState = LOW;
int redPunchFourPin = 2; //red FOUR
int redPunchFourState;
int lastRedPunchFourState = LOW;


boolean playable = true;
int pushbackLimit = 2; //how many button presses will = 1 with pushback (changes dynamically)

//debouncing values...
long lastRedButtonDebounce = 0;
long lastRedPunchOneDebounce = 0;
long lastRedPunchTwoDebounce = 0;
long lastRedPunchThreeDebounce = 0;
long lastRedPunchFourDebounce = 0;
long lastBlueButtonDebounce = 0;
long lastBluePunchOneDebounce = 0;
long lastBluePunchTwoDebounce = 0;
long lastBluePunchThreeDebounce = 0;
long debounceDelay = 40; //in milliseconds (I think?)

//int redScorebarPin = 10;
int scorebarPin = 21;
Servo redServo;
int redServoPin = 45;
int redPos = 30; //track position of servo

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, scorebarPin, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  Serial.begin(9600);
  
  //pinMode(contactPin, INPUT);
  pinMode(blueButtonPin, INPUT);
  pinMode(redButtonPin, INPUT);
  pinMode(redPunchOnePin, INPUT);
  pinMode(redPunchTwoPin, INPUT);
  pinMode(redPunchThreePin, INPUT);
  pinMode(redPunchFourPin, INPUT);
  pinMode(bluePunchOnePin, INPUT);
  pinMode(bluePunchTwoPin, INPUT);
  pinMode(bluePunchThreePin, INPUT);
  
  strip.begin();
  strip.show();
  
  redServo.attach(redServoPin); //attach
  redServo.write(redPos);
  resetBots();
  
  //set the timer
  MsTimer2::set(100, signalLight);// run every sec
  MsTimer2::start();
  
  matrix.begin();
}

void loop() {

  int redButtonReading = digitalRead(redButtonPin);
  int redPunchOneReading = digitalRead(redPunchOnePin);
  int redPunchTwoReading = digitalRead(redPunchTwoPin);
  int redPunchThreeReading = digitalRead(redPunchThreePin);
  int redPunchFourReading = digitalRead(redPunchFourPin);
  int blueButtonReading = digitalRead(blueButtonPin);
  int bluePunchOneReading = digitalRead(bluePunchOnePin);
  int bluePunchTwoReading = digitalRead(bluePunchTwoPin);
  int bluePunchThreeReading = digitalRead(bluePunchThreePin);
  Serial.print("Punch one:");
  Serial.println(redPunchOneReading);
  Serial.print("punch two: ");
  Serial.println(redPunchTwoReading);
  Serial.print("punch three: ");
  Serial.println(redPunchThreeReading);
  Serial.print("punch four: ");
  Serial.println(redPunchFourReading);
  //delay(4);
  //debounce check...
  //RED DEBOUNCING
  if (redButtonReading != lastRedButtonState) {
    lastRedButtonDebounce = millis();
  }
  if (redPunchOneReading != lastRedPunchOneState) {
    lastRedPunchOneDebounce = millis();
  }
  if (redPunchTwoReading != lastRedPunchTwoState) {
    
    lastRedPunchTwoDebounce = millis();
  }
  if (redPunchThreeReading != lastRedPunchThreeState) {
    lastRedPunchThreeDebounce = millis();
  }
  if (redPunchFourReading != lastRedPunchFourState) {
    lastRedPunchFourDebounce = millis();
  }
  
  
  if (blueButtonReading != lastBlueButtonState) {
    lastBlueButtonDebounce = millis();
  }
  if (bluePunchOneReading != lastBluePunchOneState) {
    lastBluePunchOneDebounce = millis();
  }
  if (bluePunchTwoReading != lastBluePunchTwoState) {
    lastBluePunchTwoDebounce = millis();
  }
  if (bluePunchThreeReading != lastBluePunchThreeState) {
    lastBluePunchThreeDebounce = millis();
  }
  
  //red button debounce checking
  if ((millis() - lastRedButtonDebounce) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (redButtonReading != redButtonState) {
      redButtonState = redButtonReading;

      // only toggle the LED if the new button state is HIGH
      if (redButtonState == HIGH) {
        incrementScore('r');
        redPunch = true;
        drawRed = true;
      } else {
        redPunch = false;
        drawRed = true;
      }
    }
  }
  
  //red punch ONE debounce checking
  if ((millis() - lastRedPunchOneDebounce) > debounceDelay) {

    if (redPunchOneReading != redPunchOneState) {
      redPunchOneState = redPunchOneReading;
      
      // only toggle the LED if the new button state is HIGH
      if (redPunchOneState == HIGH) {
        Serial.println("Red ONE score!");
        
        incrementScore('r');
        redPunch = true;
        drawRed = true;
      } else {
        redPunch = false;
        drawRed = true;
      }
    }
  }
  
  //red punch Two debounce checking
  if ((millis() - lastRedPunchTwoDebounce) > debounceDelay) {
    
    if (redPunchTwoReading != redPunchTwoState) {
      redPunchTwoState = redPunchTwoReading;
      // only toggle the LED if the new button state is HIGH
      if (redPunchTwoState == HIGH) {    
        Serial.println("Red TWO score!");    
        incrementScore('r');
        redPunch = true;
        drawRed = true;
      } else {
        redPunch = false;
        drawRed = true;
      }
    }
  }
    //red punch Three debounce checking
  if ((millis() - lastRedPunchThreeDebounce) > debounceDelay) {
    
    if (redPunchThreeReading != redPunchThreeState) {
      redPunchThreeState = redPunchThreeReading;
      // only toggle the LED if the new button state is HIGH
      if (redPunchThreeState == HIGH) {
        Serial.println("Red THREE score!");
        
        incrementScore('r');
        redPunch = true;
        drawRed = true;
      } else {
        redPunch = false;
        drawRed = true;
      }
    }
  }
    //red punch Four debounce checking
  if ((millis() - lastRedPunchFourDebounce) > debounceDelay) {
    if (redPunchFourReading != redPunchFourState) {
      redPunchFourState = redPunchFourReading;
      
      // only toggle the LED if the new button state is HIGH
      if (redPunchFourState == HIGH) {
        Serial.println("Red FOUR score!");
        incrementScore('r');
        redPunch = true;
        drawRed = true;
      } else {
        redPunch = false;
        drawRed = true;
      }
    }
  }
  //blue button debounce checking
  if ((millis() - lastBlueButtonDebounce) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (blueButtonReading != blueButtonState) {
      blueButtonState = blueButtonReading;

      // only toggle the LED if the new button state is HIGH
      if (blueButtonState == HIGH) {
        incrementScore('b');
      }
    }
  }
  
  if ((millis() - lastBluePunchOneDebounce) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (bluePunchOneReading != bluePunchOneState) {
      bluePunchOneState = bluePunchOneReading;

      // only toggle the LED if the new button state is HIGH
      if (bluePunchOneState == HIGH) {
        bluePunch = true;
        drawBlue = true;
        incrementScore('b');
      } else {
        bluePunch = false;
        drawBlue = true;
      } 
    }
  }
  
  if ((millis() - lastBluePunchTwoDebounce) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (bluePunchTwoReading != bluePunchTwoState) {
      bluePunchTwoState = bluePunchTwoReading;

      // only toggle the LED if the new button state is HIGH
      if (bluePunchTwoState == HIGH) {
        bluePunch = true;
        drawBlue = true;
        incrementScore('b');
      } else {
        bluePunch = false;
        drawBlue = true;
      } 
    }
  }
  if ((millis() - lastBluePunchThreeDebounce) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (bluePunchThreeReading != bluePunchThreeState) {
      bluePunchThreeState = bluePunchThreeReading;

      // only toggle the LED if the new button state is HIGH
      if (bluePunchThreeState == HIGH) {
        bluePunch = true;
        drawBlue = true;
        incrementScore('b');
      } else {
        bluePunch = false;
        drawBlue = true;
      } 
    }
  }
  
  //BLUE PLAYER INPUT
  //for the contact switch, input is taken once for every flip to "on" (1)
  /*if (contactRawVal != 0) {
    contactVal = true;
    //incrementScore('b');
  } else {
    if (contactVal) {
      //first time it has fliped to false from being true
      //score point.
      incrementScore('b');
    }
    contactVal = false;
  }*/
  
  //draw the signal lights
  if (drawRed) {
    drawRed = false;
    if (!walkLight) { //is red
      matrix.fillRect(32, 0, 64, 15, matrix.Color333(0, 0, 0)); //clears the other part of the board.
      if (!redPunch) {
        //not punching
        drawMans(stopMan, 64, 'r');
      } else {
        //else punch!
        drawMans(punchMan, 62, 'r'); //b to draw it TO blue pole        
        redPunch = false;
      }
    } else { //is green
      matrix.fillRect(32, 0, 64, 15, matrix.Color333(0, 0, 0));
      drawMans(walkMan, 66, 'r');
    }
  }
  if (drawBlue) {
    drawBlue = false;
    if (!walkLight) { //is red
      matrix.fillRect(0, 0, 32, 15, matrix.Color333(0, 0, 0)); //clears the other part of the board.
      //if punched less than 30ms ago... draw bluepunchman
      if (!bluePunch) {
        //not punching
        drawMans(stopMan, 64, 'b');
      } else {
        //else punching
        drawMans(punchMan, 62, 'b'); //r to draw it TO red pole
        bluePunch = false;
      }
    } else { //is green
      matrix.fillRect(0, 0, 32, 15, matrix.Color333(0, 0, 0));
      drawMans(walkMan, 66, 'b');
    }
  }
  
  //draw the score onto the LED strip
  drawScore();
  lastRedButtonState = redButtonReading;
  lastRedPunchOneState = redPunchOneReading;
  lastRedPunchTwoState = redPunchTwoReading;
  lastRedPunchThreeState = redPunchThreeReading;
  lastRedPunchFourState = redPunchFourReading;
  
  lastBlueButtonState = blueButtonReading;
  lastBluePunchOneState = bluePunchOneReading;
  lastBluePunchTwoState = bluePunchTwoReading;
  lastBluePunchThreeState = bluePunchThreeReading;
  
  //matrix.drawPixel(0, 15, matrix.Color333(6, 0, 4));
  //matrix.drawPixel(32, 15, matrix.Color333(0, 0, 7));
}

//checks that the player score does not exceed boundaries, and the sum of both is 10
//returns true or false if the score is able to be incremented
boolean checkScore(char player) {
  int playerScore;
  int otherPlayerScore;
  
  if (player == 'r') {
    playerScore = redScore;
    otherPlayerScore = blueScore;
  } else if (player == 'b') {
    playerScore = blueScore;
    otherPlayerScore = redScore;
  }
  
  if (blueScore + redScore == maxPoints && playerScore >= 0 && playerScore < maxPoints ) {
    //also check if they should have pushback turned on.
    //if pushback is on, only let 1 / 5 presses return true
    if (otherPlayerScore < (maxPoints/10)){
      pushbackLimit = 10;
      if (pushback(player)) {
        return true;
      }
    } else if (otherPlayerScore == (maxPoints/10)) {
      pushbackLimit = 5;
      if (pushback(player)) {
        return true;
      }
    } else if (otherPlayerScore <= (maxPoints/5)) {
      pushbackLimit = 3;
      if (pushback(player)) {
        return true;
      }
    } else {
      return true;
    }
  } else { 
    return false;
  }
  
  
  
}

//increments the score for the given player
//accepts "r" and "b" as players (RED and BLUE)
void incrementScore(char player){
  
  if (playable) {
    if (player == 'r') {
      boolean red = checkScore(player);
      if (red) {
        redScore = redScore + 1;
        blueScore = blueScore - 1;
      }    
    }
    
    if (player == 'b') {
      boolean blue = checkScore(player);
      if (blue) {
        blueScore = blueScore + 1;
        redScore = redScore - 1;
      } 
    }
  }
  
  /*Serial.print("RED: ");
  Serial.print(redScore);
  Serial.print(" -- BLUE: ");
  Serial.println(blueScore);*/
}

void drawScore() {  
  //draw red from 0 upwards
  for (int redi = 0; redi < redScore+blueScore; redi++) {
    strip.setPixelColor(redi, 255, 0, 0);
  }
  //blue pixels START drawing from where the redScore pixel ends
  for (int bluei = redScore; bluei < blueScore+redScore; bluei++) {
    strip.setPixelColor(bluei, 0, 0, 255);
  }
  
  strip.show();
}

//flips the signal lights...
void signalLight()
{
  count++;
   /*********************** the green light is on **************************/
  if(walkLight) {
    //tone(46, NOTE_A4, 80);
    tone(46, NOTE_C6, 60);
    if (count > 20) {
     resetBots();
     playable = true; //flip game to playable  
     blueScore = singleScore; //reset the game to start again. 
     redScore = singleScore;
     walkLight = false;
     drawBlue = true;
     drawRed = true;
     count = 0;
    }
  }
  /*********************** the red light is on **************************/
  else {
    if (count % 10 == 0) {
      tone(46, NOTE_D5, 100);
    }
    if (count > 200) {
      playable = false; //flip game to NOT playable
      walkLight = true;
      drawBlue = true;
      drawRed = true;
      
      //check who won and set robot to lose.
      if (redScore > blueScore) {
        //red won, pop blue
        botLose('b');
      } else if ( blueScore > redScore ) {
        //blue won, pop red
        botLose('r');
      } else if ( blueScore == redScore ) {
        //it is a tie... do the thing.
        botLose('d');
      }
      count = 0;
    }
  }
}

//controls lose state of robot heads
//possible chars are : 'r', 'b', 'd' for a DRAW
void botLose(char player) {
  
  //if player red lost, or draw, send red UP
  if (player == 'r' || player == 'd') {
    //send lose state to other board.
    redPos = 100;
    redServo.write(redPos);
  }
}

//resets the bot heads between each game.
void resetBots() {
  //Serial.println("resetting bots");
  //send reset / down state to othe
  if (redPos == 100) {
    redPos = 30;
    redServo.write(redPos);
  }
  
}

int bluePushCount = 0;
int redPushCount = 0;
//returns true if this player can score a point yet.
boolean pushback(char player) {
  if (player == 'r') {
    redPushCount++;
    if (redPushCount >= pushbackLimit) {
      redPushCount = 0;
      return true;
    } else {
      return false;
    }
  }
  if (player == 'b') {
    bluePushCount++;
    //Serial.println(bluePushCount);
    if (bluePushCount >= pushbackLimit) {
      bluePushCount = 0;
      return true;
    } else {
      return false;
    }
  }
}

//draws the given array of xy coords onto the matrix
void drawMans(int man[][2], int len, char p) {
  int r = 7;
  int g = 0;
  if (walkLight) {
    r = 0;
    g = 7;
  };
  if (p == 'r') {
    for (int i = 0; i <= len+1; i++) {
      matrix.drawPixel(man[i][0]+32, man[i][1], matrix.Color333(r, g, 0)); //for screen one
    }
  } else if ( p == 'b') {
    for (int i = 0; i <= len+1; i++) {
      matrix.drawPixel(man[i][0], man[i][1], matrix.Color333(r, g, 0)); //for sreen two
    }
  } 
  
}
