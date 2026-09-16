class MeshProperties:
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
    def read_from_file(cls, filename="Setup/MeshProperties"):
        properties = cls(0.0, 0.0, 0, 0)
        properties_map = {
            "dx": ("dx", float),
            "dy": ("dy", float),
            "nx": ("nx", int),
            "ny": ("ny", int),
        }

        try:
            input_file = open(filename, "r", encoding="utf-8")
        except OSError as error:
            raise RuntimeError(
                f"Failed to open file for reading: {filename}"
            ) from error

        with input_file:
            for line in input_file:
                if not line.strip() or line.startswith("#"):
                    continue
                if line.strip() in ("{", "}"):
                    continue

                tokens = line.split()
                if len(tokens) < 2:
                    continue

                key, value = tokens[0], tokens[1]
                value = value.split("#", 1)[0]

                if key not in properties_map:
                    print(f"Unknown property found under {key} key.")
                    continue

                try:
                    property_name, parser = properties_map[key]
                    setattr(properties, property_name, parser(value))
                except (TypeError, ValueError) as error:
                    raise RuntimeError(
                        f"Invalid value for property '{key}' in file {filename}"
                    ) from error

        return properties
