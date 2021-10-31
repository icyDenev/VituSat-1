set title "VituSat-1 mission data"
set multiplot layout 2,4 rowsfirst
plot "press.log" using 2:1 with lines title "Pressure"
plot "temp.log" using 2:1 with lines title "Temperature"
plot "gps.log" using 2:1 with lines title "Height"
plot "velo.log" using 2:1 with lines title "Velocity"
plot "accelX.log" using 2:1 with lines title 'X Axis'
plot "accelY.log" using 2:1 with lines title 'Y Axis'
plot "accelZ.log" using 2:1 with lines title 'Z Axis'
pause 1
reread