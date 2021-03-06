import numpy as np
import sys
import matplotlib.pyplot as plt

data = np.genfromtxt(sys.argv[1],skip_header=1).T


#get legend
FILE = open(sys.argv[1])
legend = str(FILE.readline())
FILE.close()
labels = legend.split(' ')

fig,ax = plt.subplots()
for label_index in range(1,data.shape[0]):
	ax.plot(data[0],data[label_index],label=labels[label_index])



ax.set_xlabel('time in ms')
ax.legend(loc='lower left')
plt.show()