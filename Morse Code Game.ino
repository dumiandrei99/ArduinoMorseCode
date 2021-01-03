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
#include <time.h> 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 6;
const int speakerPin = 9;

int index = 0;
boolean buttonState = LOW;
boolean lastButtonState = LOW;
boolean firstTry = true;
boolean ultimateLevel = false;

char LevelOneWords[6][3] = {"A","E","I","M","N","T"};
char LevelTwoWords[8][3] = {"D","G","K","O","R","S","U","W"};
char LevelThreeWords[22][3] = {"B","C","F","H","J","L","P","Q","V","X","Y","Z","1","2","3","4","5","6","7","8","9","0"};

int FirstLevelSolutionsLength[6] = {2,1,2,2,2,1};
int SecondLevelSolutionsLength[8] = {3,3,3,3,3,3,3};
int ThirdLevelSolutionsLength[22] = {4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5};


char FirstLevelSolutions[6][5][6] = {{"dot\0","line\0"},{"dot\0"},{"dot\0","dot\0"},{"line\0","line\0"},{"line\0","dot\0"},{"line\0"}};
char SecondLevelSolutions[8][5][6] ={{"line\0","dot\0","dot\0"},{"line\0","line\0","dot\0"},{"line\0","dot\0","line\0"},{"line\0","line\0","line\0"},
                                      {"dot\0","line\0","dot\0"},{"dot\0","dot\0","dot\0"},{"dot\0","dot\0","line\0"},{"dot\0","line\0","line\0"}};

char ThirdLevelSolutions[22][5][6] = {{"line\0","dot\0","dot\0","dot\0"},{"line\0","dot\0","line\0","dot\0"},{"dot\0","dot\0","line\0","dot\0"},
  									  {"dot\0","dot\0","dot\0","dot\0"},{"dot\0","line\0","line\0","line\0"},{"dot\0","line\0","dot\0","dot\0"},
  									  {"dot\0","line\0","line\0","dot\0"},{"line\0","line\0","dot\0","line\0"},{"dot\0","dot\0","dot\0","line\0"},
  									  {"line\0","dot\0","dot\0","line\0"},{"line\0","dot\0","line\0","line\0"},{"line\0","line\0","dot\0","dot\0"},
									  {"dot\0","line\0","line\0","line\0","line\0"},{"dot\0","dot\0","line\0","line\0","line\0"},{"dot\0","dot\0","dot\0","line\0","line\0"},
									  {"dot\0","dot\0","dot\0","dot\0","line\0"}, {"dot\0","dot\0","dot\0","dot\0","dot\0"},{"line\0","dot\0","dot\0","dot\0","dot\0"},{"line\0","line\0","dot\0","dot\0","dot\0"},
									  {"line\0","line\0","line\0","dot\0","dot\0"}, {"line\0","line\0","line\0","line\0","dot\0"},{"line\0","line\0","line\0","line\0","line\0"}};

  									                                             


int ton = 2000;
long dotTimeUnit = 200;
long lineTimeUnit = dotTimeUnit * 3;
long prevMillis = 0;

int buttonCounter = 0;
int pressedCounter = 0;
long times[10];

int level = 1;
int score = 0;



  
int levelDecider(int scr){
	
  	if(scr < 6)
      return 1;
    
    if(scr >= 6 && scr < 14)
      return 2;
    
    if( scr >= 14 && scr < 30)
      return 3;
  	
  	if (scr >= 30){
  	 ultimateLevel = true;
  	 return random(1,4);
    }

}

void initializeGame(int lvl, int myScore){
  
  if(lvl == 1){
    
    //index remains the same if the player got the letter wrong, so he can retry
     if(firstTry == true)
        index = random(0,6);
      
     if (!ultimateLevel){
        // first thing we see on the screen after we press the button
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("LEVEL 1");
        lcd.setCursor(5,1);
        lcd.print("SCORE: ");
        lcd.setCursor(11,1);
        lcd.print(score);
     } 
     else{
     	lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("ULTIMATE LEVEL");
        lcd.setCursor(5,1);
        lcd.print("SCORE: ");
        lcd.setCursor(11,1);
        lcd.print(score);
     }
    
      // game starts
      delay(3000);
      lcd.clear();
      displayCharacter(LevelOneWords[index][0]);
      playCharacter(LevelOneWords[index][0],750);
  }
  
    if(lvl == 2){
      
      //index remains the same if the player got the letter wrong, so he can retry
      if(firstTry == true)
         index = random(0,8);
      
      if (!ultimateLevel){
        // first thing we see on the screen after we press the button
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("LEVEL 2");
        lcd.setCursor(5,1);
        lcd.print("SCORE: ");
        lcd.setCursor(11,1);
        lcd.print(score);
     }
     else{
     	lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("ULTIMATE LEVEL");
        lcd.setCursor(5,1);
        lcd.print("SCORE: ");
        lcd.setCursor(11,1);
        lcd.print(score);
     }
      
      // game starts
      delay(3000);
      lcd.clear();
      displayCharacter(LevelTwoWords[index][0]);
      playCharacter(LevelTwoWords[index][0],750);
  }
  
    if(lvl == 3){
      //index remains the same if the player got the letter wrong, so he can retry
      if(firstTry == true)
        index = random(0,22);
      
      if (!ultimateLevel){
        
          // first thing we see on the screen after we press the button
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("LEVEL 3");
          lcd.setCursor(5,1);
          lcd.print("SCORE: ");
          lcd.setCursor(11,1);
          lcd.print(score);
      }
      else{
     	  lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("ULTIMATE LEVEL");
          lcd.setCursor(5,1);
          lcd.print("SCORE: ");
          lcd.setCursor(11,1);
          lcd.print(score);
     }
      // game starts
      delay(3000);
      lcd.clear();
      displayCharacter(LevelThreeWords[index][0]);
      playCharacter(LevelThreeWords[index][0],750);
  }
	  	
}

void correct(){
  
  	if(firstTry == true){
      score += 2;
    }
    else{
      score += 1;
      firstTry = true;
    }
    
	lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CORRECT!");
    lcd.setCursor(5,1);
    lcd.print("SCORE: ");
    lcd.setCursor(11,1);
    lcd.print(score);
    pressedCounter = 0;
    buttonCounter = 0;
  
}

void wrong(){
  	if (firstTry == true){
                          	
        lcd.setCursor(0,1);
        lcd.print("B to retry");
        buttonCounter = 0;
        pressedCounter = 0;
        firstTry = false;
      
    }
    else{
      	delay(1000);
      	lcd.clear();
      	lcd.setCursor(3,0);
      	lcd.print("GAME OVER");
      	lcd.setCursor(5,1);
      	lcd.print("SCORE:");
      	lcd.setCursor(11,1);
      	lcd.print(score);
    }
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
  
}
  
void playLine(){
  playTone(ton, lineTimeUnit);
}

void playDot(){
  playTone(ton, dotTimeUnit);

}

// intervalele de timp au fost alese
// in urma testarilor facute
// rezultatele fiind urmarite in serial monitor


boolean checkLevelOneSolution(int solutionIndex, int sizeSolution){
  
  for(int i = 0 ; i < sizeSolution ; i++){
    
   	if(strstr(FirstLevelSolutions[solutionIndex][i],"dot") != NULL){
      if(checkDot(times[i]) == false){
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Wrong dot !");
         return false;
      }
    }
    
    if(strstr(FirstLevelSolutions[solutionIndex][i],"line") !=NULL){
        if(checkLine(times[i]) == false){
          	lcd.clear();
         	lcd.setCursor(0,0);
         	lcd.print("Wrong line !");
        	return false;
        }
    }
         
  }
  return true;
}

boolean checkLevelTwoSolution(int solutionIndex, int sizeSolution){
  
  for(int i = 0 ; i < sizeSolution ; i++){
    
   	if(strstr(SecondLevelSolutions[solutionIndex][i],"dot") != NULL){
      if(checkDot(times[i]) == false){
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Wrong dot !");
         return false;
      }
    }
    
    if(strstr(SecondLevelSolutions[solutionIndex][i],"line") !=NULL){
        if(checkLine(times[i]) == false){
          	lcd.clear();
         	lcd.setCursor(0,0);
         	lcd.print("Wrong line !");
        	return false;
        }
    }
         
  }
  return true;
}

boolean checkLevelThreeSolution(int solutionIndex, int sizeSolution){
  
  for(int i = 0 ; i < sizeSolution ; i++){
    
   	if(strstr(ThirdLevelSolutions[solutionIndex][i],"dot") != NULL){
      if(checkDot(times[i]) == false){
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Wrong dot !");
         return false;
      }
    }
    
    if(strstr(ThirdLevelSolutions[solutionIndex][i],"line") !=NULL){
        if(checkLine(times[i]) == false){
          	lcd.clear();
         	lcd.setCursor(0,0);
         	lcd.print("Wrong line !");
        	return false;
        }
    }
         
  }
  return true;
}

boolean checkLine(long time){
  
  if(time > 149 && time < 301){
    return true;
  }  
  return false;
}

boolean checkDot(long time){
  if(time > 19 && time < 101){
    return true;
  }
  return false;
}

void playCharacter(char character, int myDelay){
	
  if (character == 'A'){ // A: . -
    
    playDot();
    delay(myDelay);
    playLine();
    
  }
  
  else if (character == 'B'){// B: _ . . .
    
    playLine();
    delay(myDelay);
    playDot();
    delay(myDelay);
    playDot();
    delay(myDelay);
    playDot();
    
  }
  
  else if (character == 'C'){ // C: - . - .
    
    playLine();
    delay(myDelay);
    playDot();
    delay(myDelay);
    playLine();
    delay(myDelay);
    playDot();
    
  }
  
  else if (character == 'D'){ //D: - . .
    
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
   }
  
   else if (character == 'E'){ //E : .
    
     playDot();
   }
   else if (character == 'F'){ //F: . . _ .
   	
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
   }
  
   else if (character == 'G'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
   }
  
   else if (character == 'H'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
   }
  
   else if (character == 'I'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playDot();
     
   }
  
   else if (character == 'J'){ //G: _ _ .
    
      playDot();
      delay(myDelay);
      playLine();
      delay(myDelay);
      playLine();
      delay(myDelay);
      playLine();
   }
  
   else if (character == 'K'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
   }
  
   else if (character == 'L'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
   }
  
   else if (character == 'M'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playLine();
     
   }
  
   else if (character == 'N'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playDot();
     
   }
  
   else if (character == 'O'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
   }
  
   else if (character == 'P'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
     
   }
  
   else if (character == 'Q'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
   }
  
   else if (character == 'R'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
   }
  
   else if (character == 'S'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
   }
   else if (character == 'T'){ //G: _ _ .
    
     playLine();

   }
  
   else if (character == 'U'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
   }
  
   else if (character == 'V'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
   }
  
   else if (character == 'W'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
   }
  
   else if (character == 'X'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
   }
  
   else if (character == 'Y'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     
   }
   
   else if (character == 'Z'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
   }
  
   else if (character == '1'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
   	 playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     
   }
    
   else if (character == '2'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
   	 playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     
   }
    
   else if (character == '3'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
   	 playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     
   }
  
    
   else if (character == '4'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
   	 playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playLine();
     
   }
    
   else if (character == '5'){ //G: _ _ .
    
     playDot();
     delay(myDelay);
   	 playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     
   }
   else if (character == '6'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
   	 playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     
   }
  
   else if (character == '7'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
   	 playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     
   }
   else if (character == '8'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
   	 playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
     delay(myDelay);
     playDot();
     
   }
  
   else if (character == '9'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
   	 playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playDot();
     
   }
   else if (character == '0'){ //G: _ _ .
    
     playLine();
     delay(myDelay);
   	 playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     delay(myDelay);
     playLine();
     
   }
 
}

void displayCharacter(char character){
	lcd.setCursor(8,0);
    lcd.print(character);
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(buttonPin,INPUT);
  pinMode(speakerPin, OUTPUT);
  lcd.print("Morse Code Game");
  lcd.setCursor(0,1);
  lcd.print("Press B to Start");
}

void loop() {
  
  buttonState = digitalRead(buttonPin);
  unsigned long currentMillis = millis();
  
  
  if (buttonState != lastButtonState){
  	
    if(buttonState == HIGH && buttonCounter == 0){ // START THE GAME | CONTINUE GAME
    	buttonCounter ++; 
      	level = levelDecider(score);
      	initializeGame(level,score);

    }
    else if (buttonCounter >= 1){   
      unsigned long timePressed;
      
      if(buttonState == HIGH){

          buttonCounter ++; 
          tone(speakerPin,242);
          prevMillis = currentMillis;
          pressedCounter++;
   
      }
      else{
          noTone(speakerPin);
          if(buttonCounter > 1){
            timePressed = currentMillis - prevMillis;
            Serial.println(timePressed);
            
            
            if(level == 1){
              if(pressedCounter < FirstLevelSolutionsLength[index]){
             		times[pressedCounter - 1] = timePressed;     
          	  }
              else if (pressedCounter == FirstLevelSolutionsLength[index]){
                	times[pressedCounter - 1] = timePressed;
                	if(checkLevelOneSolution(index,FirstLevelSolutionsLength[index]) == true){
                		correct();
          			}
                	else{   
                      	wrong();
             	   }
           	 }
           }
           
           if(level == 2){
           		
             if(pressedCounter < SecondLevelSolutionsLength[index]){
               times[pressedCounter - 1] = timePressed;
             }
             else if (pressedCounter == SecondLevelSolutionsLength[index]){
             	times[pressedCounter - 1] = timePressed;
                if (checkLevelTwoSolution(index,SecondLevelSolutionsLength[index]) == true){
                 correct();
                }
                else{
                 wrong();
                }
             }
           }
            
            
            if(level == 3){
           		
             if(pressedCounter < ThirdLevelSolutionsLength[index]){
               times[pressedCounter - 1] = timePressed;
             }
             else if (pressedCounter == ThirdLevelSolutionsLength[index]){
             	times[pressedCounter - 1] = timePressed;
                if (checkLevelThreeSolution(index,ThirdLevelSolutionsLength[index]) == true){
                 correct();
                }
                else{
                 wrong();
                }
             }
           }          
             
         }
      }
    }
    lastButtonState = buttonState;
  }
}
 