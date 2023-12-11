# Helper function to transpose a matrix
from move import Move

def _transpose(matrix):
    return list(map(list, zip(*matrix)))

# T = TypeVar("T")
# def _transpose(l: List[List[T]]) -> List[List[T]]:
#     return [list(i) for i in zip(*l)]

def draai_face(self, face:str):
        self.faces[face] = [list(row) for row in zip(*self.faces[face][::-1])]
# Method to perform adjacent face swap
def draai_aanligende_faces(faces):
    if "F" in faces:
      # print(faces["R"])
      # print(_transpose(faces["R"]))
      l = [faces["U"], _transpose(faces["R"]),
                 faces["D"], _transpose(faces["L"])]
      # print(l)
      r = [l[0][2], l[1][0][::-1], l[2][0], l[3][2][::-1]]
      # print(r)
      # print(faces["L"])
      # print(_transpose(faces["L"]))

      l[0][-1], l[1][0], l[2][0], l[3][-1] = r[-1:] + r[:-1]

      faces["U"][-1] = l[0][-1]
      faces["R"] = _transpose(l[1])
      faces["D"][0] = l[2][0]
      faces["L"] = _transpose(l[3])

def draai(self, move:Move):
    for _ in range(2 if move.dubbel else 3 if move.kloktegen else 1):
        draai_face(move.face)
        draai_aanligende_faces(move.face)

def draai_cube_rechts(self, dubbel = False, kloktegen = False):
    for _ in range(2 if dubbel else 3 if kloktegen else 1):
        veranderende_faces = [self.faces[face] for face in ["F", "L", "B", "R"]]
        self.faces["F"], self.faces["L"], self.faces["B"], self.faces["R"] = veranderende_faces[-1:] + veranderende_faces[:-1]

        self.draai_face("U")
        for _ in range(3):
            self.draai_face("D")
# Example to simulate and test the "F" face rotation
# Define the initial state of the cube's faces
initial_faces = {
    "U": [[11, 11, 11], [12, 12, 12], [13, 13, 13]],
    "F": [[21, 21, 21], [22, 22, 22], [23, 23, 23]],
    "D": [[3, 3, 3], [3, 3, 3], [3, 3, 3]],
    "R": [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
    "L": [[10, 11, 12], [13, 14, 15], [16, 17, 18]],
    "B": [[6, 6, 6], [6, 6, 6], [6, 6, 6]]
}

# Print initial state
# print("Initial State:")
# for face, content in initial_faces.items():
#     print(f"Face {face}:")
#     for row in content:
#         print(row)
#     print()

# Rotate the "F" face
draai_aanligende_faces(initial_faces)

# Print resulting state after rotation
print("State after rotating 'F' face:")
for face, content in initial_faces.items():
    print(f"Face {face}:")
    for row in content:
        print(row)
    print()