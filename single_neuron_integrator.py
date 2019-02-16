import numpy as np
import sys
import matplotlib.pyplot as plt

data = np.genfromtxt(sys.argv[1])

plt.plot(data[:,0],data[:,1])
plt.plot(data[:,0],data[:,2])

plt.show()