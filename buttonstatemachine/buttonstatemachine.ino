/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int TIMEOUT_PERIOD = 1000; // ms

// variables will change:
bool buttonState = false;         // variable for reading the pushbutton status
bool timeout = false;
bool ledState = false;
unsigned long now;
unsigned long timerStart;

enum State {OFF, ON, FLASH};
State state = OFF;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  now = millis();
  timerStart = now;
}

void checkButton() {
  // read the state of the pushbutton value:
  buttonState = !digitalRead(buttonPin);  
}

void checkTimer() {
  if(now - timerStart >= TIMEOUT_PERIOD) {
    timeout = true;
    timerStart = now;
  }
  else {
    timeout = false;
  }
}

void displayLED() {
  digitalWrite(ledPin, ledState);
}

void loop() {
  now = millis();
  checkButton();
  checkTimer();

  switch(state) {
    case OFF:
      if(buttonState){
        ledState = false;
        state = ON;
      }
      break;
    case ON:
      if(buttonState){
        ledState = true;
        state = FLASH;
      }
      break;
    case FLASH:
      if(timeout){
        ledState = !ledState;
        state = FLASH;
      }
      if(buttonState){
        state = OFF;
      }
      break;
  }

  timeout = false;
  buttonState = false;
  displayLED();
}






