import Mesh
import BoundaryCondition as BC
import Solver

T_top = 373  # K
T_bottom = 273  # K

mesh_generator = Mesh.MeshGenerator(0.1, 0.1, 20, 20)
mesh = Mesh.Mesh(mesh_generator)

# Stainless steel - unsed now
material_properties = Solver.MaterialProperties(16.0, 7850, 500)

solver = Solver.ExplicitSolver(material_properties=material_properties, dt=0.001)
solver.solve(mesh, timesteps=500, should_plot=True, plot_interval=50)

"""
bc_top = BC.Direchlet(mesh.mesh[0, :], lambda dx: T_top)
bc_bottom = BC.Direchlet(mesh.mesh[-1, :], lambda dx: T_bottom)
bc_left = BC.Neuman(mesh.mesh[:, 0], lambda dy, alignedCell: alignedCell, mesh.mesh[:, 1])
bc_right = BC.Neuman(mesh.mesh[:, -1], lambda dy, alignedCell: alignedCell, mesh.mesh[:, -2])

mesh.initialize(lambda x, y: 300)
bc_top.set(mesh.dx)
bc_bottom.set(mesh.dx)
bc_left.set(mesh.dy)
bc_right.set(mesh.dy)

print("Finished {T_top}")
"""