import pyvista as vis

red = vis.read("build/B_washer.vtk")
print(red.point_data )

