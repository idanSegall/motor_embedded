# leventech_step_motor
this software provides means of controlling step motor by GPIO usage in Linux based systems 

# Compile software
first download gcc and place at : /opt/toolchains/arm-2009q3/

then build by running "make"

# usage

stepMotor.o <step> <speed> <accel> <deaccel> <dir>
  
step: Number of pulses that will be sent
speed: Speed in usecond unit
accel and deaccel are usecond unit
dir: direction

# Authors

* Ilan Ganor
