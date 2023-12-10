from dataclasses import dataclass


@dataclass
class Move:
    face: str
    kloktegen: bool
    dubbel: bool