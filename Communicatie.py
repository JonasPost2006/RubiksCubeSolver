#! D:\Jonas\Coderclass\CubeSolver\RubiksCubeSolver\venv\Scripts\python.exe

import serial
import time

port = 'COM10' #verander naar goede uitgang

ser = serial.Serial(port, 9600, timeout=1)



def write_read(data):
    ser.write(bytes(data, 'utf-8')) #Checken of dit 'user_input' stuurt of de echte input
    time.sleep(0.01) #?????
    incommingData = ser.readline()
    return incommingData

while True:
    value = input("Voer de oplossing in: ")
    oplossing = write_read(value)
    print(oplossing)