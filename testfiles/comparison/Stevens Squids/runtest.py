import numpy as np
from testing import *


keys = "simiter,remiter,R,W,numerical,elementcount,nodecount,meshtime,tthtime,nextime\n"

""" sim setup """
Rs = np.array([85,40]) * 1e-6
Ws = np.array([60,15]) * 1e-6

fname = "steveS2.csv"

try:
    os.remove(fname)
except:
    pass

res = open(fname,"w")
res.write(keys)
iter = 0
res.close()
""" start simulation loop"""
for _W, _R in tqdm(zip(Ws,Rs)):
    res = open(fname,"a")
    print(f"iteration {iter}")
    remiter = 0
    names = writeGeo("loop",firstIter=True,R=_R,W=_W)

    mesh_start = time()
    runGMSH(names, "-0", "")
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
    res.write(f"{iter},{0},{_R},{_W},{numerical[0]},{elem[0][1]},{nodes[0][1]},{mesh_stop-mesh_start},{tth_end-tth_start},{nex_end-nex_start}\n")

    for k in range(4):
        res = open(fname,"a")
        print(f"\t Remesh iteration: {k}\n-------------------------")
        names = writeGeo("loop",R=_R,W=_W)

        """ remesh """
        mesh_start = time()
        n = remesh("./output/J_washer.vtk",names,0.2)
        mesh_stop = time()

        elem, nodes = getElementsAndNodeCount(["loop.msh", "loopFIELD.msh"])
        if int(elem[0][1]) > 200000:
            break
        """ run tth  """
        tth_start = time()
        runTTH()
        tth_end = time()

        """ run noise ex """
        nex_start = time()
        numerical = runNoiseEx("./output/loop_test.vtk", i)
        nex_end = time()

        res.write(f"{iter},{k+1},{_R},{_W},{numerical[0]},{elem[0][1]},{nodes[0][1]},{mesh_stop-mesh_start},{tth_end-tth_start},{nex_end-nex_start}\n")
        res.close()
        print(f"\t Done with Remesh iteration: {k}\n-------------------------")

    cleanGeo(names)
    cleanGeo(n)
    print(f"done with iteration {iter}")
    iter = iter + 1
    res.close()

res.close()
