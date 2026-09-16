from PropertiesReaderBase import PropertiesReaderBase


class MeshProperties(PropertiesReaderBase):
    def __init__(self, dx: float, dy: float, nx: int, ny: int):
        if isinstance(dx, bool) or not isinstance(dx, (int, float)):
            raise TypeError("dx must be a float")
        if isinstance(dy, bool) or not isinstance(dy, (int, float)):
            raise TypeError("dy must be a float")
        if isinstance(nx, bool) or not isinstance(nx, int):
            raise TypeError("nx must be an integer")
        if isinstance(ny, bool) or not isinstance(ny, int):
            raise TypeError("ny must be an integer")

        self.dx = float(dx)
        self.dy = float(dy)
        self.nx = nx
        self.ny = ny

    @classmethod
    def _create_default_properties(cls):
        return cls(0.0, 0.0, 0, 0)

    @classmethod
    def _create_properties_map(cls):
        return {
            "dx": ("dx", float),
            "dy": ("dy", float),
            "nx": ("nx", int),
            "ny": ("ny", int),
        }
