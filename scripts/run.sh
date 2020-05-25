#!/bin/bash

kp=0.1
kd=0.15
max_it=100000
nb=10
r=1
label=1

for pick in 0.2 0.3 0.4 0.5 0.6; do
  for drop in 0.2 0.3 0.4 0.5 0.6; do
    for n_ants in {40..101..20}; do
      for max_it in {100000..1000000..100000}; do
        for nb in {5..15..5}; do
          for m in {40..101..20}; do
            for a in 100; do
              ./ACA ../dataset/ruspini.csv ${m} ${n_ants} ${max_it} ${nb} ${kp} ${kd} ${a} ${pick} ${drop} ${r} ${label} > ACA.out
              python plot.py ${m} ${n_ants} ${max_it} ${nb} ${kp} ${kd} ${a} ${pick} ${drop} ACA.out
            done
          done
        done
      done
    done
  done
done

#./ACA ../dataset/iris.data 100 50 100000 5 ${kp} ${kd} 1 0.4 0.2 > ACA.out
