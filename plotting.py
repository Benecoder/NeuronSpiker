import numpy as np
import sys
import matplotlib.pyplot as plt


def image(data):
	fig,ax = plt.subplots()

	image = ax.imshow(data[1:])
	fig.colorbar(image)
	plt.show()

def graphs(data):

	#get legend
	FILE = open(sys.argv[1])
	legend = str(FILE.readline())
	FILE.close()
	labels = legend.split(' ')

	fig,ax = plt.subplots()
	for label_index in range(1,data.shape[0]):
		ax.plot(data[0],data[label_index],label=labels[label_index])


	ax.set_xlabel('time in ms')
	ax.legend(loc='lower right')
	plt.show()


if __name__ == '__main__':
	data = np.genfromtxt(sys.argv[1],skip_header=1).T
	image(data)
