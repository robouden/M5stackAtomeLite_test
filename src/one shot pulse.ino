//One shot test

#include "M5Atom.h"


const int switchPin = 2;
const int output_pin = 33;
const int interruptPin2 = 2;
unsigned long previousMillis;
const unsigned long interval = 10000;
bool enabled = false;
bool pulsestart = false;

void setup()
{
  pinMode( switchPin, INPUT_PULLUP);
  pinMode( output_pin, OUTPUT);
  Serial.begin(9600);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), pulserISP, FALLING);
}

void loop()
{
  unsigned long currentMillis = micros();
  
  if(pulsestart)  
  {
    digitalWrite( output_pin, HIGH);  
    previousMillis = currentMillis;
    enabled = true;
 
    pulsestart = false;
  }
  
  
  if( enabled)      
  {
    if( currentMillis - previousMillis >= interval)
    {
      digitalWrite( output_pin, LOW);  
      enabled = false;     
    }
  }
}

void pulserISP ()

{
  pulsestart = true;
 
}