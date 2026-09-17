import Mesh
import MeshProperties as MeshProp
import ExplicitHeatConduction
import time
import MaterialProperties as MaterialProp
import SimulationProperties as SimulationProp

mesh_properties = MeshProp.MeshProperties.read_from_file("Setup/MeshProperties")
mesh_generator = Mesh.MeshGenerator(mesh_properties)
mesh = Mesh.Mesh(mesh_generator)


# TODO
# Separate plotting (use existing script) - export to csv
# Laplacian operator

material_properties = MaterialProp.MaterialProperties.read_from_file("Setup/MaterialProperties")
simulation_properties = SimulationProp.SimulationProperties.read_from_file("Setup/SimulationProperties")

solver = ExplicitHeatConduction.ExplicitSolver(material_properties=material_properties, simulation_properties=simulation_properties)

start_time = time.time()
solver.solve(mesh)

end_time = time.time()

print(f'Time elapsed for 20x20 git and 500 iterations: t = {end_time - start_time}')
