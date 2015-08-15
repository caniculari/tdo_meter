tdo_meter
==========
Medidor de energía en sistema UPS

Description
-------------
This is the program to monitor an instalation for mixed electrical energy source. The primary input is the solar energy system and in the backup mode it takes the energy form the line.

The arduino stuff
------------------
The arcuino has 3 sensors:
a) VCD sensor 0 is for the solar cells. It is conected to positive and negative terminal of solar cells. This system is intended for 12V installatiosns, for higher voltages will bi neccesary change the resistors and the calculation value ein the tdo_meter.ino value

b) VCD sensor 1 is for the batteries, also is the power source for the arduino

c) Sensor 3 is a relay for determine the power source. In my case is a 12 VCD relay conected to the output of the inverter to a simple 12VCD transformer , so if the inverter fails for any reason the relay will turn off

Teh arduino has the Ethernet shield to provide data for the monitoring system trough a simple web server in a one line web page.

The cacti stuff
---------------

I love graphs, so cacti reads the web page of the arduino to graph the voltage in the batteries and in the solar array. This is acomplished by the getVArduino_battery.py and getVArduino_solar.py files

The nagios stuff
-----------------

So I want to monitor if my system is working on solar energy or in power line. The nagios plugin send an alert when the system is working in power line mode. We are gled to use the solar energy as primary source. This task is done by the check_arduino_ac.py

TODO
----
* Merge the code o all py files to a simple parser for cacti and nagios

