from PropertiesReaderBase import PropertiesReaderBase


class MaterialProperties(PropertiesReaderBase):
    def __init__(self, thermal_conductivity, density, specific_heat):
        self.thermal_conductivity = thermal_conductivity
        self.density = density
        self.specific_heat = specific_heat

    @classmethod
    def _create_default_properties(cls):
        return cls(0.0, 0.0, 0.0)

    @classmethod
    def _create_properties_map(cls):
        return {
            "thermalConductivity": ("thermal_conductivity", float),
            "specificHeatCapacity": ("specific_heat", float),
            "density": ("density", float),
        }
