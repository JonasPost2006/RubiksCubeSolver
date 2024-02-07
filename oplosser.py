from typing import List
from copy import deepcopy
import time

from rubiks import Cube
from move import Move
from movesGedaan import movesGedaan
from colour import WHITE, GREEN, ORANGE, BLUE, RED, YELLOW, COLOUR_NAMES
from moveDecoder import hussel_naar_moves, moves_naar_hussel, moves_naar_communicatie, inverted_moves, onnodig_weghalen


def geef_oplossing(cube: Cube) -> List[Move]:
    kopie_cube = movesGedaan(cube.size, deepcopy(cube.zijdes))
    print("Status na hussel: ")
    kopie_cube.print_cube()
    start = time.time()

    # kopie_cube.print_cube()
    witte_kruis(kopie_cube)
    witte_hoekjes(kopie_cube)
    middelste_laag(kopie_cube)
    OLL1(kopie_cube)
    OLL2(kopie_cube, True)
    PLL1(kopie_cube, True)
    PLL2(kopie_cube)

    end = time.time()
    tijd_gekost = (end - start) * 1000
    moves = kopie_cube.movesGedaan
    moves_in_goede_move_vorm = moves_naar_communicatie(moves)
    aantal_moves = len(moves_in_goede_move_vorm)
    
    print("\nOpgelost:")
    kopie_cube.print_cube()
    print()
    print("Moves:", moves_naar_hussel(moves))
    print("Moves voor communicatie:", moves_in_goede_move_vorm)
    print("Aantal moves:", aantal_moves)
    print("Opgelost in", int(tijd_gekost), "miliseconden!")
    
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

def witte_hoekjes(cube:Cube):
    HOEKJES = {
        "UFR": "",
        "URB": "U",
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
        status_bovenste_laag = [zijde == YELLOW for zijde in bovenste_laag]

        if status_bovenste_laag == [True, True, False, False]: #Hoekje linksboven
            cube.do_moves("F U R U' R' F'")
            break
        if status_bovenste_laag == [True, False, True, False]:
            cube.do_moves("F R U R' U' F'") #Horizontale lijn
            break
        if  status_bovenste_laag == [False, False, False, False]:#F R U R' U' F' U2 F U R U' R' F'
            cube.do_moves("R U2 R2 F R F' U2 R' F R F'")
            break
        else:
            cube.do_moves("U")

def OLL2(cube:Cube, printen):
    VORM_GELE_VLAK = {         #https://jperm.net/algs/2look/oll
        "vis_links": "L' U' L U' L' U2 L",
        "vis_rechts": "R U R' U R U2 R'",
        "dubbele_vis": "R' F R B' R' F' R B",
        "kruis_headlights": "F R U R' U' R U R' U' R U R' U' F'",
        "kruis_zijkant": "U R U2 R2 U' R2 U' R2 U2 R", #U R U2 R2 U' R2 U' R2 U2 R
        "hamer_headlights": "R2 D R' U2 R D' R' U2 R'",
        "hamer_zijkant": "U L F R' F' L' F R F'",
        "Headlights": "R2 D' R U2 R' D R U2 R",
        "Sidebars": "U' L F R' F' L' F R F'"
    }

    def bovenste_laag_hoekjes(cube: Cube):
        return [cube.get_sticker("UBL"), cube.get_sticker("UBR"), cube.get_sticker("UFR"), cube.get_sticker("UFL")]
    
    def status_bovenste_laag_hoekjes(top_layer):
        return [zijde == YELLOW for zijde in top_layer]
    
    for _ in range(4):
        hoekjes = status_bovenste_laag_hoekjes(bovenste_laag_hoekjes(cube))
        # print("Hier: ")

        if hoekjes == [False, False, False, True]:
            # print(cube.get_sticker("LUF"))
            if cube.get_sticker("FRU") == YELLOW:
                cube.do_moves(VORM_GELE_VLAK["vis_rechts"])
                if printen == True:
                    print("Vis rechts")
            else:
                cube.do_moves(VORM_GELE_VLAK["vis_links"])
                if printen == True:
                    print("Vis rechts")
            break

        elif hoekjes == [True, False, True, False]:
            if cube.get_sticker("LUF") == YELLOW:
                cube.do_moves(VORM_GELE_VLAK["dubbele_vis"])
                if printen == True:
                    print("Dubbele vis")
            else:
                cube.do_moves("U2")
                cube.do_moves(VORM_GELE_VLAK["dubbele_vis"])
                if printen == True:
                    print("Dubbele vis")
            break

        elif hoekjes == [False, False, False, False]:
            # print(cube.get_sticker("FUR"))
            # print(cube.get_sticker("FUL"))
            while cube.get_sticker("FUR") != YELLOW or cube.get_sticker("LUF") != YELLOW:
                cube.do_moves("U")

            if cube.get_corner("UFR")["F"] == cube.get_corner("UBL")["B"]:
                cube.do_moves(VORM_GELE_VLAK["kruis_headlights"])
                if printen == True:
                    print("Kruis headlights")
            else:
                # cube.do_moves("U")  #HIER WAS EERST EEN bugg doordat het algoritme wat wij kennen niet in deze positie uitgevoerd kon worden, maar eerst een U nodig was. Deze is aan het algoritme toegevoegd
                cube.do_moves(VORM_GELE_VLAK["kruis_zijkant"])
                if printen == True:
                    print("Kruis zijkant")
            break

        # elif hoekjes == [True, True, False, False]:
        elif hoekjes == [False, False, True, True]:
            # print(cube.get_sticker("BRU"))
            if cube.get_sticker("BRU") == YELLOW:
                cube.do_moves(VORM_GELE_VLAK["Headlights"])
            else:
                cube.do_moves(VORM_GELE_VLAK["Sidebars"])
            break

        else:
            cube.do_moves("U")

def PLL1(cube:Cube, printen):    #https://jperm.net/algs/2lookpll
    for _ in range(4):
        print("")
        cube.print_cube()
        if cube.get_sticker("FUR") == cube.get_sticker("LUF") and cube.get_sticker("BLU") == cube.get_sticker("BRU"):
            break
        
        if cube.get_sticker("FUR") == cube.get_sticker("LUF"):
            cube.do_moves("U R U R' U' R' F R2 U' R' U' R U R' F'")
            if printen == True:
                    print("PLL1 Diagonaal")
                    cube.print_cube()
            break
        
        cube.do_moves("U")
    
    else:
        cube.do_moves("F R U' R' U' R U R' F' R U R' U' R' F R F'")
        if printen == True:
                    print("PLL1 Headlights")

# def PLL12(cube:Cube, printen):
#     alg = "R' U L' U2 R U' R' U2 R L "

#     for _ in range(4):
#         if cube.get_sticker("FUR") == cube.get_sticker("FUL") and cube.get_sticker("BLU") == cube.get_sticker("BRU"):
#             break

#         if cube.get_sticker("FRU") == cube.get_sticker("FLU"):
#             cube.do_moves(alg)
#             break
#         cube.do_moves("U")
#     else:
#         cube.do_moves(alg + " U " + alg)

def PLL2(cube:Cube):
    opgelost = 0
    # print(cube.get_sticker("FU"))
    for _ in range(4):
        if cube.get_sticker("FUR") == cube.get_sticker("FU"):
            opgelost += 1
        cube.do_moves("U")
        # print(opgelost)
    
    if opgelost != 4:
        if opgelost == 0:
            cube.do_moves("R U' R U R U R U' R' U' R2") #Om 1 kant te solven

        while cube.get_sticker("FUR") != cube.get_sticker("FU"):
            cube.do_moves("U")
        cube.do_moves("U2") #Zorgt dat opgeloste kant achter zit zodat het algoritme uitgevoerd kan worden

        while cube.get_sticker("FUR") != cube.get_sticker("FU"):
            # print("Vanaf Hier:")
            # cube.print_cube()
            cube.do_moves("R U' R U R U R U' R' U' R2") #Herhaalt dit algoritme, zodat elke kant kan worden opgelost. Dit kan een stuk efficienter door Pll(Ub) of Pll(Ua) te pakken (kijk jperm link)
            # print("2e!!!!!!!!!!!!!")
            # cube.print_cube()

    while cube.get_sticker("FU") != cube.get_sticker("FR"):
        cube.do_moves("U")




                



# cube = Cube(3)
# hussel_moves = input("Wat is de hussel? Voer in: ")
# # hussel_moves = "L2 U' D2 R F' R L2 B L U' R2 F2 B2 D F2 L2 B2 D2 L2" #hussel van cstimer.net - doet het nog niet
# # hussel_moves = "D L' F' D2 B' D' F' L' B2 R' F2 R' D2 R F2 L2 U2 L' B" #Deze doet het niet, nu wel
# # hussel_moves = "R' F R B' R' F' R B R' F R B' R' F' R B R' F R B' R' F' R B"
# # hussel_moves = "F R U R' U' R U R' U' R U R' U' F'" #DEBUGGER
# # hussel_moves = "D' R2 B' L2 R2 B' R2 F R2 B' R2 B2 U L2 B2 D L D R' B" #Deze doet het nog niet
# cube.do_moves(hussel_moves)

# cube.print_cube()
# print()
# print()

# # # start = time.time()
# # geef_oplossing(cube)
# oplossing, moves = geef_oplossing(cube)
# oplossing_korter = onnodig_weghalen(oplossing)
# print("Moves voor communicatie:", oplossing_korter)
# print(len(oplossing_korter))