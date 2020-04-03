# ACA

## Ant clustering algorithm

The ACA, Ant Clustering Algorithm, simulates the ants' behavior on the anthill cleaning. The main goal is to put similar objects together. On data analysis, this task is called data segmentation. Usually, it is the first class of algorithms used in data analysis. It can find specific patterns on the data.

Agent-based algorithms, like ACA, is a subclass of natural computing algorithms. Each ant is an independent agent performing simple tasks in a single environment. The final result is a consequence of the emerging behavior of all agents over time.
The contribution of this research is to develop a high-performance version of ACA for shared and distributed memory systems. We also propose a GPU-based version. All this development is under GNU General Public License v3.0.

This repository is organized as follows: serial version is on the master branch; the CUDA version in on the cuda branch; the OpenMP version is on the openmp branch, and the MPi version is on the mpi branch. (As you can see just the master branch exists. It is because all of the others are under development)
