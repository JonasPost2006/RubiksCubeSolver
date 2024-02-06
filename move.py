from dataclasses import dataclass


@dataclass
class Move:
    zijde: str
    kloktegen: bool
    dubbel: bool