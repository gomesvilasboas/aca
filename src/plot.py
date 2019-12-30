import matplotlib.pyplot as plt
import numpy as np
import sys

n = int(sys.argv[1])

csv = np.genfromtxt (sys.argv[2], delimiter="")

aa = np.zeros((n,n))
for i in range(n):
  for j in range(n):
    aa[i,j] = csv[i*n + j]

plt.matshow(aa)
plt.show()
