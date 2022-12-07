
import numpy as np
import matplotlib.pyplot as plt

x, y = np.loadtxt("naive_many.txt", delimiter=' ', unpack=True)


fig, ax = plt.subplots()
ax.scatter(x, y, color = "orange",  label = "")
plt.xticks([i for i in range(21)])
    
ax.set_xlabel("Treads")
ax.set_ylabel("Time")
ax.grid()
ax.legend()
plt.show()

