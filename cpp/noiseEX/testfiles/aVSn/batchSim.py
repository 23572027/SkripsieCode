from multiprocessing import Process
from time import sleep
import re
import os
import numpy as np
from progress.bar import Bar
from tqdm import tqdm

def writeRadius(r1,r2):
    lpMesh = open("loop.geo", "r")
    loopMesh = lpMesh.read()
    lpMesh.close()

    reg1 = r"(%r1)"
    reg2 = r"(%r2)"

    sub1 = str(r1)
    sub2 = str(r2)

    loopMesh = re.sub(reg1,sub1,loopMesh,0,re.MULTILINE)
    loopMesh = re.sub(reg2,sub2,loopMesh,0,re.MULTILINE)

    try:
        lpTemp = open("loopTemp.geo", "x")
    except:
        os.remove("loopTemp.geo")
        lpTemp = open("loopTemp.geo","x")

    lpTemp.write(loopMesh)
    lpTemp.close()


    # write surface mesh
    lpMesh = open("loopFIELD.geo", "r")
    loopMesh = lpMesh.read()
    lpMesh.close()
    reg1 = r"(%r1)"
    reg2 = r"(%r2)"
    sub1 = str(r1)
    sub2 = str(r2)
    loopMesh = re.sub(reg1,sub1,loopMesh,0,re.MULTILINE)
    loopMesh = re.sub(reg2,sub2,loopMesh,0,re.MULTILINE)
    try:
        lpTemp = open("loopFIELDTemp.geo", "x")
    except:
        os.remove("loopFIELDTemp.geo")
        lpTemp = open("loopFIELDTemp.geo","x")
    lpTemp.write(loopMesh)
    lpTemp.close()

def runGMSH():
    print(f"{os.getpid()}: Meshing geometry\n")
    # os.system("gmsh loopFIELDTemp.geo -nopopup -0 -v 1")
    # os.system("gmsh loopTemp.geo -nopopup -0 -v 1")
    os.popen("gmsh loopFIELDTemp.geo -nopopup -0 -v 1").read()
    os.popen("gmsh loopTemp.geo -nopopup -0 -v 1").read()
    try:
        os.system("rm *.geo_unrolled")
        os.remove("loopFIELDTemp.geo")
        os.remove("loopTemp.geo")
    except:
        print("nope")
    print(f"{os.getpid()}: Done meshing\n")


def runTTH():
    print(f"{os.getpid()}: Running tth settings_washer.json >/dev/null 2>&1")
    os.system("tth settings_washer.json >/dev/null 2>&1")
    print(f"{os.getpid()}: Done\n")


def getCurrent():
    iFile = open("./output/i.txt")
    it = iFile.read()
    iFile.close()
    reg = r"fone fone .+ (\d*\.\d*e-\d*)"
    i_s = re.findall(reg,it,re.MULTILINE)[0]
    return i_s
    
def runNoiseEx(b_path,current):
    path = "/home/paul/Skripsie/Code/SkripsieCode/cpp/noiseEX/cmake-build-debug/nex"
    print(f"{os.getpid()}: Running "+path+" "+b_path+" "+current)
    v = os.popen(path+" "+b_path+" "+current).read()
    print(f"{os.getpid()}: Done\n")
    v = v.split("\n")
    return v


def runSim(folderPath,r1,r2):
    try:
        os.mkdir(folderPath)
    except:
        os.system(f"rm -rf {folderPath}")
        os.mkdir(folderPath)
    os.chdir(folderPath)
    os.system("cp ../loop.geo ./")
    os.system("cp ../loopFIELD.geo ./")
    os.system("cp ../settings_washer.json ./")
    SPIN_DENS = 5e17
    MU_B = 9.2740100783e-24
    PHI_0 = 2.067833848e-15
    MU_0 = 1.25663706212e-6 	
    Analytic = lambda R, D : 2/3*MU_0**2*MU_B**2*SPIN_DENS*R/D*1/(PHI_0**2)
    
    writeRadius(r1, r2)
    runGMSH()
    runTTH()
    i = getCurrent()
    msfn_numerical = runNoiseEx(f"/home/paul/Skripsie/Code/SkripsieCode/cpp/noiseEX/testfiles/aVSn/{folderPath}/output/loop_test.vtk",i)
    print(msfn_numerical)
    numerical_area = msfn_numerical[1]
    msfn_numerical = msfn_numerical[0]
    msfn_analytical = Analytic(r1,r2*2)
    analytic_area = 4*np.pi**2*r1*r2
    # write result to file
    val = f"{r1},{2*r2},{msfn_analytical},{msfn_numerical},{analytic_area},{numerical_area}\n"
    
    try:
        os.remove("resPARR_SIM.csv")
    except:
        pass

    res = open("resPARR_SIM.csv","w")
    res.write("R,D,Analytic,Numerical,Analytic Area, Numerical Area\n")
    res.write(val)
    res.close()
    os.chdir("/home/paul/Skripsie/Code/SkripsieCode/cpp/noiseEX/testfiles/aVSn/")

    return val



if __name__ == "__main__":
    r1s = np.linspace(10e-6, 30e-6, 50)
    r2s = np.linspace(2e-6,0.2e-6,50)
    pl = []
    count = 0
    for r1 in r1s:
        count = count + 1
        path = f"./sim{count}"
        pl.append(Process(target=runSim,args=(path,r1,r2,)))

    t = pl[2]
    pl[2] = pl[0]
    pl[0] = t

    for i in range(len(pl[0:-1:8])):
        print(f"Running batch: {i*8} -> {(i+1)*8}")
        for p in pl[i*8:(i+1)*8]:
            p.start()
        for p in pl[i*8:(i+1)*8]:
            p.join()
        print(f"Completed batch: {i*8} -> {(i+1)*8}")

    # not_done = True
    # while not_done:
    #     not_done = False
    #     for p in pl:
    #         if p.is_alive() == True:
    #             not_done = True
    #     sleep(0.5)

    print("\n\n Sim complete")