/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 6;
const int speakerPin = 9;

boolean buttonState = LOW;
boolean lastButtonState = LOW;
boolean firstTry = HIGH;


int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int tempoLine = 300;
int beatLine = 3;
int tempoDot = 100;
int beatDot = 2;

int buttonCounter = 0;
int score = 0;



void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
  
void playLine(){
  int tone = 2000;
  playTone(tone,beatLine * tempoLine);
}

void playDot(){
  int tone = 2000;
  playTone(tone,beatDot * tempoDot);
}


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buttonPin,INPUT);
  pinMode(speakerPin, OUTPUT);
  lcd.print("Morse Code Game");
  lcd.setCursor(0,1);
  lcd.print("Press B to Start");
}

void loop() {
  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != lastButtonState){
  	
    if(buttonState == HIGH){
      buttonCounter ++;
      Serial.print(buttonCounter);
      lcd.clear();
      
      if (buttonCounter == 1){
        
        lcd.setCursor(5,0);
      	lcd.print("LEVEL 1");
        lcd.setCursor(5,1);
        lcd.print("SCORE: ");
        lcd.setCursor(11,1);
        lcd.print(score);
        
        delay(3000);
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("A N A");
        
        
        // sound testing - Christmas Song :D
        // next step 1: find morse code for all letters
        // next step 2: find a way to play the morse code for each letter
        // next step 3: find a way to play the morse code for a word
        
        
        // the christmas song
        /*for (int i = 0; i < length; i++) {
              if (notes[i] == ' ') {
                delay(beats[i] * tempo); // rest
              } else {
                playNote(notes[i], beats[i] * tempo);
              }
              // pause between notes
              delay(tempo / 2); 
         }*/
        
        
         // tester for a line and dot sounds
         playLine();
         delay(1000);
         playDot();
         delay(1000);
         playDot();
         delay(1000);
         playLine();
         delay(1000);
         playLine();
         delay(1000);
      }
      
      if (buttonCounter == 2){
      	lcd.print("Test2");
      } 
      if (buttonCounter == 3){
      	lcd.print("Test3");
      } 
    }
    lastButtonState = buttonState;
  }
}
 