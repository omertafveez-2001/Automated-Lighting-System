//IO Pins
const byte motion1 = 4;
const byte reed = 6;
const byte relay = 7;
const byte m1Led = 2;
const byte reedLed = 3;
const byte test = 10;
const byte on = 9;

//variables
unsigned long mTime = 0;
unsigned long wTime = 600000;


void setup() {
  //set pins as input or output
  pinMode(motion1,INPUT);
  pinMode(reed,INPUT_PULLUP);
  pinMode(relay,OUTPUT);
  pinMode(m1Led,OUTPUT);
  pinMode(reedLed,OUTPUT);
  pinMode(test,INPUT_PULLUP);
  pinMode(on,INPUT_PULLUP);
  digitalWrite(relay,HIGH);
  //show loading sign
  for(byte i=0;i<60;i++){
    digitalWrite(m1Led,HIGH);
    delay(250);
    digitalWrite(reedLed,HIGH);
    delay(250);
    digitalWrite(m1Led,LOW);
    digitalWrite(reedLed,LOW);
    delay(500);
  }
}

void loop() {
  //if the switch is set to always ON
  if(digitalRead(on)==LOW){
    digitalWrite(relay,HIGH);
  }
  //if its set to AUTO or TEST
  else{
    //check if there is motion
    if(digitalRead(motion1)==HIGH){
      //mark the time of the motion
      mTime = millis();
      //indicate with led
      digitalWrite(m1Led,HIGH);
    }
    else{
      //otherwise keep led off
      digitalWrite(m1Led,LOW);
    }
    //check if the door is open
    if(digitalRead(reed)==HIGH){
      mTime = millis();
      digitalWrite(reedLed,HIGH);
    }
    else{
      digitalWrite(reedLed,LOW);
    }
    //check if the switch is set to TEST
    if(digitalRead(test)==LOW){
      wTime = 15000;
    }
    //if switch is set to AUTO
    else{
      wTime = 600000;
    }
    //check if the light needs to be turned off
    if((millis()-mTime)>wTime){
      digitalWrite(relay,LOW);
    }
    //otherwise keep it on
    else{
      digitalWrite(relay,HIGH);
    }
  }
  //delay for stabilization
  delay(10);
}
