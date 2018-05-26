# -*- coding: utf-8 -*-
"""
Created on Tue Apr 24 23:17:17 2018

@author: Santiago Reyes and Sebastian Sierra
"""

import os, socket, fcntl, smtplib, struct, time, serial

port="/dev/ttyACM0"
Arduino=serial.Serial(port,9600)
Arduino.flushInput()
response = 0
def getIpAddress(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(s.fileno(),0x8915,struct.pack('256s', ifname[:15]))[20:24])

def check_ping(hostname):
	response = os.system("ping -c 1 " + hostname)
# and then check the response...
	if response == 0:
		pingstatus = "Network Active"
	else:
		pingstatus = "Network Error"
	return pingstatus


if __name__ == "__main__":
    #if1 = 'eth0'
    if1 = 'wlan0'
    #myIp = '192.168.1.106'
    myIp = getIpAddress(if1)
    while (True):
        pingstatus = check_ping(myIp)
        if pingstatus == "Network Error":
             Arduino.write('r')
             print "Entro"
        if pingstatus == "Network Active":
             Arduino.write('p')
             print "No entro"
	print pingstatus
