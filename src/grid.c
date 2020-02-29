#include "aca.h"

int cell_has_item(const int x, const int y, Cell **B)
{
  int res = (B[x][y].item == NULL) ? 0 : 1;
  return res;
}

Cell** grid_allocation(const int m)
{
  Cell **B;
  int i, j;

  B = (Cell **)malloc(m * sizeof(Cell*));
  for(i = 0; i < m; i++) B[i] = (Cell*)malloc(m * sizeof(Cell));

  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
    {
      B[i][j].item = NULL;
      B[i][j].has_ant = 0;
      B[i][j].item_id = -1;
    }

  return B;
}

double** items_allocation(char *filename, int *n_items, int *s_items)
{
  double **items, st;
  int i, j;

  //st = omp_get_wtime();
  Data *data = read_csv(filename, n_items);
  //printf("Reading time: %f\n", omp_get_wtime() - st);

  *s_items = data[0].len;
  size_t size = *s_items*sizeof(double);
  items = (double**)malloc(*n_items * sizeof(double*));

  for (i = 0; i < *n_items; i++)
  {
      items[i] = (double*)malloc(size);
      memcpy(items[i], data[i].numeric, size);
  }

   return items;
}

/* Initialize grid with ants and items ramdomilly.
  In the first step ants are carryng no items.
*/
void initialize(const int m, const int n_ants, const int n_items, const int s_items, Cell **B, Ant *ants, double **items)
{
  int i = 0, j, x, y, ant_prob, item_prob;
  size_t size = sizeof(double)*s_items;

  // Initialize Cell with items
  do
  {
    x = rand()%m;
    y = rand()%m;
    if (cell_has_item(x, y, B) == 0 && B[x][y].has_ant == 0)
    {
      B[x][y].item = (double*)malloc(size);
      memcpy(B[x][y].item, items[i], size);
      B[x][y].item_id = i;
      i++;
    }
  } while(i != n_items);
  free(items);

  // Initialize Cell with ants
  i = 0;
  do
  {
    x = rand()%m;
    y = rand()%m;
    if (cell_has_item(x, y, B) == 0 && B[x][y].has_ant == 0)
    {
      ants[i].x = x;
      ants[i].y = y;
      ants[i].item = NULL;
      ants[i].item_id = -1;
      B[x][y].has_ant = 1;
      i++;
    }
  } while(i != n_ants);

}

void grid_print(Cell **B, const int m)
{
  int i, j;
  int has_item;
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < m; j++)
    {
      has_item = cell_has_item(i, j, B);
      fprintf(stdout, "%d\n", has_item);
      if (has_item)
      {
        //fprintf(stdout, "%d\n", B[i][j].item_id);
      }
      else
      {
        //fprintf(stdout, "%d\n", has_item);
      }
    }
  }
}