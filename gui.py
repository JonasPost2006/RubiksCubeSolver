from pprint import pprint
import time

import pygame
from pygame.locals import *

from rubiks import Cube
from move import Move
from moveDecoder import hussel_naar_moves, moves_naar_hussel, onnodig_weghalen
from oplosser import geef_oplossing
# from communicatie import verstuurMoves

HEIGHT = 1440
WIDTH = 2415
CUBIE_SIZE = 115
HORIZONTAL_START = 30

class Gui:
    def __init__(self, cube: Cube):
        self.cube = cube
        self.screen = pygame.display.set_mode((1920, 1080))

    def run(self):
        self.draw_cube()

        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_SPACE:
                        com_solution, moves = geef_oplossing(self.cube)
                        solution = moves_naar_hussel(moves)
                        #ONNODIG WEGHALEN VAN SOLUTION
                        com_solution_verbeterd = onnodig_weghalen(com_solution)
                        # verstuurMoves(com_solution)
                        print(solution)
                        print("HIEROVEN SOLUITION")
                        for move in solution.split():
                            print(move)
                            self.cube.do_moves(move)
                            self.draw_cube()
                            # time.sleep(0.01)

        pygame.quit()

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
                    
                    pygame.draw.rect(self.screen, cubie, (x, y, CUBIE_SIZE, CUBIE_SIZE), 0)
                    pygame.draw.rect(self.screen, (0, 0, 0), (x, y, CUBIE_SIZE, CUBIE_SIZE), 5)

        pygame.display.update()