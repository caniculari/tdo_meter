#!/usr/bin/python3
#:      Title   :   check_arduino_ac.py
#:      Date    :   13 ago 2015
#:      Author  :   Luis Enrique Pineda
#:      Version :   0.1
#:      Descrip :   Obtain working mode ac or dc and send alert if it's on ac
#:                 
from socket import timeout
from urllib.request import Request, urlopen
import urllib.error
import sys

target = Request('http://172.21.12.7')

try:
    response = urlopen(target, timeout = 6)

except urllib.error.URLError as e:
    if hasattr(e, 'reason'):
        print ('Failed to reach an arduino', e.reason)
        sys.exit(2)
    elif hasattr(e, 'code'):
        print ('The arduino couldn\' fulfill the request', e.code)
        sys.exit(2)
except timeout:
    print ('Response timeout')
    sys.exit(3)

else:
    html = response.read().decode('utf-8')
    volts_batt = html[html.find('bateria: ') + 9:html.find('mode')-5]
    mode = html[html.find('mode')-3]
    if mode == "A":
        print("Sistema en batería " + volts_batt + " V")
        sys.exit(0)
    elif mode == "r":
        print("Sistema en Corriente CFE")
        sys.exit(1)
    


