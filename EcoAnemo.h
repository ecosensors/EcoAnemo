
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
        
        int get_winddirection();
        float get_windspeed();
        //int WDdirection[18];
        int WindDirectionOffset = 0;                    // 0 : the van is directed to the north
        int WDdirection[18] {
    		// Analog value, direction direction (° degre)
    		0,    0,    // N
    		200,  45,   // NE
    		416,  90,   // E
    		555,  135,  // ES
    		714,  180,  // S
    		892,  225,  // SW
    		1265,  270,  // W
    		1785,  315,  // WN
    		3200,  360,  // N
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