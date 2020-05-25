/*
Ant Colony Algorithm for clustering
Authors: Fabricio Vilasboas, Calebe Bianchini, Leandro Nunes
*/

#include "aca.h"

void simulate(Ant *ants, Cell **grid, Item *items, const int m, const int number_of_ants,
              const int nb, const int elements_per_item, const int max_it, const double kp,
              const double kd, const double a, const double pick, const double drop)
{
  int it, ant;
  double ant_st, it_st, time = 0;

  for (it = 0; it < max_it; it++)
  {
    //it_st = omp_get_wtime();
    //#pragma omp parallel for
    for (ant = 0; ant < number_of_ants; ant++)
    {
      //ant_st = omp_get_wtime();
      move_ant(&ants[ant], grid, items, m, nb, elements_per_item, kp, kd, a, pick, drop);
      //printf("Ant %d time: %f\n", omp_get_wtime() - ant_st);
      //fprintf(stdout, "%d,%d,%d,%d,%d\n", it, ant, ants[ant].x, ants[ant].y, ants[ant].item_id);
    }
    //time += (omp_get_wtime() - it_st);
    //printf("Iteration %d time: %f\n", omp_get_wtime() - it_st);
  }
  //printf("Average execution time: %f\n", time/max_it);
}

void terminate(Ant *ants, Cell **grid, int number_of_ants)
{
  int i;

  for (i = 0; i < number_of_ants; i++)
    if(ant_has_item(&ants[i]))
      grid[ants[i].position.x][ants[i].position.y].item_id = ants[i].item_id;
}

int main (int argc, char **argv)
{
  /*
  Variables clarification:
    m: square grid size;
    n_ants: number of ants;
    max_it: max iterations;
    nb: number of neighbors;
    kp: threshold constant defined by the user;
    kd: threshold constant defined by the user;
    a: scale dimensionality factor
    f: perceived fraction of items;
    B: grid of cells;
    ants: vector of ants;
    items: matrix of items;
    number_of_items: number of items;
    elemts_per_items: number of elementes per item.
    pick: probability of pick an element
    drop: probability of drop an element
  */

  // A razão de proporcionalidade de m -> n_ants e n_items é de uma ordem de grandeza.
  // A grade nao necessariamente tem que ser quadrada. Fazer essa alteracao
  int m = atoi(argv[2]), number_of_ants = atoi(argv[3]), max_it = atoi(argv[4]),
      nb = atoi(argv[5]), r = atoi(argv[11]), label = atoi(argv[12]),
      number_of_items, elements_per_item, number_of_groups;
  double kp = atof(argv[6]), kd = atof(argv[7]), a = atof(argv[8]), pick = atof(argv[9]), drop = atof(argv[10]);
  double st;
  puts("\n\tRunning!\n");
  Item *items = read_csv(argv[1], &number_of_items);
  Cell **grid = grid_allocation(m);
  Ant *ants = (Ant*)malloc(number_of_ants * sizeof(Ant));
  srand(1);//time(NULL));
  elements_per_item = items[0].len;
  initialize(m, number_of_ants, number_of_items, elements_per_item, grid, ants);
  simulate(ants, grid, items, m, number_of_ants, nb, elements_per_item, max_it, kp, kd, a, pick, drop);
  terminate(ants, grid, number_of_ants);
  //grid_print(grid, m);
  number_of_groups = label_items(grid, m, items, r);
  //printf("Number of groups: %d\n", number_of_groups);
  //print_items_label(items, number_of_items);
  //for (int i = 1; i <= number_of_groups; i++)
  //{
  //  printf("\t\tGroup -> %d\n", i);
  //  print_items_label(items, number_of_items, i);
  //}
  puts("\n\tRunned!\n");

  return 0;
}
