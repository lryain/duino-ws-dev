// TRANSCEIVER VARIABLES //
int west = 0;
int south = 0;
int east = 0;
int north = 0;
int dir = 0;

boolean detected = false;

// TRANSCEIVER DIRECTION MODE VARIABLES //
const int NUM_READINGS = 10;
int directionReadings[NUM_READINGS];
int modeOfDirections = 1;
int index = 0;

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
  moveTowardBeacon();
}

void moveTowardBeacon()
{
  readTransceiverandSetDirection();
  
  if(modeOfDirections == 4){ // or West
    Serial.println("turnLeft");
  } else if(modeOfDirections == 3) { // South
    Serial.println("motorMoveBackward");
  } else if(modeOfDirections == 2) { // East
    Serial.println("turnRight");
  } else if(modeOfDirections == 1){ //North
    Serial.println("motorMoveForward");
  }
}

//  BEACON LOGIC  //
void readTransceiverandSetDirection(){
  west = analogRead(2); //left
  south = analogRead(3); //back
  east = analogRead(4); //right
  north = analogRead(5); //front
 /*
  Serial.println("");  
  Serial.print("The 4 IR value is[front:");
  Serial.print(north);
  Serial.print("-");
  Serial.print("back:");
  Serial.print(south);
  Serial.print("-");
  Serial.print("left:");
  Serial.print(west);
  Serial.print("-");
  Serial.print("right:");
  Serial.print(east);
  Serial.println("]");
  */
  getDirection();
  setModeOfDirections();
}

void getDirection(){   
  int minValue = 100;   
  if(minValue >= west){
    minValue = west;
    dir = 4;
  }
  if(minValue >= south){
    minValue = south;
    dir = 3;
  }
  if(minValue >= east){
    minValue = east;
    dir = 2;
  }
  if(minValue >= north){
    minValue = north;
    dir = 1;
  }

  /*
  Serial.print("dir is:[");
  Serial.print(dir);
  Serial.println("]");
  */
  addDirectionToReadings();

  if(dir == 1){
    Serial.println("N");
  }else if(dir == 2){
    Serial.println("E");
  }else if(dir == 3){
    Serial.println("S");
  }else if(dir == 4){
    Serial.println("W");
  }
}

void addDirectionToReadings(){
  directionReadings[index] = dir;

  index = (index + 1);
  if (index >= NUM_READINGS)             // if we're at the end of the array...
    index = 0;
}

// =========================================
// In order to smooth out the directions readings from the
// IR transceiver, You have to take the mode (most prevalent number in a collection)
// of the directionReadings Array.  This allows the program to determine which
// direction is being read the most from the device.
// Otherwise, the readings make the robot squirrelly.
// ========================================
void setModeOfDirections(){
  int directionCounts[4] = { 0,0,0,0 }; //{North(1), East(2), South(3), West(4)}

  for (int i = 1; i < NUM_READINGS; ++i){
    //Serial.print(directionReadings[i]);
    //Serial.print("[");
    ++directionCounts[directionReadings[i]-1];
    //Serial.print(directionCounts[directionReadings[i]-1]);
    //Serial.print("]");
  }

  //Determine mode of directions from count array
  //Serial.println("");
  int modeCount[2] = { 1,directionCounts[0]  }; //This array holds the current maximum count and the direction it points to.
  for(int i = 0; i < 4; ++i){
    //Serial.print(directionCounts[i]);
    //Serial.print("|");
    if(directionCounts[i] >= modeCount[1]){
      modeCount[0] = i + 1; // set direction
      modeCount[1] = directionCounts[i]; //set count
    }
  }

  modeOfDirections = modeCount[0];
  //Serial.println("");
  //Serial.print("Direction Mode: ");
  //Serial.println(modeOfDirections);
}
