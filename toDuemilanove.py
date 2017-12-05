import serial 
import time
import struct

ser = serial.Serial('/dev/ttyUSB0',9600)

ser.write(100)
print("%d",7000)
print( ser.readline())
ser.close()
