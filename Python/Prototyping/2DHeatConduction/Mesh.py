import numpy as np

class MeshGenerator():
    def __init__(self, dx, dy, nx, ny):
        self.dx = dx
        self.dy = dy
        self.nx = nx
        self.ny = ny

    def generate_mesh(self):
        ghost_cells_layers = int(2)
        Array = np.zeros((self.nx + ghost_cells_layers, self.ny + ghost_cells_layers))
        return Array


class Mesh():
    def __init__(self, mesh_generator):
        self.mesh = mesh_generator.generate_mesh()
        self.dx = mesh_generator.dx
        self.dy = mesh_generator.dy
        self.nx = mesh_generator.nx
        self.ny = mesh_generator.ny

    def initialize(self, function):
        for row in range(len(self.mesh[0, :])):
            for column in range(len(self.mesh[:, 0])):
                self.mesh[row][column] = function(row * self.dx, column * self.dy)