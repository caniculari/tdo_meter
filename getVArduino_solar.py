#!/usr/bin/python3
#:      Title   :   getVArduino_solar.py
#:      Date    :   28 nov 2014
#:      Author  :   Luis Enrique Pineda
#:      Version :   0.3
#:      Descrip :   Get values from arduino for a cacti graph (solar cells)
#:                  file path /var/lib/cacti/scripts
from socket import timeout
from urllib.request import Request, urlopen
import urllib.error


target = Request('http://172.21.12.7')

try:
    response = urlopen(target, timeout = 6)

except urllib.error.URLError as e:
    if hasattr(e, 'reason'):
        print ('Failed to reach an arduino')
        print ('Reason: ', e.reason)
    elif hasattr(e, 'code'):
        print ('The arduino couldn\' fulfill the request')
        print ('Error code: ', e.code)
except timeout:
    print ('Response timeout')

else:
    html = response.read().decode('utf-8')

    volts_batt = html[40:html.find('solar')-7]
    volts_solar = html[html.find('lar') + 5:html.find('-')-1]

    #returnText = ("battery:%s:solar:%s" %(volts_batt.rstrip(),volts_solar.rstrip()))
    returnText = (volts_solar.rstrip())
    print(returnText)

