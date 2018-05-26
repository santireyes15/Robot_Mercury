
"""
Created on Tue Oct 31 16:58:03 2017

@author: Santiago Reyes and Sebastian Sierra
"""
#
import serial
port="/dev/ttyACM0"
Arduino=serial.Serial(port,9600)
Arduino.flushInput()

def separar(data):
    if "Distancia" in data:
        label = data.split(":")
        dist = float(label[1])
        print "Distancia US: " + str(dist)

while True:
    opc = raw_input("Seleccione Opcion ")

    if(Arduino.inWaiting >0):

        if(opc == 'w' or opc == 'W'):
            Arduino.write('w')
        elif(opc == 's' or opc == 'S'):
            Arduino.write('s')
	    elif(opc == 'c' or opc == 'C'):
	        Arduino.write('c')
        elif(opc == 'a' or opc == 'A'):
            Arduino.write('a')
        elif(opc == 'd' or opc == 'D'):
            Arduino.write('d')
        elif(opc == 'o' or opc == 'O'):
            Arduino.write('o')
        elif(opc == 'p' or opc == 'P'):
            Arduino.write('p')
        elif(opc == 'r' or opc == 'R'):
            Arduino.write('r ')
        else:
            separar(Arduino.readline())
            Arduino.write('m')

Arduino.close()
