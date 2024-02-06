from typing import List, Dict, Union

from rubiks import Cube
from pieces import Corner, Edge, EDGE_TO_UPFRONT, CORNER_TO_UPFRONT
from colour import Colour
from move import Move
import moveDecoder

class movesGedaan(Cube):
    def __init__(self, size: 3, zijdes: Dict[str, List[List[Colour]]] = None):
        super().__init__(size) #MISSCHIEN WEGHALENNNNNNNNNNNNNNNNNNNNNNNNNNNN!!!!!!!!!!!!!!!!!!!!
        self.zijdes = zijdes if zijdes else self.zijdes #geeft de informatie over de zijdes aan self.zijdes. Als er geen info van zijdes is uit cube.py dan wordt de standaard info aan self.zijdes gegeven.
        self.movesGedaan = []
    
    def get_moves_gedaan(self) -> List[Move]: #Deze functie geeft een lijst met de moves die zijn gedaan terug
        return self.movesGedaan
    
    def get_edge(self, piece:str) -> Edge:
        moves = moveDecoder.hussel_naar_moves(EDGE_TO_UPFRONT[piece]) #geeft moves nodig om edge naar upfront te krijgen

        self.do_moves(moves, False) #Omdat deze moves niet aan de move list toegevoegd moeten worden, het is namelijk alleen om de kleuren van de edge te krijgen, staat er False
        info = Edge({                                   #geeft Edge de kleur van de edge piece. Piece[0] is op de bovenste(U) zijde  op plaats -1, 1, en geeft die hun kleur. Zo kan bepaald worden hoe de edge eruit ziet
            piece[0]: Colour(self.zijdes["U"][-1][1]),
            piece[1]: Colour(self.zijdes["F"][0][1])
        })
        self.do_moves(moveDecoder.inverted_moves(moves), False)
        return info

    def get_corner(self, piece: str) -> Corner:
        moves = moveDecoder.hussel_naar_moves(CORNER_TO_UPFRONT[piece])
        
        self.do_moves(moves, False) 
        info = Corner({
            piece[0]: Colour(self.zijdes["U"][-1][-1]),
            piece[1]: Colour(self.zijdes["F"][0][-1]),
            piece[2]: Colour(self.zijdes["R"][0][0])
        })
        self.do_moves(moveDecoder.inverted_moves(moves), False)
        return info
    
    def do_moves(self, moves: Union[str, List[Move]], save_history: bool = True): #moves kan een string of een lijst aan moves zijn
        super().do_moves(moves) #roept do_moves van de Cube class in main.py aan

        if isinstance(moves, str): #Als de moves in string vorm is wordt het naar 'moves' vorm gezet. Deze vorm kan de cube laten draaien
            moves = moveDecoder.hussel_naar_moves(moves)

        if save_history:
            for move in moves:
                self.movesGedaan.append(move)