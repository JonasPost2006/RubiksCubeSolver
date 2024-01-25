import re

def onnodig_weghalen(moves):
    moves = re.sub(r'(.)\1{3}', '', moves) #Haal vier opeenvolgende tekens weg, want dat staat gelijk aan niks
    moves = re.sub(r'([a-z])\1{2}', lambda m: m.group(1).upper(), moves) #Verandert drie opeenvolgende kleine letters in 1 hoofdletter
    moves = re.sub(r'([A-Z])\1{2}', lambda m: m.group(1).lower(), moves) #Precies tegenovergestelde hierboven
    
    #Haalt twee tekens weg als de eerste een hoofdletter was, en de volgende een kleine letter van dezelfde letter
    result = []
    i = 0
    while i < len(moves):
        if i < len(moves) - 1 and ((moves[i].isupper() and moves[i+1].islower()) or (moves[i].islower() and moves[i+1].isupper())) and moves[i].swapcase() == moves[i+1]:
            i += 2  # Skip both uppercase and lowercase letters of the same kind
        else:
            result.append(moves[i])
            i += 1

    return ''.join(result)

    # return moves

# Test case
moves = "RUulDddD" 
result = onnodig_weghalen(moves)
print(result)