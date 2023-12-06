from typing import NewType, Tuple, List, TypeVar, Union
from itertools import permutations

from .pieces import Corner, Edge, CORNER_TO_UPFRONT, EDGE_TO_UPFRONT 

Colour = NewType("Colour", Tuple[int, int, int])

YELLOW = Colour((255, 255, 0))
GREEN = Colour((0, 255, 0))
RED = Colour((255, 0, 0))
BLUE = Colour((0, 0, 255))
ORANGE = Colour((255, 126, 0))
WHITE = Colour((255, 255, 255))

COLOUR_MAPPING = [("U", YELLOW), ("F", GREEN), ("L", RED), ("B", BLUE), ("R", ORANGE), ("D", WHITE)]

class Cube:
    def __init__(self, size:int):
        self.size = size
        self.faces = {face: self._generate_face(colour, size) for face, colour in COLOUR_MAPPING}
    
    def get_sticker(self, sticker: str) -> Colour:
        for perm in permutations(sticker):
            if "".join(perm) in EDGE_TO_UPFRONT:
                return self.get_edge("".join(perm))[sticker[0]]
            elif "".join(perm) in CORNER_TO_UPFRONT:
                return self.get_corner("".join(perm))[sticker[0]]
        raise ValueError(f"Geen geldige sticker: {sticker}")
    