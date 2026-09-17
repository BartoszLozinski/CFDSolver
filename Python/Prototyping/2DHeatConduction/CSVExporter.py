from pathlib import Path

import numpy as np


class CSVExporter:
    def export(self, filename, data):
        path = Path(filename)
        path.parent.mkdir(parents=True, exist_ok=True)

        array = np.asarray(data)
        if array.ndim != 2:
            raise ValueError("data must be a two-dimensional array")

        np.savetxt(path, array, delimiter="\t", fmt="%.15g")