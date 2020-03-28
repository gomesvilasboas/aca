/*
Ant Colony Algorithm for clustering
Authors: Fabricio Vilasboas, Calebe Bianchini, Leandro Nunes
*/

#include "aca.h"

void simulate(Ant *ants, Cell **B, const int m, const int n_ants, const int nb,
            const int s_items, const int max_it, const double kp, const double kd,
            const double a, const double pick, const double drop)
{
  int it, ant;
  double ant_st, it_st, time = 0;

  for (it = 0; it < max_it; it++)
  {
    //it_st = omp_get_wtime();
    //#pragma omp parallel for
    for (ant = 0; ant < n_ants; ant++)
    {
      //ant_st = omp_get_wtime();
      move_ant(&ants[ant], B, m, nb, s_items, kp, kd, a, pick, drop);
      //printf("Ant %d time: %f\n", omp_get_wtime() - ant_st);
      //fprintf(stdout, "%d,%d,%d,%d,%d\n", it, ant, ants[ant].x, ants[ant].y, ants[ant].item_id);
    }
    //time += (omp_get_wtime() - it_st);
    //printf("Iteration %d time: %f\n", omp_get_wtime() - it_st);
  }
  //printf("Average execution time: %f\n", time/max_it);
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
  int m = atoi(argv[2]), number_of_ants = atoi(argv[3]), max_it = atoi(argv[4]), nb = atoi(argv[5]), number_of_items, elements_per_item;
  double kp = atof(argv[6]), kd = atof(argv[7]), a = atof(argv[8]), pick = atof(argv[9]), drop = atof(argv[10]);
  double st;
  // Ao inves de copiar o item para a formiga ou a grade, indicar apenas o indice de acesso dentro da estrutura
  Item *items = items_allocation(argv[1], &number_of_items, &elements_per_item);
  Cell **grid = grid_allocation(m);
  Ant *ants = (Ant*)malloc(number_of_ants * sizeof(Ant));
  srand(1);//time(NULL));
  initialize(m, number_of_ants, number_of_items, elements_per_item, grid, ants, items);
  simulate(ants, grid, m, number_of_ants, nb, elements_per_item, max_it, kp, kd, a, pick, drop);
  grid_print(grid, m);

  return 0;
}
