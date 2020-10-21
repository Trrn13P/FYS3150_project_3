import numpy as np
import matplotlib.pyplot as plt
from eval_line import eval_line

infile = open("./data/test_energi.txt","r")
first_line = infile.readline()



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
