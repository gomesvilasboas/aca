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

int ant_has_item(Ant *ant);
double f(Cell **grid, Item *items, Ant *ant, const int nb, const int m, const int elements_per_item, const double a);
void ant_dynamic(Ant *ant, Cell **grid, Item *items, const int m, const int nb,
                 const int elements_per_item, const double kp, const double kd,
                 const double a, const double pick, const double drop);
void move_ant(Ant *ant, Cell **grid, Item *items, const int m, const int nb,
              const int elements_per_item, const double kp, const double kd,
              const double a, const double pick, const double drop);
double manhattan_distance(double *item_value1, double *item_value2, const int n);
double euclidian_distance(double *item_Value1, double *item_value2, const int n);
int cell_has_item(const int x, const int y, Cell **grid);
Cell** grid_allocation(const int m);
Item* items_allocation(char *filename, int *number_of_items, int *elements_per_item);
void initialize(const int m, const int number_of_ants, const int number_of_items, const int elements_per_item, Cell **grid, Ant *ants);
void grid_print(Cell **grid, const int m);
Item *read_csv(char *filename, int *n_items);

#endif
