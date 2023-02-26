/*
* EcoSensors
* Library is distributed  WITHOUT WARRANTY
* 
*/

#include "Arduino.h"
#include "Ecoanemo.h"

Ecoanemo::Ecoanemo(int read_pin_wind_speed, bool debug)
{
  int _read_pin_wind_speed = read_pin_wind_speed;
  bool _debug = debug;
}

void Ecoanemo::begin(){
  pinMode(_read_pin_wind_speed, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_read_pin_wind_speed), _isr_rotation, FALLING);
}

int Ecoanemo::get_winddirection(int red_pin, bool debug)
{
  int analogInput;
  int windDirection;
  Serial.println(F("\r\nWind direction"));
  analogInput = analogRead(red_pin);
  analogInput = analogRead(red_pin);        // Take twice the mesure is necessary

  if(debug)
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
      windDirection = WDdirection[i + 1] - ((WDdirection[i + 1] - WDdirection[i + 3]) * ((analogInput - WDdirection[i]) / (WDdirection[i + 2] - WDdirection[i])));
                          
      //Serial.print("\t"); Serial.println(windDirection);
      break;
    }
  }

  if(debug)
  {
    Serial.print(F("[DEBUG] windDirection: "));
    Serial.print(windDirection);
    Serial.println(F("°"));
  }

  return windDirection = windDirection + WindDirectionOffset;

}


float Ecoanemo::get_windspeed(int red_pin, bool debug)
{
  float windspeed;
  int T = 3000;
  Rotations = 0;                  // Set Rotations count to 0 ready for calculations
  delay(T);                         // Now it's waiting for intterupts (See _isr_rotation())

  if(debug)
  {
    Serial.print(F("Rotations: "));
    Serial.print(Rotations);
    Serial.print(F("\t"));
  }
  /*
    // http://cactus.io/hookups/weather/anemometer/davis/hookup-arduino-to-davis-anemometer-wind-speed

    Using the formula V = P(2.25/T) we can calculate the speed in miles per hour.
    V is speed in miles per hour
    P is number of pulses per sample period
    T is the sample period in seconds

    Convert to mp/h using the formula V=P(2.25/T)
    V = P(2.25/T/1000) = P * 0.75 // assuming that T is egal to 3000ms but it must be in second
  */

  windspeed = Rotations * (2.25/(T/1000));   //MPH
  windspeed = windspeed * 1.609;      // Covert miles per hour to km/h

  if(debug)
  {
    Serial.print(windspeed);
    Serial.print(F(" km/h"));
  }

  return windspeed;
  

}

/*
* This is the function that the interrupt calls to increment the rotation count
* (ISR for Interrupt Service Routine)
*/

static void Ecoanemo::_isr_rotation(){
  
  //if ((millis() - ContactBounceTime) > 15 ) { // debounce the switch contact.
    //Rotations++;
    //ContactBounceTime = millis();
  //}

}


