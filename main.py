import threading
from rubiks import Cube
from communicatie import verstuurMoves
from oplosser import geef_oplossing
from moveDecoder import hussel_naar_moves, moves_naar_communicatie, onnodig_weghalen
from gui import Gui

def run_gui(cube):
    gui = Gui(cube)
    gui.run()

cube = Cube(3)
hussel_moves = input("Wat is de hussel? Voer in: ")
cube.do_moves(hussel_moves)  # Apply the provided scramble

# Run the GUI in a separate thread
gui_thread = threading.Thread(target=run_gui, args=(cube,))
gui_thread.start()

hussel_moves_pc = hussel_naar_moves(hussel_moves)
communicatie_moves_hussel = moves_naar_communicatie(hussel_moves_pc)
verstuurMoves(communicatie_moves_hussel)
cube.print_cube()
print()

oplossing_com = geef_oplossing(cube)
oplossing_com_verbeterd = onnodig_weghalen(oplossing_com)

invoer = input("Mag hij oplossen? y voor doorgaan.")
if invoer == "y":
    gui_thread.join()  # Wait for the GUI thread to finish
    verstuurMoves(oplossing_com_verbeterd)
    print("Moves:", oplossing_com_verbeterd)
    print("Aantal moves:", len(oplossing_com_verbeterd))
