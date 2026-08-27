import numpy as np
import matplotlib.pyplot as plt

"""
density * specific_heat * dT / dtime = thermal_conductivity * Laplacian(T) + HeatSource

For now 1D equation - to be developed for 2D and better architecture
Steady state - ok
Transient - TODO
heat Source term - including convection - TODO
"""

# y_i1 = y_(i+1)
# y_i_1 = y_(i-1)
def second_order_derivative_central_diff(y_i1, y_i, y_i_1, dx):
    return (y_i1 - 2 * y_i + y_i_1) / (dx ** 2)

# Discrete equation will look like:

# to match equations orders
# k * (y_i1 - 2 * y_i + y_i_1) / (dx ** 2) = rho * cp (y_i - y_i_1) / dt      // * dx**2 * 2dt
# k * dt * (y_i1 - 2 * y_i + y_i_1) = rho * cp * dx**2 * (y_i - y_i_1)
# y_i1 * a + y_i * b + y_i_1 * c = d

# d = 0 
# Simplified:
# y_i1 - 2 * y_i + y_i = 0



def generate_2nd_order_pde_matrix(a, b, c, size):
    # solves
    # y_i1 * a + y_i * b + y_i_1 * c
    # matrix of coefficient will look like:
    # x1    x2      x3      x4      x5      =   T
    # b     c       0       0       0       =   -a * T_0 + d
    # a     b       c       0       0       =   d
    # 0     c       b       c       0       =   d
    # 0     0       c       b       c       =   d
    # 0     0       0       a       b       =   -c * T_end + d

    InnerArray = np.zeros((size, size))
    for i in range(size):
        InnerArray[i][i] = b
        if i > 0:
            InnerArray[i][i - 1] = a
        if i < size - 1:
            InnerArray[i][i + 1] = c

    return InnerArray


# direchlet condition only right now
def generate_RHS_for_2nd_order_pde(a, c, d, size, y_0, y_end, RHS_previous_timestep):
    RHS = np.zeros(size)

    for i in range(len(RHS)):
        RHS[i] = RHS_previous_timestep[i] + d

    RHS[0] -= a * y_0
    RHS[-1] -= c * y_end

    return RHS



# Stainless steel
thermal_conductivity = 16.0 # W / (m * K)
density = 7850 # kg / m3
specific_heat = 500 # J / (kg * K)
x_0 = 0.0 # m 
x_end = 1.0 # m
T_0 = 1.0 # K
T_end = 0.0 # K
dx = 0.05 # m
dt = 360# s

x = np.linspace(x_0, x_end, int((x_end - x_0) / dx) + 1)

# Implicit method
r = thermal_conductivity * dt / (density * specific_heat * dx**2)
y_i1_coeff = -r
y_i_coeff = 1 + 2 * r
y_i_1_coeff = -r
T = np.linspace(T_0, T_0, len(x))
T[-1] = T_end
T_inner = T[1: -1].copy()
Array = generate_2nd_order_pde_matrix(y_i1_coeff, y_i_coeff, y_i_1_coeff, len(x) - 2)

timesteps = 100

for timestep in range(timesteps):
    RHS = generate_RHS_for_2nd_order_pde(y_i1_coeff, y_i_1_coeff, 0, len(x) - 2, T[0], T[-1], T_inner)
    T_inner = np.linalg.solve(Array, RHS)
    T = np.concatenate([[T_0], T_inner, [T_end]])

    if timestep % 10 == 0:
        plt.plot(x, T, label = f"timestep: {timestep}")
        plt.xlabel("x [m]")
        plt.ylabel("T [K]")
        plt.title("Solution of steady state conduction")
        plt.legend()
        plt.grid()
        plt.show()

print("x: ", x)
print("T: ", T)

