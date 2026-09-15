class MaterialProperties:
    def __init__(self, thermal_conductivity, density, specific_heat):
        self.thermal_conductivity = thermal_conductivity
        self.density = density
        self.specific_heat = specific_heat

    @classmethod
    def read_from_file(cls, filename="Setup/MaterialProperties"):
        properties = cls(0.0, 0.0, 0.0)
        properties_map = {
            "thermalConductivity": "thermal_conductivity",
            "specificHeatCapacity": "specific_heat",
            "density": "density",
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
                    setattr(properties, properties_map[key], float(value))
                except ValueError as error:
                    raise RuntimeError(
                        f"Invalid value for property '{key}' in file {filename}"
                    ) from error

        return properties
