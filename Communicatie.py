
import sys
import serial
import time
from moveDecoder import hussel_naar_moves
# import kociemba

port = 'COM10' #verander naar goede uitgang
ser = serial.Serial(port, 9600, timeout=1) #baudrate = 115200 voor snellere communicatie
# time.sleep(2)


# def write_read(data):
#     ser.write(bytes(data, 'utf-8'))
#     time.sleep(1)
#     incommingdata = ser.readline()
#     return incommingdata

# def writeHussel(husseling = None):
#     if husseling is not None:
#         ser.write(bytes(husseling, 'utf-8'))
#         time.sleep(1)

# def writeOplossing(goede_move_vorm = None):
#     if goede_move_vorm is not None:
#         ser.write(bytes(goede_move_vorm, 'utf-8'))
#         time.sleep(1)

def verstuurHussel(hussel):
    # cube.do_moves(hussel)
    hussel_in_movevorm = hussel_naar_moves(hussel)
    if hussel_in_movevorm is not None:
        ser.write(bytes(hussel_in_movevorm, 'utf-8'))
        print(hussel_in_movevorm)
        time.sleep(1)

def verstuurMoves(goede_move_vorm = None):
    if goede_move_vorm is not None:
        ser.write(bytes(goede_move_vorm, 'utf-8'))
        print("Oplossing verstuurd: ")
        print(goede_move_vorm)
        time.sleep(1)
        data = ser.readline()
        if data:
            return data
        
        




# while True:
#     # oplossing = geef_oplossing()
#     # value = write_read(oplossing)
#     cube = Cube(3)
#     hussel_moves = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2" #hussel van cstimer.net
#     cube.do_moves(hussel_moves)
#     husseling = hussel_naar_communicatie(hussel_moves)
#     value1 = writeHussel(husseling)
#     print(value1)
    
#     goede_move_vorm = get_goede_move_vorm(cube)
#     print(goede_move_vorm)
#     value = writeOplossing(goede_move_vorm)
#     print(value)
#     break
