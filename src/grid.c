#include "aca.h"

int cell_has_item(const int x, const int y, Cell **grid)
{
  int res = (grid[x][y].item_id == -1) ? 0 : 1;
  return res;
}

Cell** grid_allocation(const int m)
{
  Cell **grid;
  int i, j;

  grid = (Cell **)malloc(m * sizeof(Cell*));
  for(i = 0; i < m; i++) grid[i] = (Cell*)malloc(m * sizeof(Cell));

  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
    {
      grid[i][j].item_id = -1;
      grid[i][j].has_ant = 0;
    }

  return grid;
}

/* Initialize grid with ants and items ramdomilly.
  In the first step ants are carryng no items.
*/
void initialize(const int m, const int number_of_ants, const int number_of_items, const int elements_per_item, Cell **grid, Ant *ants, Item *items)
{
  int i = 0, j, x, y, ant_prob, item_prob;
  size_t size = sizeof(double)*elements_per_item;

  // Initialize Cell with items
  do
  {
    x = rand()%m;
    y = rand()%m;
    if (cell_has_item(x, y, grid) == 0 && grid[x][y].has_ant == 0)
    {
      grid[x][y].item_id = i;
      i++;
    }
  } while(i != number_of_items);
  free(items);

  // Initialize Cell with ants
  i = 0;
  do
  {
    x = rand()%m;
    y = rand()%m;
    if (cell_has_item(x, y, grid) == 0 && grid[x][y].has_ant == 0)
    {
      ants[i].position.x = x;
      ants[i].position.y = y;
      ants[i].item_id = -1;
      grid[x][y].has_ant = 1;
      i++;
    }
  } while(i != number_of_ants);
}

void grid_print(Cell **grid, const int m)
{
  int i, j;
  int has_item;
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < m; j++)
    {
      has_item = cell_has_item(i, j, grid);
      fprintf(stdout, "%d\n", has_item);
      if (has_item)
      {
        //fprintf(stdout, "%d\n", grid[i][j].item_id);
      }
      else
      {
        //fprintf(stdout, "%d\n", has_item);
      }
    }
  }
}
