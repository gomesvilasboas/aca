#ifndef _aca_h
#define _aca_h
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include "types.h"
#include "read_csv.h"

int ant_has_item(Ant *ant);
double f(Cell **B, double *item, const int x, const int y, const int nb, const int m, const int s_items, const double a);
void ant_dynamic(Ant *ant, Cell **B, const int m, const int nb, const int s_items,
                const double kp, const double kd, const double a,
                const double pick, const double drop);
void move_ant(Ant *ant, Cell **B, const int m, const int nb, const int s_items,
                const double kp, const double kd, const double a, const double pick,
                const double drop);
double manhattan_distance(double *item1, double *item2, const int n);
double euclidian_distance(double *item1, double *item2, const int n);
int cell_has_item(const int x, const int y, Cell **B);
Cell** grid_allocation(const int m);
double** items_allocation(char *filename, int *n_items, int *s_items);
void initialize(const int m, const int n_ants, const int n_items, const int s_items, Cell **B, Ant *ants, double **items);
void grid_print(Cell **B, const int m);

#endif