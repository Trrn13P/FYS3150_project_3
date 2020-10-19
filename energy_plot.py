import numpy as np
import matplotlib.pyplot as plt

infile = open("./data/test_energi.txt","r")
first_line = infile.readline()

def eval_line(line):
    line = line.split()
    new_line = []
    for i in line:
        new_line.append(eval(i))
    return new_line


infile.readline()
t = []
total_energy = []
for line in infile:
    #print(line)
    line = eval_line(line)
    t.append(line[0])
    total_energy.append(line[1])

plt.plot(t,total_energy)
plt.show()
