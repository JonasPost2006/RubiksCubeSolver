#! D:\Coderclass\RubiksCubeSolver\RubiksCubeSolver\venv\Scripts\python.exe

import serial
import time

port = 'COM3' #verander naar goede uitgang

ser = serial.Serial(port, 9600, timeout=1)

def rotate_stepper():
    ser.write(b'user_input') #Checken of dit 'user_input' stuurt of de echte input
    time.sleep(2) #?????

user_input = input("Geef input")
if user_input == True:
    rotate_stepper()

ser.close()