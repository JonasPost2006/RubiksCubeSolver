from typing import List, Dict, Union

from main import Cube
from pieces import Corner, Edge, EDGE_TO_UPFRONT, CORNER_TO_UPFRONT
from colour import Colour
from move import Move
import moveDecoder

class movesGedaan(Cube):
    def __init__(self, size: 3, faces: Dict[str, List[List[Colour]]] = None):
        super().__init__(size)
        self.faces = faces if faces else self.faces
        self.movesGedaan = []
    
    def get_moves_gedaan(self) -> List[Move]:
        return self.movesGedaan
    
    def get_edge(self, piece:str) -> Edge:
        moves = moveDecoder.hussel_naar_moves(EDGE_TO_UPFRONT[piece]) #geeft moves nodig om edge naar upfront te krijgen

        self.do_moves(moves, False) #Doet de moves om een edge naar de UPFRONT positie te krijgen zodat hij kan worden uitgelezen
        info = Edge({                                   #geeft Edge de kleur van de edge piece. Piece[0] is op de bovenste(U) zijde  op plaats -1, 1, en geeft die hun kleur. Zo kan bepaald worden hoe de edge eruit ziet
            piece[0]: Colour(self.faces["U"][-1][1]),
            piece[1]: Colour(self.faces["F"][0][1])
        })
        self.do_moves(moveDecoder.inverted_moves(moves), False) #Doet de moves terug zodat de cube onveranderd blijft
        return info

    def get_corner(self, piece: str) -> Corner:
        moves = moveDecoder.hussel_naar_moves(CORNER_TO_UPFRONT[piece])
        
        self.do_moves(moves, False)
        info = Corner({
            piece[0]: Colour(self.faces["U"][-1][-1]),
            piece[1]: Colour(self.faces["F"][0][-1]),
            piece[2]: Colour(self.faces["R"][0][0])
        })
        self.do_moves(moveDecoder.inverted_moves(moves, False))
        return info
    
    def do_moves(self, moves: Union[str, List[Move]], save_history: bool = True):
        super().do_moves(moves)

        if isinstance(moves, str):
            moves = moveDecoder.hussel_naar_moves(moves)

        if save_history:
            for move in moves:
                self.movesGedaan.append(move)