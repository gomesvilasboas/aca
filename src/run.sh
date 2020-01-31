#!/bin/bash

m=100
#./ACA     filename        m     n_ants  max_it  nb  kp   kd    a      pick  drop
./ACA ../dataset/iris.data ${m}  100     10000   10  0.1  0.15  10000  0.3   0.2  > ACA.out
python plot.py ${m} ACA.out

ruspine
