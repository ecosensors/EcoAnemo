# EcoAnemo

The library is actually under developpement

Arduino library for the DEVIS anenomter and wind direction sensors is distributed WITHOUT WARRANTY.
The library has been tested for the ATSAMD21G18 ARM Cortex M0 at 48Mhz board with 3V3 logic.

Sensor reference: 6410 | [Documentation](assets/07395-277_IM_6410.pdf) | [Spec sheet](assets/6410_SS.pdf)

![DEVIS anenomter](assets/station-meteo.jpg)

## Wiring

Wire | I/O
--- | ---
Green | Wind direction input (A1) 
Yellow | 3.3V
Black | Wind speed input (A0). Add a 4.7K (?? 20K ??)to the VCC
Red | GND

Wind Direction Translation: Variable resistance 0 - 20KΩ; 10KΩ = south, 180°

Wind Speed Translation Formula: 1600 rev/hr = 1 mph
V = P(2.25/T) (V = speed in mph, P = no. of pulses per sample period, T = sample period in seconds)


## How to use it
Connect the Davis Anemometer to your board

### Calibration
You should better make sure that the analog values returned by the vane (Wind direction) match to the cardinal directions. For the purpose, open the example file named calibration.ino and process to the following steps

1. Make sure that the variable [WindDirectionOffset](https://github.com/ecosensors/EcoAnemo/blob/main/EcoAnemo.h#L18) is with the value 0
2. Turn the vane at the same direction than the arm (metal point in the front)
3. turn the vane and at each 45°, write down the analog values to the array [WDdirection](https://github.com/ecosensors/EcoAnemo/blob/main/EcoAnemo.h#L23)


Analog value | Degre (Direction)
--- | ---
...	| 0° (N)
... | 45° (NE)
...	| 90° (E)
... | 135° (SE)
... | 180° (S)
... | 225° (SW)
... | 270° (W)
... | 315° (NW)
... | 360° (N)


### Offset
Fix the anemometer and orient the arm to the North. In that case, the variable 'WindDirectionOffset' must be egal to 0.
If the arm is not oriented to the north, you have to modify 'WindDirectionOffset' in EcoAneno.h to. Expl: If the arm is oriented to the Est, the 'WindDirectionOffset' has to be changed to 90.

## Version
[26.2.2023] v.1
