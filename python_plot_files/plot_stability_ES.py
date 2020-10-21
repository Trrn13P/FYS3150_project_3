import numpy as np
import matplotlib.pyplot as plt
from eval_line import eval_line

infile = open("../data/stability.txt","r")

infile.readline()
line = infile.readline().split()

k_0 = eval(line[5])
u_0 = eval(line[6])
e_0 = eval(line[7])
line = infile.readline().split()
E_0 = eval(line[-1])
infile.readline()
infile.readline()


deltaT = []

Euler_K = []
Euler_U = []
Euler_e = []
Euler_E = []

Euler_cromer_K = []
Euler_cromer_U = []
Euler_cromer_e = []
Euler_cromer_E = []

Velocity_verlet_K = []
Velocity_verlet_U = []
Velocity_verlet_e = []
Velocity_verlet_E = []

RK4_K = []
RK4_U = []
RK4_e = []
RK4_E = []

for line in infile:
    line = eval_line(line)
    deltaT.append(line[0])
    Euler_K.append(line[1]/k_0)
    Euler_U.append(line[2]/u_0)
    Euler_e.append(line[3]/e_0)
    Euler_E.append(line[4]/E_0)
    Euler_cromer_K.append(line[5]/k_0)
    Euler_cromer_U.append(line[6]/u_0)
    Euler_cromer_e.append(line[7]/e_0)
    Euler_cromer_E.append(line[8]/E_0)
    Velocity_verlet_K.append(line[9]/k_0)
    Velocity_verlet_U.append(line[10]/u_0)
    Velocity_verlet_e.append(line[11]/e_0)
    Velocity_verlet_E.append(line[12]/E_0)
    RK4_K.append(line[13]/k_0)
    RK4_U.append(line[14]/u_0)
    RK4_e.append(line[15]/e_0)
    RK4_E.append(line[16]/E_0)
infile.close()

"""
plt.xlabel("deltaT [yrs]")
plt.ylabel("K/K_0")
plt.plot(np.log10(deltaT),Euler_K,label="Euler")
plt.plot(np.log10(deltaT),Euler_cromer_K,label="Euler-Cromer")
plt.plot(np.log10(deltaT),Velocity_verlet_K,label="Velocity-Verlet")
plt.plot(np.log10(deltaT),RK4_K,label="RK4")
plt.legend()
plt.show()



plt.xlabel("deltaT [yrs]")
plt.ylabel(r"$U/U_0$")
plt.plot(np.log10(deltaT),Euler_U,label="Euler")
plt.plot(np.log10(deltaT),Euler_cromer_U,label="Euler-Cromer")
plt.plot(np.log10(deltaT),Velocity_verlet_U,label="Velocity-Verlet")
plt.plot(np.log10(deltaT),RK4_U,label="RK4")
plt.legend()
plt.show()

plt.xlabel("deltaT [yrs]")
plt.ylabel(r"$e/e_0$")
plt.plot(np.log10(deltaT),Euler_e,label="Euler")
plt.plot(np.log10(deltaT),Euler_cromer_e,label="Euler-Cromer")
plt.plot(np.log10(deltaT),Velocity_verlet_e,label="Velocity-Verlet")
plt.plot(np.log10(deltaT),RK4_e,label="RK4")
plt.legend()
plt.show()

"""
plt.xlabel("deltaT [yrs]",FontSize=14)
plt.ylabel(r"$E/E_0$",FontSize=14)
plt.plot(np.log10(deltaT),Euler_E,label="Euler")
plt.plot(np.log10(deltaT),Euler_cromer_E,label="Euler-Cromer")
plt.plot(np.log10(deltaT),Velocity_verlet_E,label="Velocity-Verlet")
plt.plot(np.log10(deltaT),RK4_E,label="RK4")
plt.legend()
plt.savefig("../figures/stability_ES.png")
