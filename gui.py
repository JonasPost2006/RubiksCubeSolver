from pprint import pprint
import time

import pygame
from pygame.locals import *
pygame.init()

from rubiks import Cube
from move import Move
from moveDecoder import hussel_naar_moves, moves_naar_hussel, onnodig_weghalen
from oplosser import geef_oplossing
# from communicatie import verstuurMoves

HEIGHT = 1440
WIDTH = 2415
CUBIE_SIZE = 115
HORIZONTAL_START = 30

invoer = ''
font = pygame.font.SysFont('frenchscript',40)
hussel_box = pygame.Rect(75,75,100,50)
active = False
kleur = pygame.Color('purple')
clock = pygame.time.Clock()

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

                if event.type == pygame.MOUSEBUTTONDOWN:
                    if hussel_box.collidepoint(event.pos):
                        active = True
                    else:
                        active = False

                if event.type == pygame.KEYDOWN:
                    if active:
                        if event.key == pygame.K_BACKSPACE:
                            invoer = invoer[:-1]
                        else:
                            invoer += event.unicode

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
                self.screen.fill('orange')
                if active:
                    kleur = pygame.Color('red')
                else:
                    kleur = pygame.Color('purple')
                pygame.draw.rect(self.screen, kleur, hussel_box, 4)
                surf = font.render(invoer,True,'orange')
                self.screen.blit(surf, (hussel_box.x +5 , hussel_box.y +5))
                self.text_box.w = max(100, surf.get_width()+10)
                pygame.display.update()
                clock.tick(50)

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