import Mesh
import MeshProperties as MeshProp
import ExplicitHeatConduction
import time
import MaterialProperties as MaterialProp

mesh_properties = MeshProp.MeshProperties.read_from_file()
mesh_generator = Mesh.MeshGenerator(mesh_properties.dx, mesh_properties.dy, mesh_properties.nx, mesh_properties.ny)
mesh = Mesh.Mesh(mesh_generator)

# Stainless steel
# material_properties = MP.MaterialProperties(16.0, 7850, 500)
material_properties = MaterialProp.MaterialProperties.read_from_file()

solver = ExplicitHeatConduction.ExplicitSolver(material_properties=material_properties, dt=100)

start_time = time.time()
solver.solve(mesh, timesteps=500, should_plot=True, plot_interval=50)
end_time = time.time()

print(f'Time elapsed for 20x20 git and 500 iterations: t = {end_time - start_time}')
