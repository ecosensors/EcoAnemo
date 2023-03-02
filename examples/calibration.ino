#include <EcoAnemo.h>

const int analogResolution  = 12;       // 10 or 12
int analog_Resolution = 4095;           // 1023 (10) or 4095 (12)
  
/* Wind direction */
//int WDdirection[18];
const int pin_windDritection = 15;                  // (A1)


/* Wind speed */
const int pin_windSpeed = 14;                       // (A0)

Ecoanemo anemo(pin_windSpeed,pin_windDritection, true); // Last parameter: debug

void setup() {
/*
   * There is no need to define the pinMode for the wind speed and direction,
   * because the pinMode is defined in the library (Ecoanemo::begin())
   */
  Serial.begin(9600);
  anemo.begin();
  delay(8000);                                      // Wait for the terminal

  Serial.println(F("\r\n# Analog Reference"));
  analogReference(AR_DEFAULT);                      // 3.3V
  Serial.println(F("\r\n# Analog Resolution"));
  analogReadResolution(analogResolution);

  Serial.println(F("\r\n# Start"));
}

void loop() {
  Serial.println(F("\r\nWIND DIRECTION"));
  int degree = anemo.get_windDirectionDegree();
  anemo.get_windDirectionCoord(degree);

  Serial.println(F("\r\nWIND SPEED"));
  anemo.get_windspeed();

  delay(1000);

}