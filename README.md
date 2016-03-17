# Arduino Drone Project

The code is divided in 4 parts:

* *Time*: controls the interval of time between the calculations, in order to avoid unnecessary waste of resources

* *Inputs*: gets the input from all the sources: accelerometer, gyroscope, distance, remote control, etc

* *Calculations*: uses the previous information to track position, velocity, and prepares the values for the output

* *Outputs*: sends the output information to the motors an other devices, if needed (screen, computer, etc)
