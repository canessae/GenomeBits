#!/usr/bin/env python
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

import numpy as np
import matplotlib.pyplot as plt


######################################################
######################################################
#### Number of sample points GENOMA: (ACGT)

data4 = np.loadtxt("tmp-sums/A-sum01-complete.dat")
x4 = data4[:,0]    
y4 = data4[:,1]    
n4 = x4.size

data5 = np.loadtxt("tmp-sums/C-sum01-complete.dat")
y5 = data5[:,1]    

data6 = np.loadtxt("tmp-sums/G-sum01-complete.dat")
y6 = data6[:,1]    

data7 = np.loadtxt("tmp-sums/T-sum01-complete.dat")
y7 = data7[:,1]    


plt.plot(x4, y4, marker='o', mec='none', ms=1, lw=1, label='A-sum01-complete.dat')
plt.plot(x4, y5, marker='o', mec='none', ms=1, lw=1, label='C-sum01-complete.dat')
plt.plot(x4, y6, marker='o', mec='none', ms=1, lw=1, label='G-sum01-complete.dat')
plt.plot(x4, y7, marker='o', mec='none', ms=1, lw=0.1, label='T-sum01-complete.dat')

plt.legend(frameon=True, fontsize=10, numpoints=100, loc='upper left')
plt.savefig('tmp-sums/ACGT-complete-curves.png', dpi=200)


######################################################
######################################################




