import os
import re
import numpy as np
from time import time


def writeGeo(name, **kwargs):
    lpMesh = open(f"{name}.geo", "r")
    fpMesh = open(f"{name}FIELD.geo", "r")
    loopMesh = lpMesh.read()
    fieldMesh = fpMesh.read()

    for k in kwargs.keys():
        rs = rf"(%{k})"
        sub = str(kwargs[k])
        loopMesh = re.sub(rs,sub,loopMesh,0,re.MULTILINE)
        fieldMesh = re.sub(rs,sub,fieldMesh,0,re.MULTILINE)

    try:
        lpTemp = open(f"{name}TEMP.geo", "x")
    except:
        os.remove(f"{name}TEMP.geo")
        lpTemp = open(f"{name}TEMP.geo","x")
        
    try:
        lfTemp = open(f"{name}FIELDTEMP.geo", "x")
    except:
        os.remove(f"{name}FIELDTEMP.geo")
        lfTemp = open(f"{name}FIELDTEMP.geo", "x")

    lfTemp.write(fieldMesh)
    lpTemp.write(loopMesh)
    
    lpTemp.close()
    lfTemp.close()

    lpMesh.close()
    fpMesh.close()

    return [f"{name}TEMP.geo",f"{name}FIELDTEMP.geo"]


def cleanGeo(names) -> None:
    for name in names:
        try:
            os.remove(name)
        except:
            pass
    try:
        os.system("rm *.geo_unrolled")
    except:
        pass


def runGMSH(names,*args) -> list:
    options= " "
    for k in args:
        options = options + " " + k 
    for name in names:
        os.system(f"gmsh {name}"+ options)

    return names
    
def readCurrent(path) -> str:
    iFile = open(path)
    it = iFile.read()
    iFile.close()
    reg = r"fone fone .+ (\d*\.\d*e.\d*)"
    i_s = re.findall(reg,it,re.MULTILINE)[0]
    return i_s

def runNoiseEx(b_path,current):
    path = "/home/paul/Skripsie/Code/SkripsieCode/cpp/noiseEX/cmake-build-debug/nex"
    v = os.popen(path+" "+b_path+" "+current).read()
    v = v.split("\n")
    return v

def runTTH():
    print("Starting tth")
    os.system("tth settings_washer.json > tthlog.txt")
    print("tth finished")

def getElementsAndNodeCount(names):
    nE = []
    nN = []
    for name in names:

        iFile = open(f"{name[:-4]}.msh")
        it = iFile.read()

        regNumNodes = r"\$Nodes\n(.*)\n"
        numNodes = re.findall(regNumNodes,it,re.MULTILINE)[0]
        nN.append((name,numNodes))
        regNumElem = r"\$Elements\n(.*)\n"
        numElem = re.findall(regNumElem,it,re.MULTILINE)[0]
        nE.append((name,numElem))
        iFile.close()
    return nE, nN

def remesh(outFile,names,perc):
    n = []
    for name in names:
        print(f"/home/paul/Skripsie/Code/SkripsieCode/cpp/TryRemeshing/cmake-build-debug/remesh {outFile} {name[:-4]}.geo {name[:-8]} {perc}")
        os.system(f"/home/paul/Skripsie/Code/SkripsieCode/cpp/TryRemeshing/cmake-build-debug/remesh {outFile} {name[:-4]}.geo {name[:-8]} {perc} > /dev/null")
        n.append(f"{name[:-8]}RM.geo")
        print("done with remeshing")
    return n

def seeMesh(names):
    for name in names:
        os.system(f"gmsh {name}")


if __name__ == "__main__":

    keys = "simiter,remiter,R,W,numerical,elementcount,nodecount,meshtime,tthtime,nextime\n"
    Rs = np.linspace(10e-6,40e-6,50)
    Ws = np.linspace(4e-6,0.6e-6,50)

    """ sim setup """
    # SPIN_DENS = 5e17
    # MU_B = 9.2740100783e-24
    # PHI_0 = 2.067833848e-15
    # MU_0 = 1.25663706212e-6 	
    # Analytic = lambda R, D : 2/3*MU_0**2*MU_B**2*SPIN_DENS*R/D*1/(PHI_0**2)


    try:
        os.remove("ringloop.csv")
    except:
        pass

    res = open("ringloop.csv","w")

    iter = 0
    """ start simulation loop"""
    for _R,_W in zip(Rs,Ws):
        
        print(f"iteration {iter}")
        remiter = 0
        names = writeGeo("loop",R=_R,W=_W)

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

        for k in range(2):
            print(f"\t Remesh iteration: {k}\n-------------------------")
            names = writeGeo("loop",R=_R,W=_W)

            """ remesh """
            mesh_start = time()
            n = remesh("./output/J_washer.vtk",names,0.1)
            mesh_stop = time()

            elem, nodes = getElementsAndNodeCount(["loop.msh", "loopFIELD.msh"])

            """ run tth  """
            tth_start = time()
            runTTH()
            tth_end = time()

            """ run noise ex """
            nex_start = time()
            numerical = runNoiseEx("./output/loop_test.vtk", i)
            nex_end = time()

            res.write(f"{iter},{k},{_R},{_W},{numerical[0]},{elem[0][1]},{nodes[0][1]},{mesh_stop-mesh_start},{tth_end-tth_start},{nex_end-nex_start}\n")
            print(f"\t Done with Remesh iteration: {k}\n-------------------------")

        cleanGeo(names)
        cleanGeo(n)
        
        iter = iter + 1
    
    res.close()