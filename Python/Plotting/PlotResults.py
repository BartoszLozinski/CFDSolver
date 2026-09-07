import numpy as np
import matplotlib.pyplot as plot
from pathlib import Path

results_dir = Path("Results/T")
csv_files = sorted(results_dir.glob("*.csv"), key=lambda p: int(p.stem))

if not csv_files:
    raise FileNotFoundError(f"No CSV files found in {results_dir}")

fig, ax = plot.subplots()
fig.tight_layout()

image = None

for file in csv_files:
    data = np.loadtxt(file, dtype=float)

    if image is None:
        image = ax.imshow(data, cmap="jet", origin="upper", aspect="auto")
        fig.colorbar(image, ax=ax, label="Temperature [K]")
    else:
        image.set_data(data)

    ax.set_title(f"Temperature field at timestep {file.stem}")
    ax.set_xlabel("x_id")
    ax.set_ylabel("y_id")

    fig.canvas.draw()
    plot.pause(0.05)

    print(f"Showing {file.name} - press any key to continue")
    plot.waitforbuttonpress()

