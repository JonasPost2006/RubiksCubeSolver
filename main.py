import time
from rubiks import Cube
from communicatie import verstuurHussel, verstuurMoves
from oplosser import geef_oplossing
from moveDecoder import hussel_naar_moves, moves_naar_communicatie, inverted_moves


# def get_hussel(hussel):
#     return hussel


cube = Cube(3)
# hussel = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2" #llUddrFrllblUrrffbbdffllbbddll
# hussel = "D' R' F R' U' L' D2 R' F' D2 B R2 F' D2 B2 R2 B R2"
hussel_moves = input("Wat is de hussel? Voer in: ")

cube.do_moves(hussel_moves)
hussel_moves_pc = hussel_naar_moves(hussel_moves)
communicatie_moves_hussel = moves_naar_communicatie(hussel_moves_pc)
verstuurMoves(communicatie_moves_hussel)
cube.print_cube()
print()
# time.sleep(2)
oplossing_com, oplossing_moves = geef_oplossing(cube)
oplossing_inverted = inverted_moves(oplossing_moves)
print(oplossing_inverted)
oplossing_inverted_com = moves_naar_communicatie(oplossing_inverted)
print(oplossing_inverted_com)
# oplossing_inverted = oplossing[::-1]
# print(oplossing_inverted)
print(oplossing_com, "VAN TEENSY")
invoer = input("Mag hij oplossen? y voor doorgaan.")
if invoer == "y":
    verstuurMoves(oplossing_com)

# invoer2 = input("Mag hij oplossing terug doen? y om door te gaan.")
# if invoer == "y":
#     verstuurMoves(oplossing_inverted_com)