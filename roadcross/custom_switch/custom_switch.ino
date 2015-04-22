int redScore = 5;
int blueScore = 5;

int contactPin = 13; //pin no for input BLUE PLAYER
int flexPin = 0; //pin for flex sensor RED PLAYER

int switchVal = 0; //raw input value from the contact switch
int contactVal = false; //value from contact switch mapped to boolean
int sensorRange = 0; //the range recorded from the flex sensor

void setup() {
  Serial.begin(9600);
 
  pinMode(contactPin, INPUT);
}

void loop() {
  int flexVal, degrees;
  switchVal = digitalRead(contactPin); //BLUE, contact punch pad
  flexVal = analogRead(flexPin); //RED, flex punch pad
  
  // convert the voltage reading to inches
  // the first two numbers are the sensor values for straight (768) and bent (853)
  // the second two numbers are the degree readings we'll map that to (0 to 90 degrees)
  degrees = map(flexVal, 768, 853, 0, 90);
  
  //BLUE PLAYER INPUT
  //for the contact switch, input is taken once for every flip to "on" (1)
  if (switchVal != 0) {
    Serial.println("ON");
    contactVal = true;
  } else {
    if (contactVal) {
      //first time it has fliped to false from being true
      //score point.
      
    }
    contactVal = false;
    Serial.println("OFF");
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
  if (player == 'red') {
    int playerScore = redScore;
  } else if (player == 'blue') {
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
  if (player == 'red') {
    if (checkScore(redScore)) {
      redScore = redScore + 1;
      blueScore = blueScore - 1;
    }    
  } else if (player == 'blue') {
    if (checkScore(blueScore)) {
      blueScore = blueScore + 1;
      redScore = redScore - 1;
    }
    
  }
}

/*
if key == "w" then
		--player Blue
		if checkScore(playerBlue) then 
			playerBlue = playerBlue + 1; --should pass the score bumping to an external function for consistency
			playerRed = playerRed - 1;
		end
	end
	if key == "up" then
		--player Red
		if checkScore(playerRed) then 
			playerRed = playerRed + 1;
			playerBlue = playerBlue - 1;
		end
	end
*/

