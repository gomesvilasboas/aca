#!/bin/bash

kp=0.1
kd=0.15
max_it=100000
nb=10
r=1
label=1
pick=0.4
drop=0.3
n_ants=100
max_it=10000
nb=15
m=100
a=100
../bin/ACA ../dataset/4096_500.csv ${m} ${n_ants} ${max_it} ${nb} ${kp} ${kd} ${a} ${pick} ${drop} ${r} ${label} &> ../results/ACA.out
#gprof -b ./ACA ../results/gmon.out > ../results/ACA_4096_500.gprof
