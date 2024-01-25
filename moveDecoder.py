from typing import List
from move import Move
import re

#Hussel en moves zijn anders, een 'geschreven' moveset zoals in pieces.py, het is een notatie die niet handig is om te gebruiken in code.
#Daarom wordt het hier in een andere vorm gezet.

def hussel_naar_moves(hussel: str) -> List[Move]: #Zet alle moves in een lijst
    moves = []

    for move in hussel.split():
        kloktegen = "'" in move
        dubbel = "2" in move
        moves.append(Move(move[0], kloktegen, dubbel)) #Creëert een Move object voor elke move in de hussel en geeft aan of het een klok mee, tegen of dubbele move is
    return moves

def moves_naar_hussel(moves: List[Move]) -> str:
    hussel = []

    for move in moves:
        current_move = move.face

        if move.dubbel:
            current_move += "2"
        elif move.kloktegen:
            current_move += "'"
        
        hussel.append(current_move)

    return " ".join(hussel) #Spatie tussen elke beweging van hussel

def moves_naar_communicatie(moves: List[Move]) -> str:
    communicatie = []
    move_lijst = ["f", "r", "b", "l"]
    move_y = 0

    for move in moves:
        if move.face.lower() == 'y': #Omdat y niet kan worden toegepast bij de robot moeten de instructies van de moves worden aangepast.
            move_y += 1
            continue    #Y moet niet in de communicatie komen want daar kan de robot niks mee doen. Daarom uit de hele loop

        if move.face.lower() in move_lijst:
            current_move = move_lijst[(move_lijst.index(move.face.lower()) + move_y) % len(move_lijst)]
        else:
            current_move = move.face.lower()

        if move.kloktegen:
            current_move = current_move.upper()
            if move.dubbel:
                current_move += current_move
        elif move.dubbel:
            current_move += current_move
        
        # if len(communicatie) >= 3 and all(prev_move == communicatie[-1] for prev_move in communicatie[-3:]): WERKT NOG NIET GOED
        #     del communicatie[-3:]
        #     continue
        # elif len(communicatie) >= 2 and communicatie[-1] == communicatie[-2] == current_move:
        #     del communicatie[-2:]
        #     current_move = current_move.upper() if current_move.islower() else current_move.lower()

        communicatie.append(current_move)

    return "".join(communicatie)

def hussel_naar_communicatie(moves: List[Move]) -> str:
    nieuwe_moves = hussel_naar_moves(moves)
    moves_naar_communicatie(nieuwe_moves)

def inverted_moves(moves: List[Move]):
    inverted_moves = []

    for move in reversed(moves):
        inverted_move = Move(move.face, not move.kloktegen, move.dubbel)
        inverted_moves.append(inverted_move)
    
    return inverted_moves

def onnodig_weghalen(moves):
    moves = re.sub(r'(.)\1{3}', '', moves) #Haal vier opeenvolgende tekens weg, want dat staat gelijk aan niks
    moves = re.sub(r'([a-z])\1{2}', lambda m: m.group(1).upper(), moves) #Verandert drie opeenvolgende kleine letters in 1 hoofdletter
    moves = re.sub(r'([A-Z])\1{2}', lambda m: m.group(1).lower(), moves) #Precies tegenovergestelde hierboven
        
    #Haalt twee tekens weg als de eerste een hoofdletter was, en de volgende een kleine letter van dezelfde letter - Reductie van ongeveer 15 moves
    result = []
    i = 0
    while i < len(moves):
        if i < len(moves) - 1 and ((moves[i].isupper() and moves[i+1].islower()) or (moves[i].islower() and moves[i+1].isupper())) and moves[i].swapcase() == moves[i+1]:
            i += 2 
        else:
            result.append(moves[i])
            i += 1

    return ''.join(result)

