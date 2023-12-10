from typing import NewType, Tuple

Colour = NewType("Colour", Tuple[int, int, int])


YELLOW = Colour((255, 255, 0))
GREEN = Colour((0, 255, 0))
RED = Colour((255, 0, 0))
BLUE = Colour((0, 0, 255))
ORANGE = Colour((255, 126, 0))
WHITE = Colour((255, 255, 255))

COLOUR_MAP = [("U", YELLOW), ("F", GREEN), ("L", RED), ("B", BLUE), ("R", ORANGE), ("D", WHITE)]

COLOUR_NAMES = {
    YELLOW: "Yellow",
    GREEN: "Green",
    RED: "Red",
    BLUE: "Blue",
    ORANGE: "Orange",
    WHITE: "White",
}