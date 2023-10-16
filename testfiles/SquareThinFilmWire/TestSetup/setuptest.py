import testing as t
import os
import numpy as np

Rs = np.linspace(10e-6,15e-6,10)
Ws = np.linspace(7e-6,3e-6,10)

path = os.getcwd()

i = 0

for i in range(10):
    os.chdir(f"./test{i}")
    os.system(f"cp loopTEMP.msh loop.msh")
    os.system(f"cp loopFIELDTEMP.msh loopFIELD.msh")
    os.chdir(path)
