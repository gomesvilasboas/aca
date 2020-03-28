#!/bin/bash

m=100
#./ACA  filename            m     n_ants  max_it  nb  kp   kd    a    pick  drop
./ACA   ../dataset/iris.data ${m}  70      100000  15  0.1  0.15  100  0.4   0.3  > ACA.out
python plot.py ${m} ACA.out
