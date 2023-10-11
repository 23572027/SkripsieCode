import os

path = os.getcwd()

for i in range(2,11):
    os.chdir(f"{path}/test{i}")
    print(f"Running test {i}")
    os.system("tth settings_washer.json > tthlog.txt")
    print(f"Done with test {i}")
    os.chdir(path)
