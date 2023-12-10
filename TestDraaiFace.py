from collections import namedtuple

# Define a mock Colour class for illustration purposes
Colour = namedtuple('Colour', ['color'])

# Define the input face list
face = [
    [Colour("red"), Colour("blue"), Colour("white")],
    [Colour("green"), Colour("yellow"), Colour("red")],
    [Colour("orange"), Colour("white"), Colour("blue")]
]

# Simulate the draai_face method
rotated_face = [list(row) for row in zip(*face[::-1])]

# Display the original and rotated faces
print("Original Face:")
for row in face:
    print(row)

print("\nRotated Face:")
for row in rotated_face:
    print(row)