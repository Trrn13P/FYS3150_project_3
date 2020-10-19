import matplotlib.pyplot as plt
import numpy as np

def eval_line(line):
    line = line.split()
    new_line = []
    for i in line:
        new_line.append(eval(i))
    return new_line

infile = open("./data/test.txt","r")
first_line = infile.readline().split()
number_of_planets = eval(first_line[0][18:])
N = eval(first_line[1][13:])


t = infile.readline().split()
infile.readline()
for i in range(len(t)):
    t[i] = eval(t[i])
t = np.asarray(t)


planets_X = np.zeros((N,number_of_planets*3))


for i in range(N):
    for j in range(number_of_planets):
        line = infile.readline()
        line = eval_line(line)
        index = int(j*3)
        #print(index)
        planets_X[i][index:index+3]=line[0:3]
    infile.readline()


#Plotter xy-positioner
for i in range(number_of_planets):
    index = int(i*3)
    plt.plot(planets_X[:,index],planets_X[:,index+1])

#plt.xlim(-10,10)
#plt.ylim(-10,10)
plt.show()
