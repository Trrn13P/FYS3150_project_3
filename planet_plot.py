import matplotlib.pyplot as plt
import numpy as np

infile = open("./data/test.txt","r")
first_line = infile.readline().split()

number_of_planets = eval(first_line[0][-1])

t = infile.readline().split()
infile.readline()
for i in range(len(t)):
    t[i] = eval(t[i])
t = np.asarray(t)

planet1 = []
planet2 = []
#planet3 = []

def eval_expr(line):
    line = line.split()
    new_line = []
    for i in line:
        new_line.append(eval(i))
    return new_line


k = 0
for line in infile:
    if k==0:
        planet1.append(eval_expr(line))
    if k==1:
        planet2.append(eval_expr(line))
    if k==2:
        k=0
    else:
        k+=1

planet2 = np.asarray(planet2)
planet1 = np.asarray(planet1)

#print(planet1)
plt.plot(planet1[0:,0],planet1[0:,1])
plt.plot(planet2[0:,0],planet2[0:,1])
plt.show()
