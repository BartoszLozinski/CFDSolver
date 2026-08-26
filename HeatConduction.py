import numpy as np
import matplotlib.pyplot as plt

"""
density * specific_heat * dT / dtime = thermal_conductivity * Laplacian(T) + HeatSource

For now 1D equation - to be developed for 2D and better architecture

"""

# y_i1 = y_(i+1)
# y_i_1 = y_(i-1)
def second_order_derivative_central_diff(y_i1, y_i, y_i_1, dx):
    return (y_i1 - 2 * y_i + y_i_1) / (dx ** 2)

# Discrete equation will look like:

# k * (y_i1 - 2 * y_i + y_i_1) / (dx ** 2) = 0
# Simplified:
# y_i1 - 2 * y_i + y_i = 0

# matrix of coefficient will look like:
# x1    x2      x3      x4      x5      =   T

# -2    1       0       0       0       =   -1 * T_0
# 1     -2      1       0       0       =   0
# 0     1       -2      1       0       =   0
# 0     0       1       -2      1       =   0
# 0     0       0       1       -2      =   -1 * T_end

# Stainless steel
thermal_conductivity = 16.0 # W / (m * K)
# density = 7850 # kg / m3
# specific_heat = 500 # J / (kg * K)
x_0 = 0.0 # m 
x_end = 1.0 # m
T_0 = 373 # K
T_end = 273 # K
dx = 0.05 # m

x = np.linspace(x_0, x_end, int((x_end - x_0) / dx) + 1)
Array = np.zeros((len(x) - 2, len(x) - 2))

# fulfill matrix
for i in range(len(x) - 2):
    Array[i][i] = -2
    if (i > 0):
        Array[i][i - 1] = 1
    if (i < len(x) - 3):
        Array[i][i + 1] = 1

RHS = np.zeros(len(x) - 2)
RHS[0] = -T_0
RHS[-1] = -T_end

T_inner = np.linalg.solve(Array, RHS)
T = np.concatenate([[T_0], T_inner, [T_end]])

plt.plot(x, T)
plt.xlabel("x [m]")
plt.ylabel("T [K]")
plt.title("Solution of steady state conduction")
plt.grid()
plt.show()

print("x: ", x)
print("T: ", T)

