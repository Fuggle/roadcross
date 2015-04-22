int redScore = 5;
int blueScore = 5;

int contactPin = 13; //pin no for input BLUE PLAYER
int flexPin = 0; //pin for flex sensor RED PLAYER

int switchVal = 0; //raw input value from the contact switch
int contactVal = false; //value from contact switch mapped to boolean
int sensorRange = 0; //the range recorded from the flex sensor

//NEOPIXEL setup
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 7

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void setup() {
  Serial.begin(9600);
 
  pinMode(contactPin, INPUT);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int flexVal, degrees;
  switchVal = digitalRead(contactPin); //BLUE, contact punch pad
  flexVal = analogRead(flexPin); //RED, flex punch pad
  
  //NEOPIXEL colours
  //strip.Color(255, 0, 0); // Red
  //strip.Color(0, 255, 0); // Green
  //strip.Color(0, 0, 255); // Blue
  
  
  // convert the voltage reading to inches
  // the first two numbers are the sensor values for straight (768) and bent (853)
  // the second two numbers are the degree readings we'll map that to (0 to 90 degrees)
  degrees = map(flexVal, 768, 853, 0, 90);
  
  //BLUE PLAYER INPUT
  //for the contact switch, input is taken once for every flip to "on" (1)
  if (switchVal != 0) {
    contactVal = true;
    incrementScore('b');
  } else {
    if (contactVal) {
      //first time it has fliped to false from being true
      //score point.
      //incrementScore('blue');
    }
    contactVal = false;
  }
  
  //RED PLAYER INPUT
  //for the flex sensor, while the reading is less than 705.. nothing
  //if it is greater than 705, record how much greater, 
  //when it flips back to 705, push range to score.
  if (flexVal > 705) {
    sensorRange = flexVal - 705;
  } else {
    //below 705, record sensorScore and flip it back to 0
    
  }
  
  
  //draw the score onto the LED strip
 drawScore();
 
  delay(200);
}

//Increments the score based on how hard the flex sensor was hit.
int sensorScore(int sensorRange) {
  //how should we calculate the contribution of harder punches to the score?
}

//checks that the player score does not exceed boundaries, and the sum of both is 10
//returns true or false if the score is able to be incremented
boolean checkScore(char player) {
  
  int playerScore;
  if (player == 'r') {
    int playerScore = redScore;
  } else if (player == 'b') {
    int playerScore = blueScore;
  }
  
  if (blueScore + redScore == 10 && playerScore >= 0 && playerScore < 10 ) {
    return true;
  } else { 
    return false;
  }
}

//increments the score for the given player
//accepts "red" and "blue" as players
void incrementScore(char player){
  boolean red = checkScore(redScore);
  boolean blue = checkScore(blueScore);
  
  if (player == 'r') {
    if (red) {
      redScore = redScore + 1;
      blueScore = blueScore - 1;
    }    
  }
  Serial.println(player);
  if (player == 'b') {
    if (blue) {
      blueScore = blueScore + 1;
      redScore = redScore - 1;
    } 
  }
}

void drawScore() {
  Serial.println(redScore);
  
  //draw red from 0 upwards
  for (int redi = 0; redi < redScore; redi++) {
    strip.setPixelColor(redi, 255, 0, 0);
  }
  //blue pixels START drawing from where the redScore pixel ends
  for (int bluei = redScore; bluei < blueScore+redScore; bluei++) {
    strip.setPixelColor(bluei, 0, 0, 255);
  }
  
  strip.show();
}

