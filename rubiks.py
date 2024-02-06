from typing import NewType, Tuple, List, TypeVar, Union
from itertools import permutations

from pieces import Corner, Edge, CORNER_TO_UPFRONT, EDGE_TO_UPFRONT
from move import Move
from colour import Colour, COLOUR_MAP, COLOUR_NAMES
import moveDecoder

class Cube:
    def __init__(self, size:3): #int = 3 moet gegeven worden voor 3x3 rubiks
        self.size = size
        self.zijdes = {zijde: self.maak_zijde(colour, size) for zijde, colour in COLOUR_MAP} #Dit maakt de zes zijdes van de cube met elk een eigen kleur.
    
    def maak_zijde(self, colour: Colour, size: 3): #Creëert een 2D lijst van een cube zijde
        return [[colour for _ in range(size)] for _ in range(size)] #Geeft bijv. [[Colour("red"), Colour("red"), Colour("red")] x 3]

    def get_sticker(self, sticker: str) -> Colour:
        for mogelijkheid in permutations(sticker):        #Door door elke mogelijkheid van sticker-code te gaan, hoef je niet elke keer heel precies te zijn met de stickercode
            if "".join(mogelijkheid) in EDGE_TO_UPFRONT:  #Als hij in edge_to_upfront of corner_to_upfront zit, wordt de waarde gegeven van de piece.
                return self.get_edge("".join(mogelijkheid))[sticker[0]]
            elif "".join(mogelijkheid) in CORNER_TO_UPFRONT:
                return self.get_corner("".join(mogelijkheid))[sticker[0]]
    
    def get_edge(self, piece:str) -> Edge:
        moves = moveDecoder.hussel_naar_moves(EDGE_TO_UPFRONT[piece]) #Geeft moves nodig om edge naar upfront te krijgen
        self.do_moves(moves) #Doet de moves om een edge naar de UPFRONT positie te krijgen zodat hij kan worden uitgelezen
        kleuren = Edge({                                   #geeft Edge de kleur van de edge piece. Piece[0] is op de bovenste(U) zijde  op plaats 2, 1, en geeft die hun kleur. Zo kan bepaald worden hoe de edge eruit ziet
            piece[0]: Colour(self.zijdes["U"][2][1]),
            piece[1]: Colour(self.zijdes["F"][0][1])
        })
        moveDecoder.inverted_moves(moves) #Doet de moves terug zodat de cube onveranderd blijft

        return kleuren
    
    def get_corner(self, piece: str) -> Corner:     #Hier gebeurt hetzelfde als bij get_edge
        moves = moveDecoder.hussel_naar_moves(CORNER_TO_UPFRONT[piece])
        self.do_moves(moves)
        kleuren = Corner({
            piece[0]: Colour(self.zijdes["U"][2][2]),
            piece[1]: Colour(self.zijdes["F"][0][2]),
            piece[2]: Colour(self.zijdes["R"][0][0])
        })
        moveDecoder.inverted_moves(moves)

        return kleuren

    def do_moves(self, moves: Union[str, List[Move]]): #Accepteert een string van moves, of een lijst Move. De moves worden vervolgens in een lijst gezet
        if isinstance(moves, str):      #Als de moves in stringvorm staan, is het in husselvorm. Daarom wordt het naar de moves-vorm gebracht
            moves = moveDecoder.hussel_naar_moves(moves)
        
        for move in moves:
            if move.zijde == "y":        #y is notatie om de cube naar rechts te draaien zonder een zijde te draaien
                self.draai_cube_rechts()
            elif move.zijde == "y'":
                for _ in range(3):
                    self.draai_cube_rechts()
            else:
                self.draai(move)        #Draai de zijde die move zegt dat gedraait moet worden, door draai wordt de zijde zelf, en de aanligende zijdes bewerkt.
    
    def opgelost(self) -> bool:
        for zijde in self.zijdes.values():
            for rij in zijde:
                if any(piece_colour != zijde[0][0] for piece_colour in rij): #Als er een piece is met een andere kleur dan de middelste, dan false
                    return False
        
        return True
    
    def draai_zijde(self, zijde:str):
        self.zijdes[zijde] = [list(rij) for rij in zip(*self.zijdes[zijde][::-1])]

    def draai_aanligende_zijdes(self, zijde:str):
        if zijde == "U":
            veranderende_rijen = [self.zijdes[zijde][0] for zijde in ["F", "L", "B", "R"]]  #Maak een lijst met alle pieces in de eerste rij van de aanligende zijdes.
            self.zijdes["F"][0], self.zijdes["L"][0], self.zijdes["B"][0], self.zijdes["R"][0] = veranderende_rijen[-1:] + veranderende_rijen[:-1] #p_i_r[-1:] pakt de inhoud van het laatste element in de lijst, dus eerste rij van zijde R
            #p_i_r[:-1] pakt de rest van de lijst, dus eerste rij van F, L en B. Inhoud van R wordt voor de rest geplakt. Dit is hetzelfde als een draai van 90 graden.

        elif zijde == "D":
            veranderende_rijen = [self.zijdes[zijde][2] for zijde in ["F", "L", "B", "R"]]  #Grote hulp en bron: https://www.geeksforgeeks.org/python-list-slicing/
            self.zijdes["F"][2], self.zijdes["L"][2], self.zijdes["B"][2], self.zijdes["R"][2] = veranderende_rijen[1:] + veranderende_rijen[:1]
        
        elif zijde == "F":
            veranderende_zijdes = [self.zijdes["U"], transponeer(self.zijdes["R"]), self.zijdes["D"], transponeer(self.zijdes["L"])]
            veranderende_rijen = [veranderende_zijdes[0][2], veranderende_zijdes[1][0][::-1], veranderende_zijdes[2][0], veranderende_zijdes[3][2][::-1]]

            veranderende_zijdes[0][2], veranderende_zijdes[1][0], veranderende_zijdes[2][0], veranderende_zijdes[3][2] = veranderende_rijen[-1:] + veranderende_rijen[:-1]

            self.zijdes["U"][2] = veranderende_zijdes[0][2]
            self.zijdes["R"] = transponeer(veranderende_zijdes[1]) #transporeer terug
            self.zijdes["D"][0] = veranderende_zijdes[2][0]
            self.zijdes["L"] = transponeer(veranderende_zijdes[3])

        elif zijde == "R":
            self.draai_cube_rechts()
            self.draai_aanligende_zijdes("F")
            self.draai_cube_rechts(kloktegen = True)
        
        elif zijde == "L":
            self.draai_cube_rechts(kloktegen = True)
            self.draai_aanligende_zijdes("F")
            self.draai_cube_rechts()

        elif zijde == "B":
            self.draai_cube_rechts(dubbel = True)
            self.draai_aanligende_zijdes("F")
            self.draai_cube_rechts(dubbel = True)

    def draai(self, move:Move):
        for _ in range(2 if move.dubbel else 3 if move.kloktegen else 1):
            self.draai_zijde(move.zijde)
            self.draai_aanligende_zijdes(move.zijde)

    def draai_cube_rechts(self, dubbel = False, kloktegen = False): #Voor de y move
        for _ in range(2 if dubbel else 3 if kloktegen else 1):
            veranderende_zijdes = [self.zijdes[zijde] for zijde in ["F", "L", "B", "R"]]    #Alle deze zijdes veranderen
            self.zijdes["F"], self.zijdes["L"], self.zijdes["B"], self.zijdes["R"] = veranderende_zijdes[-1:] + veranderende_zijdes[:-1] #F word L, L wordt B, enz.

            self.draai_zijde("U") #U moet met de klok mee en D tegen de klok in dus 3x klok mee
            for _ in range(3):
                self.draai_zijde("D")

    def print_cube(self):
        volgorde = [("U", (0, 1)), ("L", (1, 0)), ("F", (1, 1)), ("R", (1, 2)), ("B", (1, 3)), ("D", (2, 1))]     #Volgorde waarin de cube uitgevouwen / geprint gaat worden
        
        geprinte_cube = [["        " for _ in range(12)] for _ in range(9)] #De cube wordt 12 breedt, want vier zijdes naast elkaar, en 9 hoog, want drie zijdes hoog

        for zijde, (rij_offset, col_offset) in volgorde: #Haal de inhoud van elke zijde op
            zijde_inhoud = self.zijdes[zijde]
            for rij in range(self.size): #Size is 3
                for col in range(self.size):
                    unfolded_rij = rij + rij_offset * self.size
                    unfolded_col = col + col_offset * self.size
                    geprinte_cube[unfolded_rij][unfolded_col] = f"[{COLOUR_NAMES[zijde_inhoud[rij][col]]}]"

        for rij in geprinte_cube:
            print(" ".join(rij))


def transponeer(matrix):
    return list(map(list, zip(*matrix)))
# cube = Cube(3)
# move_F = Move("F", False, False)
# move_R = Move("R", False, False)
# cube.draai(move_F)
# cube.draai(move_R)
# cube.print_cube()