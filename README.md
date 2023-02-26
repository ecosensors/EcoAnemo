# EcoAnemo

The library is actually under developpement

Library for the DEVIS anenomter and wind direction sensors is distributed WITHOUT WARRANTY.
(Référence: 6410 | [Documentation](assets/07395-277_IM_6410.pdf)) | [Documentation](assets/6410_SS.pdf))
![DEVIS anenomter](https://eco-sensors.ch/wp-content/uploads/2020/08/anemomter.jpg)

The library has been tested for the ATSAMD21G18 ARM Cortex M0 at 48Mhz board with 3V3 logic


## Wiring

Green 		=> Wind direction input (A1) 
Yellow		=> 3.3V
Black		=> Wind speed input (A0). Add a 4.7K (?? 20K ??)to the VCC
Red			=> GND

Wind Direction Translation: Variable resistance 0 - 20KΩ; 10KΩ = south, 180°
Wind Speed Translation Formula: 
1600 rev/hr = 1 mph
V = P(2.25/T) (V = speed in mph, P = no. of pulses per sample period, T = sample period in seconds)



## Calibration

Run your board and move the wind vane to the north (0°) and write down the analog value. Turn the wind vane to 45° (NE). Turn again the wind vane to 45° (E) and write down the anaog value and repeat the operation each 45°.

0° 		=> ... (N)
45° 	=> ... (NE)
90°		=> ... (E)
135°	=> ... (SE)
180°	=> ... (S)
225°	=> ... (SW)
270°	=> ... (W)
315°	=> ... (NW)
360°	=> ... (N)

Report the analog values to the first column of 'WDdirection[18]' in EcoAneno.h

In the example file, you can do the above steps in calibration.h file, specialy if you defined the analogReadResolution to 12. (I created calibration.h for my personal need)

## Offset
If the arm is not directed to the north, it must be corrected 'WindDirectionOffset' in EcoAneno.h to adjust
