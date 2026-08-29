import Mesh
import BoundaryCondition as BC

T_top = 373  # K
T_bottom = 273  # K

mesh_generator = Mesh.MeshGenerator(0.1, 0.1, 5, 5)
mesh = Mesh.Mesh(mesh_generator)

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
