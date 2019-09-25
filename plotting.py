import numpy as np
import sys
import matplotlib.pyplot as plt

data = np.genfromtxt(sys.argv[1],skip_header=1).T


im_data = np.zeros((data.shape[1]//2,data.shape[1]//1))
for i in range(data.shape[0]):
	im_data[i*(data.shape[1]//2//data.shape[0]):(i+1)*(data.shape[1]//2//data.shape[0])] = data[i]

plt.imshow(im_data)
plt.show()

"""
#get legend
FILE = open(sys.argv[1])
legend = str(FILE.readline())
FILE.close()
labels = legend.split(' ')

fig,ax = plt.subplots()
for label_index in range(1,data.shape[0]):
	if label_index<6:
		ax.plot(data[0],data[label_index],label=labels[label_index],color='blue')
	else:
		ax.plot(data[0],data[label_index],label=labels[label_index],color='red')



ax.set_xlabel('time in ms')
ax.legend(loc='lower right')
plt.show()"""