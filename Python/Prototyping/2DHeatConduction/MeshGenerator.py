import numpy as np

class MeshGenerator():
    def __init__(self, dx, dy, nx, ny):
        self.dx = dx
        self.dy = dy
        self.nx = nx
        self.ny = ny

    def generate_mesh(self):
        ghost_cells_layers = int(2)
        Array = np.zeros(self.nx + ghost_cells_layers, self.ny + ghost_cells_layers)
        return Array
