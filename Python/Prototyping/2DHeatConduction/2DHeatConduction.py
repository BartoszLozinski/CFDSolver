import Mesh
import Solver
import time

T_top = 373  # K
T_bottom = 273  # K

mesh_generator = Mesh.MeshGenerator(0.1, 0.1, 20, 20)
mesh = Mesh.Mesh(mesh_generator)

# Stainless steel - unsed now
material_properties = Solver.MaterialProperties(16.0, 7850, 500)

solver = Solver.ExplicitSolver(material_properties=material_properties, dt=100)

start_time = time.time()
solver.solve(mesh, timesteps=500, should_plot=False, plot_interval=50)
end_time = time.time()

print(f'Time elapsed for 20x20 git and 500 iterations: t = {end_time - start_time}')
