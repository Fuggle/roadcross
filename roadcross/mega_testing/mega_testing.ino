//Signal light variables
int count = 0;
boolean walkLight = false; //false = red, true = green
boolean draw = true;
boolean playable = true;

int buttonPin = 5;

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <MsTimer2.h> //timer

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

//original library snippet
//RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);



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
//len of this is 64
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


void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  
  //set the timer
  MsTimer2::set(1000, signalLight);// run every sec
  MsTimer2::start();
  
  matrix.begin();
}

void loop() {
  int buttonVal = digitalRead(buttonPin);
  // put your main code here, to run repeatedly:
  //ledstate = !digitalRead(testpin);
  //clear the display between frames...
  Serial.println(buttonVal);
  //digitalWrite(testpin, ledstate);
  if (draw) {
    draw = false;
    if (!walkLight) { //is red
      matrix.fillRect(0, 0, 64, 32, matrix.Color333(0, 0, 0)); //clears the other part of the board.
      drawMans(stopMan, 64);
    } else { //is green
      matrix.fillRect(0, 0, 64, 32, matrix.Color333(0, 0, 0));
      drawMans(walkMan, 66);
    }
  }
  
  //scrolling display test
  /*matrix.fillRect(0, 0, 64, 16, matrix.Color333(0, 0, 0));
  for (int i = 0; i < 64; i++) {
    matrix.drawPixel(i, 8, matrix.Color333(2, 2, 7));
    delay(50);
  }*/
  
}


//flips the signal lights...
void signalLight()
{
  count++;
   /*********************** the green light is on **************************/
  if(walkLight) //is green
  {
    if (count > 3)
    {
     playable = true; //flip game to playable  
     //digitalWrite(signalPinGreen,LOW);
     //digitalWrite(signalPinRed, HIGH);
     walkLight = false;
     draw = true;
     count = 0;
    }
  }
  /*********************** the red light is on **************************/
  else
  {
    if (count > 8)
    {
      playable = false; //flip game to NOT playable
      //digitalWrite(signalPinGreen,HIGH);
      //digitalWrite(signalPinRed,LOW);
      walkLight = true;
      draw = true;
      count = 0;
    }
  }
}


//draws the given array of xy coords onto the matrix
void drawMans(int man[][2], int len) {
  int r = 7;
  int g = 0;
  if (walkLight) {
    r = 0;
    g = 7;
  };
  for (int i = 0; i <= len+1; i++) {
    matrix.drawPixel(man[i][0], man[i][1], matrix.Color333(r, g, 0)); //for screen one
    matrix.drawPixel(man[i][0]+32, man[i][1], matrix.Color333(r, g, 0)); //for sreen two
  }
}

