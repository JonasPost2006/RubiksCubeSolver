

import serial
import time
from oplosser import get_goede_move_vorm
from moveDecoder import hussel_naar_communicatie
from main import Cube
# import kociemba

port = 'COM10' #verander naar goede uitgang
ser = serial.Serial(port, 9600, timeout=1) #baudrate = 115200 voor snellere communicatie
# time.sleep(2)

# cubeStatus = "DRLUUBFBRBLURRLRUBLRDDFDLFUFUFFDBRDUBRUFLLFDDBFLUBLRBD"
# solution = kociemba.solve(cubeStatus)
# print("Solution: ", solution)

# def write_read(data):
#     ser.write(bytes(data, 'utf-8'))
#     time.sleep(1)
#     incommingdata = ser.readline()
#     return incommingdata

def write(goede_move_vorm = None):
    if goede_move_vorm is not None:
        ser.write(bytes(goede_move_vorm, 'utf-8'))
        time.sleep(1)

def write2(husseling = None):
    if husseling is not None:
        ser.write(bytes(husseling, 'utf-8'))
        time.sleep(1)

while True:
    # oplossing = geef_oplossing()
    # value = write_read(oplossing)
    cube = Cube(3)
    hussel_moves = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2" #hussel van cstimer.net
    cube.do_moves(hussel_moves)
    husseling = hussel_naar_communicatie(hussel_moves)
    value1 = write2(husseling)
    print(value1)
    
    goede_move_vorm = get_goede_move_vorm(cube)
    print(goede_move_vorm)
    value = write(goede_move_vorm)
    print(value)
    break
