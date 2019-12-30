#!/bin/bash

m=100
#./ACA filename m n_ants max_it nb kp kd a
./ACA ../dataset/iris.data ${m} 100 1000000 10 0.1 0.15 0.001 0.4 0.2 > ACA.out
python plot.py ${m} ACA.out
