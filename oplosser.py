from typing import List
from copy import deepcopy
import time

from rubiks import Cube
from move import Move
from movesGedaan import movesGedaan
from colour import WHITE, GREEN, ORANGE, BLUE, RED, YELLOW, COLOUR_NAMES
from moveDecoder import hussel_naar_moves, moves_naar_hussel, moves_naar_communicatie, inverted_moves

# def geef_oplossing(cube: Cube) -> List[Move]:
#     kopie_cube = movesGedaan(cube.size, deepcopy(cube.faces)) #Belangrijk om een kopie van de status van de cube te maken, zodat deze niet wordt verandert tijdens het zoeken naar de oplossing
    
#     witte_kruis(kopie_cube)

#     def print_cube(self):
#         unfolded_order = [("U", (0, 1)), ("L", (1, 0)), ("F", (1, 1)), ("R", (1, 2)), ("B", (1, 3)), ("D", (2, 1))]
        
#         unfolded_cube = [["     " for _ in range(12)] for _ in range(9)]

#         for face, (row_offset, col_offset) in unfolded_order:
#             face_content = self.faces[face]
#             for row in range(self.size):
#                 for col in range(self.size):
#                     unfolded_row = row + row_offset * self.size
#                     unfolded_col = col + col_offset * self.size
#                     unfolded_cube[unfolded_row][unfolded_col] = f"[{COLOUR_NAMES[face_content[row][col]]}]"

#         for row in unfolded_cube:
#             print(" ".join(row))
#     kopie_cube.print_cube()
#     # blatest = kopie_cube.movesGedaan
#     # print("Oplossing: ", blatest)
#     # print("Husselvorm: ", moves_naar_hussel(blatest))
#     # goede_move_vorm = moves_naar_communicatie(blatest).lower()
#     # print("Husselvorm: ", goede_move_vorm)

def geef_oplossing(cube: Cube) -> List[Move]:
    kopie_cube = movesGedaan(cube.size, deepcopy(cube.faces))
    # kopie_cube.print_cube()
    witte_kruis(kopie_cube)
    witte_hoekjes(kopie_cube)
    middelste_laag(kopie_cube)
    OLL1(kopie_cube)

    print()
    print()
    kopie_cube.print_cube()
    moves = kopie_cube.movesGedaan
    # print("HIER", moves)
    print(moves_naar_hussel(moves))
    moves_in_goede_move_vorm = moves_naar_communicatie(moves)#.lower()
    print(moves_in_goede_move_vorm)
    aantal_moves = len(moves_in_goede_move_vorm)
    print(aantal_moves)
    
    return moves_in_goede_move_vorm, moves

def witte_kruis(cube: movesGedaan):
    EDGE_PIECES = {
        "UF": "",
        "UL": "U'",
        "UR": "U",
        "UB": "U2",
        "LB": "L U' L'",
        "LD": "L2 U'",      #Hier moet je geen L' F doen. Hierdoor krijg je het probleem dat je een edge piece die goed zat, veranderd van positie.
        "LF": "L' U' L",
        "RB": "R' U R",
        "RD": "R2 U",
        "RF": "R U R'",
        "DB": "B2 U2",
        "DF": "F2"
    }

    for colour in [GREEN, RED, BLUE, ORANGE]:
        for edge in EDGE_PIECES:
            current_edge = tuple(cube.get_edge(edge).values()) #Krijg de RGB waardes van de edge

            if current_edge in [(colour, WHITE), (WHITE, colour)]: #Als deze edge een edge is van het witte kruis, worden de moves gedaan om hem naar upfront te krijgen
                cube.do_moves(EDGE_PIECES[edge])

                if cube.get_edge("UF")["U"] == WHITE: #Als de bovenste sticker van de piece op UF wit is dan F2, zo zit hij op de goede plek
                    cube.do_moves("F2")
                else:                                 #Anders R U' R' F om piece op juiste positie te krijgen
                    cube.do_moves("R U' R' F")
                
                cube.do_moves("D")
                break
    # cube.do_moves("D2")

def witte_hoekjes(cube:Cube):
    HOEKJES = {
        "UFR": "",
        "UBR": "U",
        "UBL": "U2",
        "UFL": "U'",
        "DFR": "R U R' U'",
        "DBR": "R' U R U",
        "DBL": "L U2 L'", #"L U L' U"
        "DFL": "L' U' L", 
    }

    for kleur1, kleur2 in [(GREEN, ORANGE), (ORANGE, BLUE), (BLUE, RED), (RED, GREEN)]:
        for hoekje in HOEKJES:
            current_corner = cube.get_corner(hoekje).values()

            if kleur1 in current_corner and kleur2 in current_corner and WHITE in current_corner:
                cube.do_moves(HOEKJES[hoekje])

                if cube.get_sticker("UFR") == WHITE:
                    moves = "U R U2 R' U R U' R'"
                elif cube.get_sticker("FUR") == WHITE:
                    moves = "U R U' R'"
                else:
                    moves = "R U R'"
                
                cube.do_moves(moves)
                cube.do_moves("D'")
                break

def middelste_laag(cube:Cube):
    EDGE_PIECES = {
        "UF": "",
        "UL": "U'",
        "UR": "U",
        "UB": "U2",
        "LB": "L U' L' B L' B' L",
        "LF": "L F' L' F L' U' L U",
        "RB": "R' U R B' R B R'",
        "RF": "R' F R F' R U R' U'"
    }

    for kleur1, kleur2 in [(GREEN, ORANGE), (ORANGE, BLUE), (BLUE, RED), (RED, GREEN)]:
        for edge in EDGE_PIECES:
            current_edge = tuple(cube.get_edge(edge).values())

            # if kleur1 in current_edge and kleur2 in current_edge:
            if current_edge == (kleur1, kleur2) or current_edge == (kleur2, kleur1):
                cube.do_moves(EDGE_PIECES[edge])
                
                if cube.get_sticker("UF") == kleur1:
                    moves = "U2 R' F R F' R U R'"
                else:
                    moves = "U R U' R' F R' F' R"
                cube.do_moves(moves)
                cube.do_moves("y") #Draai cube naar links
                break

#2-look OLL (Bron: https://jperm.net/3x3/cfop)
#Stap 1
def OLL1(cube:Cube):
    for _ in range(4):
        bovenste_laag = [cube.get_sticker("UL"), cube.get_sticker("UB"), cube.get_sticker("UR"), cube.get_sticker("UF")]
        status_bovenste_laag = [face == YELLOW for face in bovenste_laag]

        if status_bovenste_laag == [True, True, False, False]: #Hoekje linksboven
            cube.do_moves("F U R U' R' F'")
            break
        if status_bovenste_laag == [True, False, True, False]:
            cube.do_moves("F R U R' U' F'") #Horizontale lijn
            break
        if  status_bovenste_laag == [False, False, False, False]:#F R U R' U' F' U2 F U R U' R' F'
            cube.do_moves("R U2 R2 F R F' U2 R' F R F'") #Checken of deze altijd werkt
            break
        else:
            cube.do_moves("U")
        
             


cube = Cube(3)
hussel_moves = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2" #hussel van cstimer.net
cube.do_moves(hussel_moves)
# inverted_hussel = inverted_moves(hussel_naar_moves(hussel_moves))
# print(inverted_hussel, "HIEEERRRR")
# inverted_hussel_com = moves_naar_communicatie(inverted_hussel)
# print(inverted_hussel_com)

# cube.print_cube()
print()
print()

# # start = time.time()
geef_oplossing(cube)
# end = time.time()
# print(end - start)

