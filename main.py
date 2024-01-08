import time
from rubiks import Cube
from communicatie import verstuurHussel, verstuurOplossing
from oplosser import geef_oplossing


# def get_hussel(hussel):
#     return hussel


cube = Cube(3)
hussel = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2" #llUddrFrllblUrrffbbdffllbbddll
cube.do_moves(hussel)
cube.print_cube()
print()
# verstuurHussel(hussel)
time.sleep(2)
oplossing = geef_oplossing(cube)
oplossing_inverted = oplossing[::-1]
print(oplossing_inverted)
print(oplossing, "VAN TEENSY")
invoer = input("Mag hij oplossen? y voor doorgaan.")
if invoer == "y":
    verstuurOplossing(oplossing)

invoer2 = input("Mag hij oplossing terug doen? y om door te gaan.")
if invoer == "y":
    verstuurOplossing(oplossing_inverted)