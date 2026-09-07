import numpy as np
import matplotlib.pyplot as plot

path = "Results/T/0.csv"

data = []

with open(path, "r", encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        row = [float(x) for x in line.split()]
        data.append(row)

array_2d = np.array(data, dtype=float)


plot.figure()
plot.imshow(array_2d, cmap="jet", origin="upper", aspect="auto")
plot.colorbar(label="Temperature [K]")
plot.title("Temperature field")
plot.xlabel("x")
plot.ylabel("y")
plot.show()

print(array_2d.shape)
