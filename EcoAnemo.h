
/*
* EcoSensors
* Library is distributed WITHOUT WARRANTY
* 
*/
#include <Arduino.h>

#ifndef Ecoanemo_h
#define Ecoanemo_h

class Ecoanemo{

	public:
		Ecoanemo(int WindSpeedPin, int WindDirectionPin, bool dbg=false): _read_pin_wind_speed(WindSpeedPin), _read_pin_wind_direction(WindDirectionPin), _debug(dbg) {};
        void begin();
        
        int WindDirectionOffset = 0;                    // 0 : the van is directed to the north

        int get_windDirectionDegree(bool rounded);
        void get_windDirectionCoord(int degree);
        float get_windspeed();
        int WDdirection[18] {
    		// Analog value, direction direction (° degre)
    		0,    0,    // N
    		500,  45,   // NE
    		943,  90,   // E 943
    		1350,  135,  // ES
    		1720,  180,  // S
    		2350,  225,  // SW
    		2800,  270,  // W
    		3300,  315,  // WN
    		4095,  360,  // N
  		}; 

    protected:
        static unsigned long Rotations;               // (ANENO) cup rotation counter used in interrupt routine
        static unsigned long ContactBounceTime;       // /ANENO) Timer to avoid contact bounce in interrupt
    
    private:
        bool _debug;
        int _read_pin_wind_speed;
        int _read_pin_wind_direction;
        static void _isr_rotation();
        // static unsigned long Rotations;         // (ANENO) cup rotation counter used in interrupt routine

 };
 #endif