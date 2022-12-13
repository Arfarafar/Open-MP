
import numpy as np
import matplotlib.pyplot as plt

x, y = np.loadtxt("naive_many.txt", delimiter=' ', unpack=True)

for i in range(len(x)):
    y[i]=8.15/y[i]

fig, ax = plt.subplots()
ax.scatter(x, y, color = "orange",  label = "")
plt.xticks([i for i in range(22)])
    
ax.set_xlabel("Treads")
ax.set_ylabel("Acceleration")
ax.grid()
plt.show()

