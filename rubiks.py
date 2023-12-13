from typing import NewType, Tuple, List, TypeVar, Union
from itertools import permutations

from pieces import Corner, Edge, CORNER_TO_UPFRONT, EDGE_TO_UPFRONT
from move import Move
from colour import Colour, COLOUR_MAP, COLOUR_NAMES
import moveDecoder

class Cube:
    def __init__(self, size:3): #int = 3 moet gegeven worden voor 3x3 rubiks
        self.size = size
        self.faces = {face: self.maak_face(colour, size) for face, colour in COLOUR_MAP} #Dit maakt de zes zijdes van de cube met elk een eigen kleur.
    
    def maak_face(self, colour: Colour, size: 3): #Creëert een 2D lijst van een cube face
        return [[colour for _ in range(size)] for _ in range(size)] #Geeft bijv. [[Colour("red"), Colour("red"), Colour("red")] x 3]

    def get_sticker(self, sticker: str) -> Colour:
        for perm in permutations(sticker):
            if "".join(perm) in EDGE_TO_UPFRONT:
                return self.get_edge("".join(perm))[sticker[0]]
            elif "".join(perm) in CORNER_TO_UPFRONT:
                return self.get_corner("".join(perm))[sticker[0]]
        raise ValueError(f"Geen geldige sticker: {sticker}")
    
    def get_edge(self, piece:str) -> Edge:
        moves = moveDecoder.hussel_naar_moves(EDGE_TO_UPFRONT[piece]) #geeft moves nodig om edge naar upfront te krijgen

        self.do_moves(moves) #Doet de moves om een edge naar de UPFRONT positie te krijgen zodat hij kan worden uitgelezen
        info = Edge({                                   #geeft Edge de kleur van de edge piece. Piece[0] is op de bovenste(U) zijde  op plaats -1, 1, en geeft die hun kleur. Zo kan bepaald worden hoe de edge eruit ziet
            piece[0]: Colour(self.faces["U"][-1][1]),
            piece[1]: Colour(self.faces["F"][0][1])
        })
        moveDecoder.inverted_moves(moves) #Doet de moves terug zodat de cube onveranderd blijft
        return info
    
    def get_corner(self, piece: str) -> Corner:
        moves = moveDecoder.hussel_naar_moves(CORNER_TO_UPFRONT[piece])
        
        self.do_moves(moves)
        info = Corner({
            piece[0]: Colour(self.faces["U"][-1][-1]),
            piece[1]: Colour(self.faces["F"][0][-1]),
            piece[2]: Colour(self.faces["R"][0][0])
        })
        moveDecoder.inverted_moves(moves)

        return info

    def do_moves(self, moves: Union[str, List[Move]]): #Accepteert een string van moves, of een lijst Move. De moves worden vervolgens in een list gezet
        if isinstance(moves, str):
            moves = moveDecoder.hussel_naar_moves(moves)
        
        for move in moves:
            if move.face == "y":        #y is notatie om de cube naar rechts te draaien zonder een zijde te draaien
                self.draai_cube_rechts()
            elif move.face == "y'":
                for _ in range(3):
                    self.draai_cube_rechts()
            else:
                self.draai(move)
    
    def opgelost(self) -> bool:
        for face in self.faces.values():
            for row in face:
                if any(piece_colour != face[0][0] for piece_colour in row): #Als er een piece is met een andere kleur dan de middelste, dan false
                    return False
        
        return True
    
    def draai_face(self, face:str):
        self.faces[face] = [list(row) for row in zip(*self.faces[face][::-1])]

    def draai_aanligende_faces(self, face:str):
        if face == "U":
            veranderende_rijen = [self.faces[face][0] for face in ["F", "L", "B", "R"]]  #Maak een lijst met alle pieces in de eerste rij van de aanligende zijdes.
            self.faces["F"][0], self.faces["L"][0], self.faces["B"][0], self.faces["R"][0] = veranderende_rijen[-1:] + veranderende_rijen[:-1] #p_i_r[-1:] pakt de inhoud van het laatste element in de lijst, dus eerste rij van zijde R
            #p_i_r[:-1] pakt de rest van de lijst, dus eerste rij van F, L en B. Inhoud van R wordt voor de rest geplakt. Dit is hetzelfde als een draai van 90 graden.

        elif face == "D":
            veranderende_rijen = [self.faces[face][2] for face in ["F", "L", "B", "R"]]  #GROTE HULP EN BRON https://www.geeksforgeeks.org/python-list-slicing/
            self.faces["F"][2], self.faces["L"][2], self.faces["B"][2], self.faces["R"][2] = veranderende_rijen[1:] + veranderende_rijen[:1]
        
        elif face == "F":
            veranderende_faces = [self.faces["U"], transporeer(self.faces["R"]), self.faces["D"], transporeer(self.faces["L"])]
            veranderende_rijen = [veranderende_faces[0][2], veranderende_faces[1][0][::-1], veranderende_faces[2][0], veranderende_faces[3][2][::-1]]

            veranderende_faces[0][2], veranderende_faces[1][0], veranderende_faces[2][0], veranderende_faces[3][2] = veranderende_rijen[-1:] + veranderende_rijen[:-1]

            self.faces["U"][2] = veranderende_faces[0][2]
            self.faces["R"] = transporeer(veranderende_faces[1]) #transporeer terug
            self.faces["D"][0] = veranderende_faces[2][0]
            self.faces["L"] = transporeer(veranderende_faces[3])

        elif face == "R":
            self.draai_cube_rechts()
            self.draai_aanligende_faces("F")
            self.draai_cube_rechts(kloktegen = True)
        
        elif face == "L":
            self.draai_cube_rechts(kloktegen = True)
            self.draai_aanligende_faces("F")
            self.draai_cube_rechts()

        elif face == "B":
            self.draai_cube_rechts(dubbel = True)
            self.draai_aanligende_faces("F")
            self.draai_cube_rechts(dubbel = True)

    def draai(self, move:Move):
        for _ in range(2 if move.dubbel else 3 if move.kloktegen else 1):
            self.draai_face(move.face)
            self.draai_aanligende_faces(move.face)

    def draai_cube_rechts(self, dubbel = False, kloktegen = False):
        for _ in range(2 if dubbel else 3 if kloktegen else 1):
            veranderende_faces = [self.faces[face] for face in ["F", "L", "B", "R"]]
            self.faces["F"], self.faces["L"], self.faces["B"], self.faces["R"] = veranderende_faces[-1:] + veranderende_faces[:-1]

            self.draai_face("U")
            for _ in range(3):
                self.draai_face("D")        #????????????????????/

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


def transporeer(matrix):
    return list(map(list, zip(*matrix)))
# cube = Cube(3)
# move_F = Move("F", False, False)
# move_R = Move("R", False, False)
# cube.draai(move_F)
# cube.draai(move_R)
# cube.print_cube()