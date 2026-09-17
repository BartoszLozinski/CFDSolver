import Mesh
import MeshProperties as MeshProp
import ExplicitHeatConduction
import ImplicitHeatConduction
import time
import MaterialProperties as MaterialProp
import SimulationProperties as SimulationProp

mesh_properties = MeshProp.MeshProperties.read_from_file("Setup/MeshProperties")
mesh_generator = Mesh.MeshGenerator(mesh_properties)
mesh = Mesh.Mesh(mesh_generator)
material_properties = MaterialProp.MaterialProperties.read_from_file("Setup/MaterialProperties")
simulation_properties = SimulationProp.SimulationProperties.read_from_file("Setup/SimulationProperties")
explicit_solver = ExplicitHeatConduction.ExplicitSolver(material_properties=material_properties, simulation_properties=simulation_properties)

start_time = time.time()

explicit_solver.solve(mesh)

end_time = time.time()

print(f'Time elapsed for 20x20 git and 500 iterations: t = {end_time - start_time}')
print("Starting implicit solver with the same setup!")

implicit_solver = ImplicitHeatConduction.ImplicitSolver(material_properties=material_properties, simulation_properties=simulation_properties)

start_time = time.time()

implicit_solver.solve(mesh)

end_time = time.time()

print(f'Time elapsed for 20x20 git and 500 iterations: t = {end_time - start_time}')
