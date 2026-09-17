from PropertiesReaderBase import PropertiesReaderBase


class SimulationProperties(PropertiesReaderBase):
    def __init__(self, dt: float, should_export_results: bool, export_frequency: int, timesteps: int, tolerance: float):
        if isinstance(dt, bool) or not isinstance(dt, (int, float)):
            raise TypeError("dt must be a float")
        if not isinstance(should_export_results, bool):
            raise TypeError("should_export_results must be a boolean")
        if isinstance(export_frequency, bool) or not isinstance(export_frequency, int):
            raise TypeError("export_frequency must be an integer")
        if isinstance(timesteps, bool) or not isinstance(timesteps, int):
            raise TypeError("timesteps must be an integer")
        if isinstance(tolerance, bool) or not isinstance(tolerance, (int, float)):
            raise TypeError("tolerance must be an integer")

        self.dt = float(dt)
        self.should_export_results = should_export_results
        self.export_frequency = export_frequency
        self.timesteps = timesteps
        self.tolerance = float(tolerance)

    @classmethod
    def _create_default_properties(cls):
        return cls(0.0, False, 0, 0, 0.0)

    @classmethod
    def _create_properties_map(cls):
        return {
            "dt": ("dt", float),
            "shouldExportResults": ("should_export_results", bool),
            "exportFrequency": ("export_frequency", int),
            "timesteps": ("timesteps", int),
            "tolerance": ("tolerance", float),
        }
