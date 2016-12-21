void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i<70;i++){
  pinMode(i,OUTPUT);
  }



}

void loop() {
  // put your main code here, to run repeatedly:
 for(int i = 0;i<70;i++)
 { 
   digitalWrite(i,HIGH);
 }
 delay(500);
 for(int i = 0;i<70;i++)
 { 
   digitalWrite(i,LOW);
 } 
 delay(500);
}
