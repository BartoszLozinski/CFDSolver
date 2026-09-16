import numpy as np

class MeshGenerator():
    def __init__(self, mesh_properties):
        self.dx = mesh_properties.dx
        self.dy = mesh_properties.dy
        self.nx = mesh_properties.nx
        self.ny = mesh_properties.ny

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
