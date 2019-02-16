import numpy as np
import sys
import matplotlib.pyplot as plt

data = np.genfromtxt(sys.argv[1])

plt.plot(data[:,0],data[:,1],color = 'blue',label='voltage')
plt.plot(data[:,0],data[:,2],color = 'red',label='correction')
plt.xlabel('time in ms')
plt.show()