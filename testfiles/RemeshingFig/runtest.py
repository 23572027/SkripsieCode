import numpy as np
from testing import *


keys = "simiter,remiter,R,W,numerical,elementcount,nodecount,meshtime,tthtime,nextime\n"
# Rs = np.linspace(10e-6,15e-6,10)
# Ws = np.linspace(0.5e-6,100e-6,25)
Ws = np.logspace(np.log10(0.5e-6),np.log10(100e-6),25)
""" sim setup """
# SPIN_DENS = 5e17
# MU_B = 9.2740100783e-24
# PHI_0 = 2.067833848e-15
# MU_0 = 1.25663706212e-6 	
# Analytic = lambda R, D : 2/3*MU_0**2*MU_B**2*SPIN_DENS*R/D*1/(PHI_0**2)


try:
    os.remove("stevecomp.csv")
except:
    pass

res = open("stevecomp.csv","w")
res.write(keys)
iter = 0
_R = 5E-6
res.close()
""" start simulation loop"""
for _W in tqdm(Ws):
    res = open("stevecomp.csv","a")
    print(f"iteration {iter}")
    remiter = 0
    names = writeGeo("loop",W=_W)

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

    for k in range(3):
        res = open("stevecomp.csv","a")
        print(f"\t Remesh iteration: {k}\n-------------------------")
        names = writeGeo("loop",R=_R,W=_W)

        """ remesh """
        mesh_start = time()
        n = remesh("./output/J_washer.vtk",names,0.1)
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

        res.write(f"{iter},{k},{_R},{_W},{numerical[0]},{elem[0][1]},{nodes[0][1]},{mesh_stop-mesh_start},{tth_end-tth_start},{nex_end-nex_start}\n")
        res.close()
        print(f"\t Done with Remesh iteration: {k}\n-------------------------")

    cleanGeo(names)
    cleanGeo(n)
    print(f"done with iteration {iter}")
    iter = iter + 1
    res.close()

res.close()
