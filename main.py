import time
from rubiks import Cube
from communicatie import verstuurHussel, verstuurOplossing
from oplosser import geef_oplossing


# def get_hussel(hussel):
#     return hussel


cube = Cube(3)
hussel = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2"
cube.do_moves(hussel)
cube.print_cube()
print()
verstuurHussel(hussel)
# time.sleep(2)
oplossing = geef_oplossing(cube)
print(oplossing)
verstuurOplossing(oplossing)