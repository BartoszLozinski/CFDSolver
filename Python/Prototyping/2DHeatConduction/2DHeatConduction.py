import Mesh
import ExplicitHeatConduction
import time
import MaterialProperties as MP

mesh_generator = Mesh.MeshGenerator(0.1, 0.1, 20, 20)
mesh = Mesh.Mesh(mesh_generator)

# Stainless steel
# material_properties = MP.MaterialProperties(16.0, 7850, 500)
material_properties = MP.MaterialProperties.read_from_file()

solver = ExplicitHeatConduction.ExplicitSolver(material_properties=material_properties, dt=100)

start_time = time.time()
solver.solve(mesh, timesteps=500, should_plot=True, plot_interval=50)
end_time = time.time()

print(f'Time elapsed for 20x20 git and 500 iterations: t = {end_time - start_time}')
