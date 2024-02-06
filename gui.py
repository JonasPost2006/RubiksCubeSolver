from pprint import pprint
import time

import pygame
from pygame.locals import *
pygame.init()

from rubiks import Cube
from move import Move
from moveDecoder import hussel_naar_moves, moves_naar_hussel, onnodig_weghalen, hussel_naar_communicatie, moves_naar_communicatie
from oplosser import geef_oplossing
# from communicatie import verstuurMoves

HEIGHT = 1440
WIDTH = 2415
CUBIE_SIZE = 115
HORIZONTAL_START = 30


font = pygame.font.SysFont(None,40)
kleur_uit = pygame.Color('lightskyblue3')
kleur_aan = pygame.Color('dodgerblue2')
clock = pygame.time.Clock()

class Gui:
    def __init__(self, cube: Cube):
        self.cube = Cube(3) #cube
        self.screen = pygame.display.set_mode((1920, 1080))
        self.active = False
        self.invoer = ''
        self.hussel_box = pygame.Rect(50, 50, 140, 40)
        self.kleur = kleur_uit
        self.achtergrond_kleur = pygame.Color((30, 30, 30))

    def run(self):
        self.screen.fill(self.achtergrond_kleur)
        self.draw_cube()
        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.MOUSEBUTTONDOWN:
                    if self.hussel_box.collidepoint(event.pos):
                        self.active = not self.active
                    else:
                        self.active = False

                    self.kleur = kleur_aan if self.active else kleur_uit

                if event.type == pygame.KEYDOWN:
                    if self.active:
                        self.screen.fill((30, 30, 30))
                        self.draw_cube()
                        if event.key == pygame.K_RETURN:
                            self.cube.do_moves(self.invoer)
                            print(self.invoer)
                            self.cube.print_cube()
                            hussel_move_vorm = hussel_naar_moves(self.invoer)
                            hussel_communicatie = moves_naar_communicatie(hussel_move_vorm)
                            print("HIER HUSSEL COM", hussel_communicatie)
                            # verstuurMoves(hussel_communicatie)
                            self.invoer = ''
                            self.screen.fill((30, 30, 30))
                            self.draw_cube()
                        elif event.key == pygame.K_BACKSPACE:
                            self.invoer = self.invoer[:-1]
                            self.screen.fill((30, 30, 30))
                            self.draw_cube()
                        else:
                            self.invoer += event.unicode

                    elif event.key == pygame.K_SPACE:
                        com_solution, moves = geef_oplossing(self.cube)
                        solution = moves_naar_hussel(moves)
                        #ONNODIG WEGHALEN VAN SOLUTION
                        com_solution_verbeterd = onnodig_weghalen(com_solution)
                        print("Oplossing:", com_solution_verbeterd)
                        print("Aantal moves:", len(com_solution_verbeterd))
                        # verstuurMoves(com_solution_verbeterd)
                        for move in solution.split():
                            self.cube.do_moves(move)
                            self.draw_cube()
                            # time.sleep(0.075)
                    
                    elif event.key == pygame.K_ESCAPE:
                        pygame.quit()

  

                surf = font.render(self.invoer, True, self.kleur)
                
                width = max(200, surf.get_width() + 10)
                self.hussel_box.w = width
                
                self.screen.blit(surf, (self.hussel_box.x + 5 , self.hussel_box.y + 5))
                
                pygame.draw.rect(self.screen, self.kleur, self.hussel_box, 4)
                
                # pygame.display.update()
                pygame.display.flip()
                clock.tick(30)

        pygame.quit()

    def draw_cube(self):
        for zijde_num, zijde in enumerate(["U", "F", "D", "B", "L", "R"]):
            for row_num, row in enumerate(self.cube.zijdes[zijde]):
                for cubie_num, cubie in enumerate(row):
                    if zijde == "L":
                        zijde_num = 1
                        horizontal_adjust = - self.cube.size * CUBIE_SIZE
                    elif zijde == "R":
                        zijde_num = 1
                        horizontal_adjust = self.cube.size * CUBIE_SIZE
                    elif zijde == "B":
                        zijde_num = 1
                        horizontal_adjust = 2 * self.cube.size * CUBIE_SIZE
                    else:
                        horizontal_adjust = 0
                        
                    x = 1920 / 3 + cubie_num * CUBIE_SIZE + horizontal_adjust
                    y = self.cube.size * zijde_num * CUBIE_SIZE + row_num * CUBIE_SIZE + HORIZONTAL_START
                    
                    pygame.draw.rect(self.screen, cubie, (x, y, CUBIE_SIZE, CUBIE_SIZE), 0)
                    pygame.draw.rect(self.screen, (0, 0, 0), (x, y, CUBIE_SIZE, CUBIE_SIZE), 5)

        pygame.display.update()