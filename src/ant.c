#include "aca.h"

int ant_has_item(Ant *ant)
{
  int res = (ant->item.value == NULL) ? 0 : 1;
  return res;
}

double f(Cell **grid, double *item_value, const int x, const int y, const int nb, const int m, const int elements_per_item, const double a)
{
  int i, j;
  double sum = 0.0, r;
  for (i = x - nb; i < x + nb; i++)
    for (j = y - nb; j < y + nb; j++)
    {
      if (i >= 0 && i < m && j >= 0 && j < m)
      {
        if (cell_has_item(i, j, grid) == 1)
        {
          sum += 1 - (euclidian_distance(item_value, grid[i][j].item.value, elements_per_item) / a);
          //sum += manhattan_distance(item_value, grid[i][j].item, s_items);
        }
      }
    }
    r = sum/(nb*nb);
    return (r > 0) ? r : 0;
}

void ant_dynamic(Ant *ant, Cell **grid, const int m, const int nb, const int elements_per_item,
                 const double kp, const double kd, const double a,
                 const double pick, const double drop)
{
  double pp, pd, fi;
  size_t size = sizeof(double)*elements_per_item;

  //Probability of the ant drop the item
  if (ant_has_item(ant) == 1 && cell_has_item(ant->x, ant->y, grid) == 0)
  {
    fi = f(grid, ant->item.value, ant->x, ant->y, nb, m, elements_per_item, a);
    //printf("fi = %.2f\n", fi);
    pd = (fi < kd) ? 2.0*fi : 1.0;
    //printf("pd = %.2f\n", pd);
    //fprintf(stderr, "\tDrop; pd: %f\n", pd);
    if (pd >= drop)
    {
      //printf("Largou -> %d\n", ant->item_id);
      grid[ant->x][ant->y].item.value = (double*)malloc(size);
      memcpy(grid[ant->x][ant->y].item.value, ant->item.value, size);
      free(ant->item.value);
      ant->item.value = NULL;
      grid[ant->x][ant->y].item.item_id = ant->item.item_id;
      ant->item.item_id = -1;
      //fprintf(stdout, "\tDroped item %d on cell [%d, %d] with pd = %f.\n", grid[ant->x][ant->y].item_id, ant->x, ant->y, pd);
    }
    return;
  }

  // Probability of the ant pick the item
  if (ant_has_item(ant) == 0 && cell_has_item(ant->x, ant->y, grid) == 1)
  {
    fi = f(grid, grid[ant->x][ant->y].item.value, ant->x, ant->y, nb, m, elements_per_item, a);
    //printf("fi = %.2f\n", fi);
    pp = powf(kp / (kp + fi), 2);
    //printf("pp = %.2f\n", pp);
    //fprintf(stderr, "\tPick; pp: %f\n", pp);
    if (pp >= pick)
    {
      ant->item.value = (double*)malloc(size);
      memcpy(ant->item.value, grid[ant->x][ant->y].item.value, size);
      free(grid[ant->x][ant->y].item.value);
      grid[ant->x][ant->y].item.value = NULL;
      ant->item.item_id = grid[ant->x][ant->y].item.item_id;
      grid[ant->x][ant->y].item.item_id = -1;
      //printf("Pegou -> %d\n", ant->item_id);
      //fprintf(stdout, "\tPicked item %d on cell [%d, %d] with pp = %f.\n", ant->item_id, ant->x, ant->y, pp);
    }
    return;
  }
}

void move_ant(Ant *ant, Cell **grid, const int m, const int nb, const int elements_per_item,
              const double kp, const double kd, const double a, const double pick,
              const double drop)
{
  int direction, moved = 0, stuck = 0, step = 5;

  do
  {
    direction = rand()%4;

    switch (direction)
    {
      case 0: // Move up [x-1,y];
        stuck += 1;
        if ((ant->x - step) >= 0)
        {
          if (grid[ant->x-step][ant->y].has_ant == 0)
          {
            grid[ant->x][ant->y].has_ant = 0;
            ant->x -= step;
            grid[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 1: // Move down [x+1,y];
        stuck += 1;
        if ((ant->x + step) < m)
        {
          if (grid[ant->x+step][ant->y].has_ant == 0)
          {
            grid[ant->x][ant->y].has_ant = 0;
            ant->x += step;
            grid[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 2: // Move right [x,y+1];
        stuck += 1;
        if ((ant->y + step) < m)
        {
          if (grid[ant->x][ant->y+1].has_ant == 0)
          {
            grid[ant->x][ant->y].has_ant = 0;
            ant->y += step;
            grid[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 3: // Move left [x,y-1];
        stuck += 1;
        if ((ant->y - step) >= 0)
        {
          if (grid[ant->x][ant->y-step].has_ant == 0)
          {
            grid[ant->x][ant->y].has_ant = 0;
            ant->y -= step;
            grid[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
    }
    ant_dynamic(ant, grid, m, nb, elements_per_item, kp, kd, a, pick, drop);
  } while(moved == 0 && stuck <= 4);
}
