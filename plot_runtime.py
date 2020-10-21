import numpy as np
import matplotlib.pyplot as plt
from eval_line import eval_line


infile = open("./data/runtimes.txt","r")

infile.readline()
infile.readline()

deltaT = []
Euler = []
Euler_cromer = []
Velocity_verlet = []
RK4 = []


for line in infile:
    line = eval_line(line)
    deltaT.append(line[0])
    Euler.append(line[1])
    Euler_cromer.append(line[2])
    Velocity_verlet.append(line[3])
    RK4.append(line[4])


plt.xlabel("$log_{10}$(yrs)",FontSize=14)
plt.ylabel(r"$log_{10}$(seconds)",FontSize=14)

plt.plot(np.log10(deltaT),np.log10(Euler),label="Euler")
plt.plot(np.log10(deltaT),np.log10(Euler_cromer),label="Euler-Cromer")
plt.plot(np.log10(deltaT),np.log10(Velocity_verlet),label="Velocity-Verlet")
plt.plot(np.log10(deltaT),np.log10(RK4),label="RK4")
plt.legend()
plt.savefig("./figures/runtimes.png")



infile.close()
