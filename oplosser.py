from typing import List
from copy import deepcopy
import time

from main import Cube
from move import Move
from movesGedaan import movesGedaan
from colour import WHITE, GREEN, ORANGE, BLUE, RED, YELLOW, COLOUR_NAMES
from moveDecoder import hussel_naar_moves, moves_naar_hussel, moves_naar_communicatie

def geef_oplossing(cube: Cube) -> List[Move]:
    kopie_cube = movesGedaan(cube.size, deepcopy(cube.faces)) #Belangrijk om een kopie van de status van de cube te maken, zodat deze niet wordt verandert tijdens het zoeken naar de oplossing
    
    witte_kruis(kopie_cube)

    def print_cube(self):
        unfolded_order = [("U", (0, 1)), ("L", (1, 0)), ("F", (1, 1)), ("R", (1, 2)), ("B", (1, 3)), ("D", (2, 1))]
        
        unfolded_cube = [["     " for _ in range(12)] for _ in range(9)]

        for face, (row_offset, col_offset) in unfolded_order:
            face_content = self.faces[face]
            for row in range(self.size):
                for col in range(self.size):
                    unfolded_row = row + row_offset * self.size
                    unfolded_col = col + col_offset * self.size
                    unfolded_cube[unfolded_row][unfolded_col] = f"[{COLOUR_NAMES[face_content[row][col]]}]"

        for row in unfolded_cube:
            print(" ".join(row))
    kopie_cube.print_cube()
    blatest = kopie_cube.movesGedaan
    print("Oplossing: ", blatest)
    print("Husselvorm: ", moves_naar_hussel(blatest))
    goede_move_vorm = moves_naar_communicatie(blatest).lower()
    print("Husselvorm: ", goede_move_vorm)

def get_goede_move_vorm(cube: Cube) -> str:
    kopie_cube = movesGedaan(cube.size, deepcopy(cube.faces))
    witte_kruis(kopie_cube)

    kopie_cube.print_cube()
    blatest = kopie_cube.movesGedaan
    goede_move_vorm = moves_naar_communicatie(blatest).lower()
    print(goede_move_vorm)
    
    return goede_move_vorm

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

cube = Cube(3)
hussel_moves = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2" #hussel van cstimer.net
cube.do_moves(hussel_moves)
cube.print_cube()
print()
print()

start = time.time()
geef_oplossing(cube)
end = time.time()
print(end - start)

