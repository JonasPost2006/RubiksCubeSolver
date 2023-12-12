from typing import List
from copy import deepcopy

from main import Cube
from move import Move
from movesGedaan import movesGedaan
from colour import WHITE, GREEN, ORANGE, BLUE, RED, YELLOW
from moveDecoder import hussel_naar_moves, moves_naar_hussel

def geef_oplossing(cube: Cube) -> List[Move]:
    kopie_cube = movesGedaan(cube.size, deepcopy(cube.faces))