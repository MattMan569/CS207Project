/*
  File: VideoGameControllerWithArduino.ino
  
  Purpose: This file is the slightly modified original from
    https://www.instructables.com/id/Video-Game-Controller-With-Arduino/
    that serves as a proof of concept and a basis for my own project to
    build off of.
*/

const int ButtonOne = 10;
const int ButtonTwo = 11;
const int ButtonThree = 12;
const int ButtonFour = 13;

void setup(){
   Serial.begin(1000000);

   pinMode(ButtonOne, INPUT);
   pinMode(ButtonTwo, INPUT);
   pinMode(ButtonThree, INPUT);
   pinMode(ButtonFour, INPUT);
} 

void loop(){
  if (digitalRead(ButtonOne))
  {
    Serial.println("1:");
    delay(100);
  }
  if (digitalRead(ButtonTwo))
  {
    Serial.println("2:");
    delay(100);
  }
  if (digitalRead(ButtonThree))
  {
    Serial.println("3:");
    delay(100);
  }
  if (digitalRead(ButtonFour))
  {
    Serial.println("4:");
    delay(100);
  }
}
