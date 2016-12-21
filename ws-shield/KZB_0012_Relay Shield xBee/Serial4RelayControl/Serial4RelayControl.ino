//Relay control on arduino digital pins. 
unsigned char relayPin[4] = {4,5,6,7};
//Relay name Correspond to relay pins. example a=4, b=5, c=6, d=7
unsigned char relayNum[4] = {'a','b','c','d'};
// If you know the size of the String you're expecting, you could use a char[] instead.
String incomingString; // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
// example string "a1,b0,c0,d0"
char splitChar = ',';
char toggleChar = '*';
const int swnum = 4;
String singleCmd[swnum];

void setup() {
    Serial.begin(9600);
    Serial.println("Power On");
    for(int i = 0; i < 4; i++)
    {
      pinMode(relayPin[i],OUTPUT);
      digitalWrite(relayPin[i],LOW);
    }
}

 int getRelayPinByNum(char relayNumChar){
  for(int i=0; i<4; i++){
    if(relayNumChar==relayNum[i]){
      return relayPin[i];
    }
  }
 }
 
void loop()
{
  while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read(); 
      if (inChar =='#') {
        stringComplete = true;
      } 
      // add it to the inputString:
      if(stringComplete == false) {
        incomingString += inChar;
      }
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
    }
    
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print("incomingString: "); 
    Serial.println(incomingString); 
    // handle
    if(incomingString.indexOf(splitChar)>0){//full command
      Serial.println("full mode");
      for(int i=0; i<swnum; i++){
        singleCmd[i] = incomingString.substring(i*3,i*3+2);
        char relayNum = singleCmd[i].substring(0,1).charAt(0);
        char relayStatus = singleCmd[i].substring(1,2).charAt(0);
        int relayPin = getRelayPinByNum(relayNum);
        Serial.print("relayNum: "); 
        Serial.println(relayPin );
        Serial.print("relayStatus: "); 
        Serial.println(relayStatus );
        if(relayStatus=='1'){
          digitalWrite(relayPin,HIGH);
        }else{
          digitalWrite(relayPin,LOW);
        }
      }
    }else{//single command
      if(incomingString.indexOf(toggleChar)>0){//toggle mode
        Serial.println("toggle mode"); 
        char relayNum = incomingString.substring(0,1).charAt(0);
        int relayPin = getRelayPinByNum(relayNum);
        Serial.print("relayNum: "); 
        Serial.println(relayPin);
        Serial.print("relayStatus: "); 
        Serial.println(digitalRead(relayPin)==HIGH?LOW:HIGH );
        digitalWrite(relayPin,digitalRead(relayPin)==HIGH?LOW:HIGH);
      }else{//free mode
        Serial.println("single mode"); 
        char relayNum = incomingString.substring(0,1).charAt(0);
        char relayStatus = incomingString.substring(1,2).charAt(0);
        int relayPin = getRelayPinByNum(relayNum);
        Serial.print("relayNum: "); 
        Serial.println(relayPin );
        Serial.print("relayStatus: "); 
        Serial.println(relayStatus );
        if(relayStatus=='1'){
          digitalWrite(relayPin,HIGH);
        }else{
          digitalWrite(relayPin,LOW);
        }
      }
    }
    // clear the string:
    incomingString = "";
    stringComplete = false;
  }
}
