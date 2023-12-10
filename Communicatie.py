

import serial
import time
# import kociemba

port = 'COM3' #verander naar goede uitgang
ser = serial.Serial(port, 9600, timeout=1) #baudrate = 115200 voor snellere communicatie
# time.sleep(2)

# cubeStatus = "DRLUUBFBRBLURRLRUBLRDDFDLFUFUFFDBRDUBRUFLLFDDBFLUBLRBD"
# solution = kociemba.solve(cubeStatus)
# print("Solution: ", solution)

def write_read(data):
    ser.write(bytes(data, 'utf-8'))
    time.sleep(1)
    incommingdata = ser.readline()
    return incommingdata

while True:
    oplossing = input("Voer oplossing in: ")
    value = write_read(oplossing)
    print(value)
