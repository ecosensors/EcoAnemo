/*
* EcoSensors
* Library is distributed  WITHOUT WARRANTY
* 
*/

#include "Ecoanemo.h"
#include "Arduino.h"

void Ecoanemo::begin(){
  pinMode(_read_pin_wind_speed, INPUT_PULLUP);
  pinMode(_read_pin_wind_direction, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_read_pin_wind_speed), _isr_rotation, FALLING);
}

int Ecoanemo::get_windDirectionDegree(bool rounded)
{
  /* TODO - Developpemtn in progresss */
  int analogInput;
  int windDirection = 0;
  analogInput = analogRead(_read_pin_wind_direction);
  delay(10);
  analogInput = analogRead(_read_pin_wind_direction);        // Take twice the mesure is necessary

  if(_debug)
  {
    Serial.print(F("[DEBUG] analogInput: "));
    Serial.println(analogInput);
  }


  if (analogInput <= WDdirection[0])
  {      // Minimum value
    windDirection = WDdirection[0 + 1];
  }
  
  if (analogInput >= WDdirection[17])
  {     // Maximum value
    windDirection = WDdirection[17 + 1];
  }
  
  for (int i = 0; i < 18; i = i + 2)
  {
    if ((analogInput >= WDdirection[i]) && (analogInput <= WDdirection[i + 2]))
    {

      float numerateur = analogInput - WDdirection[i];
      float denominateur = WDdirection[i + 2] - WDdirection[i];
      windDirection = WDdirection[i + 1] - ((WDdirection[i + 1] - WDdirection[i + 3]) * (numerateur / denominateur));

      break;
    }
  }

  windDirection = windDirection + WindDirectionOffset;

  if (windDirection > 360){
    windDirection = windDirection - 360;
  }

  if(_debug)
  {
    Serial.print(F("[DEBUG] Wind Direction: "));
    Serial.print(windDirection);
    Serial.println(F("°"));
  }

  if(rounded)
  {
    if (windDirection < 22)
      windDirection = 0;          // N
    else if (windDirection < 67)
      windDirection = 45;         // NE
    else if (windDirection < 112)
      windDirection = 90;         // E
    else if (windDirection < 157)
      windDirection = 135;        // SE
    else if (windDirection < 202)
      windDirection = 180;        // S
    else if (windDirection < 247)
      windDirection = 225;        // SW
    else if (windDirection < 292)
      windDirection = 270;        // W
    else if (windDirection < 337)
      windDirection = 315;        // NW
    else
      windDirection = 360;
  
    if(_debug)
    {
      Serial.print(F("[DEBUG] Wind Direction rounded: "));
      Serial.print(windDirection);
      Serial.println(F("°"));
    }

  }

  return windDirection;

}

/* To be inproved */
void Ecoanemo::get_windDirectionCoord(int degree)
{
  if (degree < 22)
      Serial.println(F("N"));
    else if (degree < 67)
      Serial.println(F("NE"));
    else if (degree < 112)
      Serial.println(F("E"));
    else if (degree < 157)
      Serial.println(F("SE"));
    else if (degree < 202)
      Serial.println(F("S"));
    else if (degree < 247)
      Serial.println(F("SE"));
    else if (degree < 292)
      Serial.println(F("W"));
    else if (degree < 337)
      Serial.println(F("NW"));
    else
      Serial.println(F("N"));
}
  
unsigned long Ecoanemo::Rotations;
unsigned long Ecoanemo::ContactBounceTime;

float Ecoanemo::get_windspeed()
{
  /*
    // http://cactus.io/hookups/weather/anemometer/davis/hookup-arduino-to-davis-anemometer-wind-speed

    Using the formula V = P(2.25/T) we can calculate the speed in miles per hour.
    V is speed in miles per hour
    P is number of pulses per sample period
    T is the sample period in seconds

    Convert to mp/h using the formula V=P(2.25/T)
    V = P(2.25/T/1000) = P * 0.75 // assuming that T is egal to 3000ms but it must be in second
  */

  float windspeed;

  int T = 3000;                   // the sample period
  Rotations = 0;                  // Set Rotations count to 0 ready for calculations

  if(_debug){
    Serial.print(F("[DEBUG] "));
    Serial.print(T/1000);
    Serial.println(F("s. sample of period"));
  }

  delay(T);                       // Now it's waiting for intterupts (See _isr_rotation())

  if(_debug)
  {
    Serial.print(F("[DEBUG] Rotations: "));
    Serial.print(Rotations);
    Serial.print(F("\t"));
  }

  windspeed = Rotations * (2.25/(T/1000));   //MPH
  windspeed = windspeed * 1.609;      // Covert miles per hour to km/h

  if(_debug)
  {
    //Serial.print(F("[DEBUG] "));
    Serial.print(windspeed);
    Serial.println(F(" km/h"));
  }

  return windspeed;

}

/*
* This is the function that the interrupt calls to increment the rotation count
* (ISR for Interrupt Service Routine)
*/
void Ecoanemo::_isr_rotation(){
  if ((millis() - ContactBounceTime) > 15 ) { // debounce the switch contact.
    Rotations++;
    ContactBounceTime = millis();
  }
}


