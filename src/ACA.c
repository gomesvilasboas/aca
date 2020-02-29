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
    n_items: number of items;
    s_items: number of elementes per item.
    pick:
    drop:
  */

  // A razão de proporcionalidade de m -> n_ants e n_items é de uma ordem de grandeza.
  int m = atoi(argv[2]), n_ants = atoi(argv[3]), max_it = atoi(argv[4]), nb = atoi(argv[5]), n_items, s_items;
  double kp = atof(argv[6]), kd = atof(argv[7]), a = atof(argv[8]), pick = atof(argv[9]), drop = atof(argv[10]);
  double **items;
  double st;
  Cell **B;
  Ant *ants = (Ant*)malloc(sizeof(Ant) * n_ants);
  srand(1);//time(NULL));
  //fprintf(stdout, "Allocating B\n");
  B = grid_allocation(m);
  //fprintf(stdout, "Allocating items\n");
  items = items_allocation(argv[1], &n_items, &s_items);
  //fprintf(stdout, "Initialize\n");
  initialize(m, n_ants, n_items, s_items, B, ants, items);
  //fprintf(stdout, "Simulate\n");
  simulate(ants, B, m, n_ants, nb, s_items, max_it, kp, kd, a, pick, drop);
  grid_print(B, m);

  return 0;
}
