import matplotlib.pyplot as plt
import numpy as np
import sys

m = sys.argv[1]
n_ants =  sys.argv[2]
max_it = sys.argv[3]
nb = sys.argv[4]
kp = sys.argv[5]
kd = sys.argv[6]
a = sys.argv[7]
pick = sys.argv[8]
drop = sys.argv[9]
infile = sys.argv[10]

csv = np.genfromtxt (infile, delimiter="")
n = int(m)
aa = np.zeros((n,n))
for i in range(n):
  for j in range(n):
    aa[i,j] = csv[i*n + j]

plt.matshow(aa)
plt.show()
#title = "/home/fabricio/Documents/ACA/dataset_iris_m_" + m + "_ants_" + n_ants + "_maxit_" + max_it + "_nb_" + nb + "_kp_" + kp + "_kd_" + kd + "_a_" + a + "_pick_" + pick + "_drop_" + drop + ".png"
#plt.savefig(title)
