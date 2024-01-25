    def draw_cube(self):
        for face_num, face in enumerate(["U", "F", "D", "B", "L", "R"]):
            for row_num, row in enumerate(self.cube.faces[face]):
                for cubie_num, cubie in enumerate(row):
                    if face == "L":
                        face_num = 1
                        horizontal_adjust = - self.cube.size * CUBIE_SIZE
                    elif face == "R":
                        face_num = 1
                        horizontal_adjust = self.cube.size * CUBIE_SIZE
                    elif face == "B":
                        face_num = 1
                        horizontal_adjust = 2 * self.cube.size * CUBIE_SIZE
                    else:
                        horizontal_adjust = 0

                    x = 1920 / 3 + cubie_num * CUBIE_SIZE + horizontal_adjust
                    y = self.cube.size * face_num * CUBIE_SIZE + row_num * CUBIE_SIZE + HORIZONTAL_START

                    color = (255, 255, 255) if cubie == 1 else (0, 0, 0)  # Set color based on cubie value (1 or 0)

                    pygame.draw.rect(self.screen, color, (x, y, CUBIE_SIZE, CUBIE_SIZE), 0)
                    pygame.draw.rect(self.screen, (0, 0, 0), (x, y, CUBIE_SIZE, CUBIE_SIZE), 5)

        pygame.display.update()
