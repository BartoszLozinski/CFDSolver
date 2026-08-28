class BoundaryCondition:
    def __init__(self, boundary_cells, function):
        self.boundary_cells = boundary_cells
        self.function = function

    def set(self, space_step):
        pass


#right now only space dependend BC
#pass slices of the mesh boudnary cells
#TODO add time dependent
class Direchlet(BoundaryCondition):
    def set(self, space_step):
        for i in range(len(self.boundary_cells)):
            self.boundary_cells[i] = self.function(space_step * i)


class Neuman(BoundaryCondition):
    def __init__(self, boundary_cells, function, aligned_cells):
        super().__init__(boundary_cells, function)
        self.aligned_cells = aligned_cells


    def set(self, space_step):
        for i in range(len(self.boundary_cells)):
            self.boundary_cells[i] = self.function(space_step * i, self, self.aligned_cells[i])
