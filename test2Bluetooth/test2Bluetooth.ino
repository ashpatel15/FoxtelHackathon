#include <CapacitiveSensor.h>
 
int led = 13;
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Pins used for inputs and outputs********************************************************
const int analogInPin0 = A0;// Analog input pins
const int analogInPin1 = A1;
const int analogInPin2 = A2;
const int analogInPin3 = A3;
 
//Arrays for the 4 inputs**********************************************
float sensorValue[4] = {0,0,0,0};
float voltageValue[4] = {0,0,0,0};
 
//Char used for reading in Serial characters
char inbyte = '0';
float a = 0.0;
float b = 2.0;
float c = 3.0;
float d = 4.0;
//*******************************************************************************************
// CapSense Vars 
#define COMMON_PIN      2    // The common 'send' pin for all keys
#define CS(Y) CapacitiveSensor(COMMON_PIN, Y)
#define NUM_OF_SAMPLES  50   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   200  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     2    // Number of keys that are on the keyboard

int thresh []{200, 900};
CapacitiveSensor keys[] = { CS(3), CS(4)}; //, CS(4), CS(5), CS(6), CS(7), CS(8), CS(9), CS(10)
boolean onOff = false; 
boolean yes;
boolean previous = false;
int debounce = 1500;
long time = 0;
//*******************************************************************************************
// LED control
int ledPin[] = {6, 7}; 
int state[] = {LOW,LOW};
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 100;  // constants won't change :
boolean startBlink = false;
boolean startBlink2 = false;

void setup() {
  // initialise serial communications at 9600 bps:
  Serial.begin(9600);

  //Setting up of CapSense 
  for(int i=0; i<NUM_OF_KEYS; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);

    pinMode(ledPin[i], OUTPUT); 
    digitalWrite(ledPin[i], LOW); 
   
  }
  
}
 
void loop() {
//
//  Serial.print(keys[0].capacitiveSensor(NUM_OF_SAMPLES));
//  Serial.print(" ");
//  Serial.print(keys[1].capacitiveSensor(NUM_OF_SAMPLES));
//Serial.println();
// digitalWrite(ledPin[0], HIGH);
//  digitalWrite(ledPin[1], HIGH);

  
  for (int i = 0; i < NUM_OF_KEYS; ++i) {

    if (keys[i].capacitiveSensor(NUM_OF_SAMPLES) > thresh[i]){yes = true;}
    else {yes = false;}  

     
    // If the capacitance reading is greater than the threshold, play a note:
      if(i == 0){
         //This is is for LED PIN 6
         if(yes == true && previous  == false && millis() - time>debounce){
           //Put Send to Android in here
           
            sendAndroidValues(0); 
            time = millis();                     
          }

      }else if (i == 1){
        //This is is for LED PIN 7
        if(yes == true && previous  == false && millis() - time>debounce){
           //Put Send to Android in here 
           sendAndroidValues(1);

           time = millis();     
           
        }
      }

      
    } 
  
  previous = yes;
  
  //when serial values have been received this will be true
  if (Serial.available() > 0){
    inbyte = Serial.read();

    //Buy Main event
    if (inbyte == '0'){
      //LED off
      startBlink = false;
    }
    
    if (inbyte == '1'){
      //LED on
     startBlink = true;
    }

    if(inbyte == '2'){
      startBlink = false;
      digitalWrite(ledPin[0], HIGH);
    }

    if(inbyte == '6'){
      startBlink = false;
      digitalWrite(ledPin[0], LOW);
    }

    //Record program
    if (inbyte == '3'){
      //LED off
      startBlink2 = false;
    }
    
    if (inbyte == '4'){
      //LED on
     startBlink2 = true;
    }

    if(inbyte == '5'){
      startBlink2 = false;
      digitalWrite(ledPin[1], HIGH);
    }

    if(inbyte == '7'){
      startBlink2 = false;
      digitalWrite(ledPin[1], LOW);
    }

    if(inbyte == '8'){
      startBlink2 = false;
      digitalWrite(ledPin[0], LOW);
      digitalWrite(ledPin[1], LOW);
    }
  }




  //If API call success
  if(startBlink == true){
    makeBlink(0);
  }

  if(startBlink2 == true){
    makeBlink(1);
  }
 delay(10);   
  //delay by 2s. Meaning we will be sent values every 2s approx
  //also means that it can take up to 2 seconds to change LED state

}


void makeBlink (int pos){
   unsigned long currentMillis = millis();
    
     if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
    
        // if the LED is off turn it on and vice-versa:
        if (state[pos] == LOW) {
          state[pos] = HIGH;
        } else {
          state[pos] = LOW;
        }

    // set the LED with the ledState of the variable:
        digitalWrite(ledPin[pos], state[pos]);
      }
}
 
//sends the values from the sensor over serial to BT module
void sendAndroidValues(int btn)
 {
  //puts # before the values so our app knows what to do with the data
  Serial.print('#');
  Serial.print(btn);
  Serial.print('~'); //used as an end of transmission character - used in app for string length
  Serial.println();
  delay(10);        //added a delay to eliminate missed transmissions
}
