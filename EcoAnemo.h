
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
		Ecoanemo(int WindSpeedPin, bool dbg=false): _read_pin_wind_speed(WindSpeedPin), _debug(dbg) {};
        void begin();
        
                       
        //volatile unsigned long ContactBounceTime;       // /ANENO) Timer to avoid contact bounce in interrupt
        int get_winddirection(int read_pin);
        float get_windspeed();
        //int WDdirection[18];
        int WindDirectionOffset = 0;                    // 0 : the van is directed to the north
        int WDdirection[18] {
    		// Analog value, direction direction (° degre)
    		0,    0,    // N
    		270,  45,   // NE
    		561,  90,   // E
    		642,  135,  // ES
    		743,  180,  // S
    		814,  225,  // SW
    		870,  270,  // W
    		920,  315,  // WN
    		987,  360,  // N
  		}; 

    protected:
        // static unsigned long Rotations;         // (ANENO) cup rotation counter used in interrupt routine
        
    private:
        bool _debug;
        int _read_pin_wind_speed;
        static void _isr_rotation();
        static unsigned long Rotations;         // (ANENO) cup rotation counter used in interrupt routine

 };
 #endif