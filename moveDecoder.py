from typing import List

from move import Move

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
    com = []

    for move in moves:
        current_move = move.face

        if move.dubbel:
            current_move += current_move
        elif move.kloktegen:
            current_move += current_move + current_move
        
        com.append(current_move)

    return "".join(com) #Spatie tussen elke beweging van hussel

def hussel_naar_communicatie(moves: List[Move]) -> str:
    nieuwe_moves = hussel_naar_moves(moves)
    moves_naar_communicatie(nieuwe_moves)

def inverted_moves(moves: List[Move]):
    inverted_moves = []

    for move in reversed(moves):
        inverted_move = Move(move.face, not move.kloktegen, move.dubbel)
        inverted_moves.append(inverted_move)
    
    return inverted_moves

if __name__ == "__main__": #Nog ff checken!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    hussel = "L U2 D B' R2 U2 F R B2 U2 R2 U R2 U2 F2 D R2 D F2"

    print(hussel_naar_moves(hussel))