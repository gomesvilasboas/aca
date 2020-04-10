# ACA

## Ant clustering algorithm

The ACA, Ant Clustering Algorithm, simulates the ants' behavior on the anthill cleaning. The main goal is to put similar objects together. On data analysis, this task is called data segmentation. Usually, it is the first class of algorithms used in data analysis. It can find specific patterns on the data.

Agent-based algorithms, like ACA, is a subclass of natural computing algorithms. Each ant is an independent agent performing simple tasks in a single environment. The final result is a consequence of the emerging behavior of all agents over time.
The contribution of this research is to develop a high-performance version of ACA for shared and distributed memory systems. We also propose a GPU-based version. All this development is under GNU General Public License v3.0.

This repository is organized as follows: serial version is on the master branch; the CUDA version in on the cuda branch; the OpenMP version is on the openmp branch, and the MPi version is on the mpi branch. (As you can see just the master branch exists. It is because all of the others are under development)

## How to compile this project

There is a Makefile in src directory. Just clone this project and run make. Simple like this. Please be sure that you have g++ installed in you system.

## How to use

To use ACA you have to define some parameters. They are explained below:

Parameters:
  * dataset: input file in csv format
  * m: square grid size;
  * n_ants: number of ants;
  * max_it: max iterations;
  * nb: number of neighbors;
  * kp: threshold constant for pick (recommended is 0.1);
  * kd: threshold constant for drop (recommended is 0.15);
  * a: scale dimensional factor;
  * pick: probability of ant to pick an element (float in range of 0 ~ 1);
  * drop: probability of ant to drop an element (float in range of 0 ~ 1);
  * r: radius to be considered on cluster labeling;
  * label: to show a specific label (code change is necessary).

Putting this all together, we have:

 `./ACA dataset m n_ants max_it nb kp kd a pick drop r label`

And finally, there is a file in the src directory called run.sh that can facilitate the ACA usage.
