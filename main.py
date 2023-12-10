from typing import NewType, Tuple, List, TypeVar, Union
from itertools import permutations

from pieces import Corner, Edge, CORNER_TO_UPFRONT, EDGE_TO_UPFRONT
from move import Move
from colour import Colour, COLOUR_MAP, COLOUR_NAMES
import moveDecoder

class Cube:
    def __init__(self, size:3): #int = 3 moet gegeven worden voor 3x3 rubiks
        self.size = size
        self.faces = {face: self.maak_face(colour, size) for face, colour in COLOUR_MAP}
    
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
    
    def opgelost(self) -> bool:
        for face in self.faces.values():
            for row in face:
                if any(piece_colour != face[0][0] for piece_colour in row): #Als er een piece is met een andere kleur dan de middelste, dan false
                    return False
        
        return True
    
    def maak_face(self, colour: Colour, size: 3): #Creëert een 2D lijst van een cube face
        return [[colour for _ in range(size)] for _ in range(size)] #Geeft bijv. [[Colour("red"), Colour("red"), Colour("red")] x 3]
    
    def draai_face(self, face:str):
        self.faces[face] = [list(row) for row in zip(*self.faces[face][::-1])]

    def daai_aanligende_faces(self, face:str):
        if face == "U":
            veranderende_rijen = [self.faces[face][0] for face in ["F", "L", "B", "R"]]  #Maak een lijst met alle pieces in de eerste rij van de aanligende zijdes.
            self.faces["F"][0], self.faces["L"][0], self.faces["B"][0], self.faces["R"][0] = veranderende_rijen[-1:] + veranderende_rijen[:-1] #p_i_r[-1:] pakt de inhoud van het laatste element in de lijst, dus eerste rij van zijde R
            #p_i_r[:-1] pakt de rest van de lijst, dus eerste rij van F, L en B. Inhoud van R wordt voor de rest geplakt. Dit is hetzelfde als een draai van 90 graden.

        elif face == "D":
            veranderende_rijen = [self.faces[face][2] for face in ["F", "L", "B", "R"]]  #GROTE HULP EN BRON https://www.geeksforgeeks.org/python-list-slicing/
            self.faces["F"][2], self.faces["L"][2], self.faces["B"][2], self.faces["R"][2] = veranderende_rijen[1:] + veranderende_rijen[:1]
        
        elif face == "F":
            veranderende_faces = [self.faces["U"], transporeer(self.faces["R"]), self.faces["D"], transporeer(self.faces["L"])]
            veranderende_rijen = [veranderende_faces[0][2], veranderende_faces[1][0][::-1], self.faces[2][0], transporeer(self.faces[3][2][::-1])]

            veranderende_faces[0][2], veranderende_faces[1][0], veranderende_faces[2][0], veranderende_faces[3][2] = veranderende_rijen[-1:] + veranderende_rijen[:-1]

            self.faces["U"][2] = veranderende_faces[0][2]
            self.faces["R"] = transporeer(veranderende_faces[1]) #transporeer terug
            self.faces["D"][0] = veranderende_faces[2][0]
            self.faces["L"] = veranderende_faces([3])


    def print_cube(self):
        for face, content in self.faces.items():
            print(f"Face {face}:")
            for row in content:
                # Map RGB values to color names
                color_names_row = [COLOUR_NAMES[colour] for colour in row]
                print(color_names_row)
            print()  # Print an empty line for separation between faces


def transporeer(matrix):
    return list(map(list, zip(*matrix)))
# cube = Cube(3)
# # cube.print_cube()
# cube.draai_face("F") #Werkt nog niet
# cube.print_cube()