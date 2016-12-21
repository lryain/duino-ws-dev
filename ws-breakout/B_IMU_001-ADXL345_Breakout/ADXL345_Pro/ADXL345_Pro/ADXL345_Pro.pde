import processing.serial.*; 
Serial duankou;
int   Y_Rotate=90, X_Rotate=90;
void setup() 
{ 
  size(800,600, P3D); 
  stroke(102); 
  strokeWeight(20);
  colorMode(RGB, 1); 


  duankou = new Serial(this,"COM9",9600);  
} 
//主程序
void draw() 
{ 
  background(0.5); 
  pushMatrix();
  
  translate(width/2, height/2, -150); 
  while(duankou.available()<3);
  Y_Rotate= duankou.read();
  X_Rotate = duankou.read();
 
  rotateX((X_Rotate-90) * PI / 180.0);
  rotateZ((Y_Rotate-90) * PI / 180.0);   
  scale(150);
  beginShape(QUADS);
  fill(0, 1, 1); vertex(-1,  1,  1);
  fill(1, 1, 1); vertex( 1,  1,  1);
  fill(1, 0, 1); vertex( 1, -1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);

  fill(1, 1, 1); vertex( 1,  1,  1);
  fill(1, 1, 0); vertex( 1,  1, -1);
  fill(1, 0, 0); vertex( 1, -1, -1);
  fill(1, 0, 1); vertex( 1, -1,  1);

  fill(1, 1, 0); vertex( 1,  1, -1);
  fill(0, 1, 0); vertex(-1,  1, -1);
  fill(0, 0, 0); vertex(-1, -1, -1);
  fill(1, 0, 0); vertex( 1, -1, -1);

  fill(0, 1, 0); vertex(-1,  1, -1);
  fill(0, 1, 1); vertex(-1,  1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);
  fill(0, 0, 0); vertex(-1, -1, -1);

  fill(0, 1, 0); vertex(-1,  1, -1);
  fill(1, 1, 0); vertex( 1,  1, -1);
  fill(1, 1, 1); vertex( 1,  1,  1);
  fill(0, 1, 1); vertex(-1,  1,  1);

  fill(0, 0, 0); vertex(-1, -1, -1);
  fill(1, 0, 0); vertex( 1, -1, -1);
  fill(1, 0, 1); vertex( 1, -1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);
  endShape();
  popMatrix(); 
} 

