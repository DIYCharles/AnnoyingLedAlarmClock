
#include <DS3231.h>
#include <Wire.h>
#include <CuteBuzzerSounds.h>
DS3231 clock;
bool led_stop = false; //this is what is holding the value for the button press
bool snooze = false;
bool buzzerbool = false;
bool h12Flag;
bool pmFlag;
int ledpin = 13;
int buttonpin = 12;
//int buzzer = 11;//the pin of the active buzzer
#define BUZZER_PIN 11

void setup() {
  Wire.begin();
  Serial.begin(57600);
//  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
  pinMode(ledpin, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP); //set the button to work by shorting to ground. Open is high, closed is low. 
  digitalWrite(buttonpin, HIGH);  // turn on pullup resistor
  cute.init(BUZZER_PIN);
}

void loop() {
  int hr = clock.getHour(h12Flag, pmFlag); //get the current hour in 24hr format
  int dow = clock.getDoW();
  int p = 0;
  if (buzzerbool == true){
    cute.play(S_CONNECTION);
  }
  if (dow == 3 || dow == 5){
    if (hr <= 15 && hr >= 7){ //also if it is between 7am and 10am
    if (led_stop == 0){ //and the button is still in the false state do this.
      buzzerbool = true;
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      Serial.print("morning meds ");
    } else {
      digitalWrite(ledpin, LOW);
      buzzerbool = false;
    }
  } else {
    digitalWrite(ledpin, LOW);
    buzzerbool = false;
  }
  } else if (dow == 2 || dow == 4 || dow == 6){
    if (hr <= 15 && hr >= 7){ //also if it is between 7am and 10am
    if (led_stop == 0){ //and the button is still in the false state do this.
      buzzerbool = true;
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
      delay(50);
      digitalWrite(ledpin, HIGH);
      Serial.print("morning meds ");
    } else {
      digitalWrite(ledpin, LOW);
      buzzerbool = false;
    }
  } else {
    digitalWrite(ledpin, LOW);
    buzzerbool = false;
  }
    } 
  else {
    digitalWrite(ledpin, LOW);
    buzzerbool = false;
    }
  
  
  if (hr == 12){ //if it is 12 reset the button boolean 
    led_stop = 0;
    Serial.print("bool reset ");
  } else if (hr == 23){ //if it is 11pm reset the button boolean 
    led_stop = 0;
    Serial.print("bool reset ");
  }
  
  if (digitalRead(buttonpin) == LOW) { //read to see if the button has been pressed
    delay(25); //wait a sec so you're not just spamming the button with a single press
    led_stop = 1; //set the button boolean to true  
    Serial.print("ledstopped ");
    
    if (snooze == 0){
      cute.play(S_BUTTON_PUSHED);
      delay(5000);
      led_stop = 0;
      snooze = 1;
    } else {
      cute.play(S_CONNECTION);
      delay(50);
      cute.play(S_CONNECTION);
      delay(50);
      cute.play(S_DISCONNECTION);
      delay(50);
      cute.play(S_DISCONNECTION);
      led_stop = 1;
    }
    
    }
  Serial.print("\n hr \n");
     Serial.print(hr, DEC);
  Serial.print(" ");
  Serial.print("\n min \n");
  Serial.print(clock.getMinute(), DEC);
  
  Serial.print("\n dow \n");
  Serial.print(dow, DEC);
}
