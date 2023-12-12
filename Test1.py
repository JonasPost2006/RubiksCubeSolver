# Helper function to transpose a matrix
from move import Move
def _transpose(matrix):
    return list(map(list, zip(*matrix)))

# T = TypeVar("T")
# def _transpose(l: List[List[T]]) -> List[List[T]]:
#     return [list(i) for i in zip(*l)]

def draai_face(face:str, faces):
    faces[face] = [list(row) for row in zip(*faces[face][::-1])]

# Method to perform adjacent face swap
def draai_cube_rechts(faces):
    # for _ in range(2 if dubbel else 3 if kloktegen else 1):
    veranderende_faces = [faces[face] for face in ["F", "L", "B", "R"]]
    faces["F"], faces["L"], faces["B"], faces["R"] = veranderende_faces[-1:] + veranderende_faces[:-1]

    draai_face("U", faces)
    for _ in range(3):
        draai_face("D", faces) 

def _adjacent_face_swap(faces):
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
# Example to simulate and test the "F" face rotation
# Define the initial state of the cube's faces

initial_faces = {
    "U": [[11, 11, 11], [12, 12, 12], [13, 13, 13]],
    "F": [[21, 21, 21], [22, 22, 22], [23, 23, 23]],
    "D": [[31, 32, 33], [34, 35, 36], [37, 38, 39]],
    "R": [[41, 42, 43], [44, 45, 46], [47, 48, 49]],
    "L": [[51, 52, 53], [54, 55, 56], [57, 58, 59]],
    "B": [[61, 62, 63], [64, 65, 66], [67, 68, 69]]
}

# Print initial state
# print("Initial State:")
# for face, content in initial_faces.items():
#     print(f"Face {face}:")
#     for row in content:
#         print(row)
#     print()

# Rotate the "F" face
# _adjacent_face_swap(initial_faces)
# draai_cube_rechts(initial_faces)

# Print resulting state after rotation
print("State after rotating 'F' face:")
for face, content in initial_faces.items():
    print(f"Face {face}:")
    for row in content:
        print(row)
    print()