class Laplacian:
    def __init__(self, dx, dy, field):
        self.dx = dx
        self.dy = dy
        self.field = field

    def __call__(self, ix, iy):
        if ix < 1 or iy < 1 or ix >= self.field.shape[0] - 1 or iy >= self.field.shape[1] - 1:
            raise IndexError(f"Index ix {ix} or iy {iy} is out of field range")

        return ((self.field[ix + 1, iy] - 2 * self.field[ix, iy] + self.field[ix - 1, iy]) / self.dx**2 +
                (self.field[ix, iy + 1] - 2 * self.field[ix, iy] + self.field[ix, iy - 1]) / self.dy**2)
