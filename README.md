# VituSat-1
VituSat-1 is a project based on ESA’s (European Space Agency) renowned design-build-launch space-related program – CanSat
## 1. Used Technologies
### Programming Languages:
- Arduino (Based on C)
- C++
### Programs and IDEs:
- gnuplot
- Arduino IDE
- Code::Blocks
### Hardware:
- Arduino T-Minus
- Accelerometer (x2)
- Pressure Sensor
- Temperature Sensor
- GPS Transmitter
- Micro SD Shield

## 2. Work Process, Problems, and Solutions
### Phase 1: Role Assignment and Work Process Planning 
During phase 1 we had to assign roles to everyone. I, alongside two other boys, choose 
to develop the satellite, because of our bigger experience with programming
compared to the other two boys, who decided to design and test the rocket module, 
because of their advanced Physics knowledge. Soon after we divided the roles among 
ourselves, we began to plan the work process. We, the satellite development team, 
decided to split the work by testing the sensors simultaneously, while the rocket design 
team decided not to divide the tasks, but work on one task at a time. 
 
### Phase 2: Sensors and Microcontroller Testing 
After we finished the planning phase, the real work began!
I began testing the accelerometers and the GPS, which later 
proved to be a hard work to do, especially when you haven’t 
soldered anything in your life :D
However, my teacher taught me how to work with a soldering 
iron by giving me a learning kit with capacitors, relays, resistors, 
etc. That also helped me learn more in-depth how electrical 
circuits work.
In the end, I managed to solder the pins of the sensors and test 
them successfully! 

### Phase 3: Satellite Assembly 
Even though this phase seemed to be the easiest, there were 
numerous difficulties we had to overcome. First, we 
experienced difficulties with the soldering of the sensors on the 
PCB (Printed Circuit Board), because of the uncommon 
connections between the pins on the board. That is why we had 
to unsolder, reposition, and solder the sensors once again.
Furthermore, we had problems with the assembly of the various parts of the code, 
because even though the sensors worked individually, the whole code resulted in 
memory overflow. That is why we had to optimize the code by replacing cumbersome 
raw-data converters with faster and less-memory-demanding ones.

### Phase 4: Radio Transceiver Connection and XY-plane Data  Representation 
The final phase of our project was to set up the data stream from the radio module on 
the satellite towards the ground station receiver, where our computer would receive 
the data, gathered by the satellite. Then, by using COMFile, we would archive the 
received information. After that, a C++ app, written by us, splits that data into separate 
files, which are then put into a gnuplot program, which illustrates the data from each 
file in an XY-plane.
The biggest problem we encountered during this phase is the processing of the 
corrupted data. We managed to overcome this difficulty by adding checkers in the C++ 
application.

## 3. Final Results
We managed to create a fully working CanSat satellite and a rocket, which could be 
launched in the lower atmosphere.
