class Field():
    def __init__(self, mesh):
        self.mesh = mesh
        self.field = mesh.mesh.copy()

    def __getitem__(self, key):
        return self.field[key]

    def __setitem__(self, key, value):
        self.field[key] = value

    def copy(self):
        return self.field.copy()

    def initialize(self, function):
        rows, columns = self.field.shape
        for row in range(rows):
            for column in range(columns):
                self.field[row, column] = function(row * self.mesh.dx,
                                                   column * self.mesh.dy)

    def set_boundary_conditions(self, top_bc, bottom_bc, left_bc, right_bc):
        top_bc.set(self.mesh.dx)
        bottom_bc.set(self.mesh.dx)
        left_bc.set(self.mesh.dy)
        right_bc.set(self.mesh.dy)
