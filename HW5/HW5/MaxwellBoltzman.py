import matplotlib.pyplot as plt
import numpy as np
from lmfit import  Model

dir="./"
file="Velocities.dat"

def MBvel(v, amp, T):
    "Maxwell-Boltzman: MBvel(x, amp, cen, wid)"
    return (amp*v) * np.exp(-(v)**2 /(2*T))

velocities = np.loadtxt(dir+file, dtype=np.float)
num_bins=100

(y,edges) = np.histogram(velocities, num_bins, normed=1)

x = np.array(range(0,edges.size-1),dtype=np.float)
for i in range(0,edges.size-1):
    x[i] = (edges[i]+edges[i+1])/2.0

gmod = Model(MBvel)
result = gmod.fit(y, v=x, amp=1, T=0.5)

print(result.fit_report())

plt.plot(x, y,         'bo')
plt.plot(x, result.best_fit, 'r-')
plt.title("Histogram of Velocities")
plt.xlabel("Velocity")
plt.ylabel("Probability")

plt.show()
