import matplotlib.pyplot as plt
import numpy as np
from eval_line import eval_line


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
        planets_X[i][index:index+3]=line[0:3]
    infile.readline()


#Plotter xy-positioner
for i in range(number_of_planets):
    index = int(i*3)
    plt.plot(planets_X[:,index],planets_X[:,index+1])
plt.show()
#plt.xlim(-10,10)
#plt.ylim(-10,10)
#plt.show()

#plt.plot(planets_X[:,3],planets_X[:,4])
#plt.show()



"""


#import numpy as np
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation

#plt.style.use('seaborn-pastel')


fig = plt.figure()
ax = p3.Axes3D(fig)

line, = ax.plot([], [],[], lw=3)
line2 = ax.plot([],[],[],lw=3)

def init():
    line.set_data([], [])
    line2 = set_data([],[])
    return line, line2
def animate(i):

    x1 = planets_X[:i,0]
    y1 = planets_X[:i,0+1]
    z1 = planets_X[:i,0+2]
    line.set_data(x1, y1)
    line.set_3d_properties(x1,z1)

    x2 = planets_X[:i,3]
    y2 = planets_X[:i,3+1]
    z2 = planets_X[:i,3+2]
    line2.set_data(x2, y2)
    line2.set_3d_properties(x2,z2)
    return line, line2,


ax.set_xlim3d([-10, 10])
ax.set_xlabel('X')

ax.set_ylim3d([-10, 10])
ax.set_ylabel('Y')

ax.set_zlim3d([-10, 10])
ax.set_zlabel('Z')

# Creating the Animation object

anim = FuncAnimation(fig, animate,frames=200, interval=20, blit=True)

#anim.save('growingCoil.mp4', writer = 'ffmpeg', fps = 30)
plt.show()


anim = []

# Animate the figures
for figcomps in [figcomps1,figcomps2]:
    fig,ax,line=figcomps
    anim.append(animation.FuncAnimation(fig,renderFrame,fargs=[line]))
"""
