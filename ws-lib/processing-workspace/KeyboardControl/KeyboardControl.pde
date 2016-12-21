import processing.serial.*;

 // Serial Variables
 Serial serialPort;    // The serial port: 
 int baudRate = 9600; //make sure this matches the baud rate in the arduino program.
 int lf = 10;
 
 // Font Settings
 PFont font;
 
 // Sensor Variables
 String direction = "N";
 int sensorReading;
 int angle;
 int degreeIncrement = 6;
 
 int startAngle = 0;
 int endAngle = 180;
 
 int totalReadings = 0;
 
 void setup(){
   smooth();
   size(600, 400);
 
   //270 is Helvetica-Neue (my current favorite) to get a list use println(PFont.list());
   font = createFont(PFont.list()[200], 24); 
   textFont(font); 
 
   serialPort = new Serial(this, Serial.list()[0], baudRate);
   serialPort.bufferUntil(lf);
 
   //noLoop();
 }
 
 
void draw()
{
  background(#266014);
  renderDirection();
}

void serialEvent(Serial p) {
  String inString;
  try {
    inString = (serialPort.readString());
    
    noStroke();
    smallFont();
    text("Receved commamd is: " + inString, 10, 300);
  }
  catch(Exception e) {
    println(e);
  }
  redraw();
}

void keyPressed()
{
  noStroke();
  smallFont();
  text("Send commamd is: " + key, 10, 100);
  if(key=='w'){
    direction = "N";
    serialPort.write('f');
  }else if(key=='s'){
    direction = "S";
    serialPort.write('b');
  }else if(key=='a'){
    direction = "W";
    serialPort.write('l');
  }else if(key=='d'){
    direction = "E";
    serialPort.write('r');
  }else{
    serialPort.write('s');
    renderAlert();
  }
}

void renderDirection(){
  fill(#e38a20);
  rect(400,0,200,200);
  smallFont();
  noStroke();
  renderNorth(direction.equals("N"));
  renderSouth(direction.equals("S"));
  renderWest(direction.equals("W"));
  renderEast(direction.equals("E")); 
}
 
void renderNorth(boolean isCurrent){
  if(isCurrent == true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(225), radians(315)); 
  }else{
    fill(#696969, 475);
    arc(500, 100, 150, 150, radians(225), radians(315));
  } 
  fill(#ffffff);
  text("N", 492, 50);
}
 
void renderSouth(boolean isCurrent){
  if(isCurrent==true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(45), radians(135));
  }else{
    fill(#696969, 475);
    arc(500, 100, 150, 150, radians(45), radians(135));
  }  
  fill(#ffffff);
  text("S", 492, 165);
}
 
void renderWest(boolean isCurrent){
  if(isCurrent==true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(135), radians(225));
  }else{
    fill(#464646, 475);
    arc(500, 100, 150, 150, radians(135), radians(225));
  }  
  fill(#ffffff);
  text("W", 435, 110);
}
 
void renderEast(boolean isCurrent){
  // the 405 angle here is weird, you'd think that because you're starting at 315
  // it would be 45 (the beginning of the South arc), but
  // you have to continue around the circle adding angles
  // in when you pass the 360/0 degrees mark
  if(isCurrent==true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(315), radians(405));
  }else{
    fill(#464646, 475);
    arc(500, 100, 150, 150, radians(315), radians(405));
  }  
  fill(#ffffff);
  text("E", 553, 110);
}
 
void renderAlert(){
  largeFont();
  fill(#980f0f);
  rect(400,200,200,200);
  fill(#ffffff);
  text("ALERT", 440, 305);
}
 
void renderClear(){
  mediumFont();
  fill(#ffffff);
  text("CLEAR", 450, 305);
}
 
void smallFont(){  textFont(font, 24); }
void mediumFont(){ textFont(font, 30); }
void largeFont(){  textFont(font, 40); }
