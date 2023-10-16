import numpy as np
from testing import *
import os

Rs = np.linspace(10e-6,15e-6,10)
Ws = np.linspace(7e-6,3e-6,10)
path = os.getcwd() 
keys = "simiter,R,W,numerical,elementcount,nodecount,meshtime,tthtime,nextime\n"
try:
    os.remove("bl.csv")
except:
    pass

res = open("bl.csv","w")
res.write(keys)

iter = 0 
for _R,_W in zip(Rs,Ws):

    if iter > 2:
        os.chdir(f"./test{iter}")
        print(f"iteration {iter}")
     
        names = writeGeo("loop",R=_R,W=_W)

        mesh_start = time()
        mesh_stop = time()
        elem, nodes = getElementsAndNodeCount(["loop.msh", "loopFIELD.msh"])

        """ run first iteration of tth"""
        tth_start = time()
        runTTH()
        tth_end = time()
        i = readCurrent("./output/i.txt")
        """ run nex """
        nex_start = time()
        numerical = runNoiseEx("./output/loop_test.vtk", i)
        nex_end = time()
        """ write result """
        res.write(f"{iter},{_R},{_W},{numerical[0]},{elem[0][1]},{nodes[0][1]},{mesh_stop-mesh_start},{tth_end-tth_start},{nex_end-nex_start}\n")
        print(f"Done with iteration {iter}")
        os.chdir(path)
    iter = iter + 1
