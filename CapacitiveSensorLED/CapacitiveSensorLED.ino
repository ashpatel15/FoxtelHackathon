#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
#define COMMON_PIN      4    // The common 'send' pin for all keys
#define CS(Y) CapacitiveSensor(COMMON_PIN, Y)
#define NUM_OF_SAMPLES  50   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   850  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     2    // Number of keys that are on the keyboard
CapacitiveSensor keys[] = {CS(3), CS(6)}; //, CS(4), CS(5), CS(6), CS(7), CS(8), CS(9), CS(10)


boolean onOff = false; 
boolean yes;
boolean previous = false;
int debounce = 1500;
long time = 0;

void setup()                    
{
for(int i=0; i<NUM_OF_KEYS; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
    pinMode(ledPin[i], OUTPUT);  
  }
   Serial.begin(9600);
    
}

void loop()                    
{
  for (int i = 0; i < NUM_OF_KEYS; ++i) {

    if (keys[i].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD){yes = true;}
    else {yes = false;}    
    // If the capacitance reading is greater than the threshold, play a note:
   

      if(i == 0){
         //This is is for LED PIN 13
         if(yes == true && previous  == false && millis() - time>debounce){
           //Put Send to Android in here 
//             if(state[i] == LOW){
//               state[i] = HIGH;
//             }
//             else 
//               state[i] = LOW;
               time = millis();                  
          }

      }else if (i == 1){
        //This is is for LED PIN 12
        if(yes == true && previous  == false && millis() - time>debounce){
           //Put Send to Android in here 
//           if(state[i] == LOW){
//             state[i] = HIGH;
//           }
//           else 
//             state[i] = LOW;
             time = millis();     
           
        }
      }

      previous = yes;

      Serial.println(millis()-time);
      delay(10);   
    }   
  }
  
     
