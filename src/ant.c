#include "aca.h"

int ant_has_item(Ant *ant)
{
  int res = (ant->item_id == -1) ? 0 : 1;
  return res;
}

double fpick(Cell **grid, Item *items, Ant *ant, const int nb, const int m, const int elements_per_item, const double a)
{
  int i, j;
  double sum = 0.0, r;

  for (i = ant->position.x - nb; i < ant->position.x + nb; i++)
    for (j = ant->position.y - nb; j < ant->position.y + nb; j++)
    {
      if (i >= 0 && i < m && j >= 0 && j < m)
      {
        if (cell_has_item(i, j, grid) == 1)
        {
          sum += 1 - (euclidian_distance(items[grid[ant->position.x][ant->position.y].item_id].numeric, items[grid[i][j].item_id].numeric, elements_per_item) / a);
          //sum += manhattan_distance(item_numeric, grid[i][j].item, s_items);
        }
      }
    }
    r = sum/(nb*nb);
    return (r > 0) ? r : 0;
}

double fdrop(Cell **grid, Item *items, Ant *ant, const int nb, const int m, const int elements_per_item, const double a)
{
  int i, j;
  double sum = 0.0, r;

  for (i = ant->position.x - nb; i < ant->position.x + nb; i++)
    for (j = ant->position.y - nb; j < ant->position.y + nb; j++)
    {
      if (i >= 0 && i < m && j >= 0 && j < m)
      {
        if (cell_has_item(i, j, grid) == 1)
        {
          sum += 1 - (euclidian_distance(items[ant->item_id].numeric, items[grid[i][j].item_id].numeric, elements_per_item) / a);
          //sum += manhattan_distance(item_numeric, grid[i][j].item, s_items);
        }
      }
    }
    r = sum/(nb*nb);
    return (r > 0) ? r : 0;
}

void ant_dynamic(Ant *ant, Cell **grid, Item *items, const int m, const int nb,
                 const int elements_per_item, const double kp, const double kd,
                 const double a, const double pick, const double drop)
{
  double pp, pd, fi;
  size_t size = sizeof(double)*elements_per_item;

  //Probability of the ant drop the item
  //printf("ant->x: %d, ant->y: %d\n", ant->position.x, ant->position.y);
  if (ant_has_item(ant) == 1 && cell_has_item(ant->position.x, ant->position.y, grid) == 0)
  {
    //puts("drop");
    fi = fdrop(grid, items, ant, nb, m, elements_per_item, a);
    //printf("fi = %.2f\n", fi);
    pd = (fi < kd) ? 2.0*fi : 1.0;
    //printf("pd = %.2f\n", pd);
    //fprintf(stderr, "\tDrop; pd: %f\n", pd);
    if (pd >= drop)
    {
      //printf("Largou . %d\n", ant->item_id);
      grid[ant->position.x][ant->position.y].item_id = ant->item_id;
      ant->item_id = -1;
      //fprintf(stdout, "\tDroped item %d on cell [%d, %d] with pd = %f.\n", grid[ant->x][ant->y].item_id, ant->x, ant->y, pd);
    }
    return;
  }

  // Probability of the ant pick the item
  if (ant_has_item(ant) == 0 && cell_has_item(ant->position.x, ant->position.y, grid) == 1)
  {
    //puts("pick");
    fi = fpick(grid, items, ant, nb, m, elements_per_item, a);
    //printf("fi = %.2f\n", fi);
    pp = powf(kp / (kp + fi), 2);
    //printf("pp = %.2f\n", pp);
    //fprintf(stderr, "\tPick; pp: %f\n", pp);
    if (pp >= pick)
    {
      ant->item_id = grid[ant->position.x][ant->position.y].item_id;
      grid[ant->position.x][ant->position.y].item_id = -1;
      //printf("Pegou . %d\n", ant->item_id);
      //fprintf(stdout, "\tPicked item %d on cell [%d, %d] with pp = %f.\n", ant->item_id, ant->x, ant->y, pp);
    }
    return;
  }
}

void move_ant(Ant *ant, Cell **grid, Item *items, const int m, const int nb,
              const int elements_per_item, const double kp, const double kd,
              const double a, const double pick, const double drop)
{
  int direction, moved = 0, stuck = 0, step = 5;

  do
  {
    direction = rand()%4;

    switch (direction)
    {
      case 0: // Move up [x-1,y];
        stuck += 1;
        if ((ant->position.x - step) >= 0)
        {
          if (grid[ant->position.x-step][ant->position.y].has_ant == 0)
          {
            grid[ant->position.x][ant->position.y].has_ant = 0;
            ant->position.x -= step;
            grid[ant->position.x][ant->position.y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 1: // Move down [x+1,y];
        stuck += 1;
        if ((ant->position.x + step) < m)
        {
          if (grid[ant->position.x+step][ant->position.y].has_ant == 0)
          {
            grid[ant->position.x][ant->position.y].has_ant = 0;
            ant->position.x += step;
            grid[ant->position.x][ant->position.y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 2: // Move right [x,y+1];
        stuck += 1;
        if ((ant->position.y + step) < m)
        {
          if (grid[ant->position.x][ant->position.y+1].has_ant == 0)
          {
            grid[ant->position.x][ant->position.y].has_ant = 0;
            ant->position.y += step;
            grid[ant->position.x][ant->position.y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 3: // Move left [x,y-1];
        stuck += 1;
        if ((ant->position.y - step) >= 0)
        {
          if (grid[ant->position.x][ant->position.y-step].has_ant == 0)
          {
            grid[ant->position.x][ant->position.y].has_ant = 0;
            ant->position.y -= step;
            grid[ant->position.x][ant->position.y].has_ant = 1;
            moved = 1;
          }
        }
      break;
    }
    ant_dynamic(ant, grid, items, m, nb, elements_per_item, kp, kd, a, pick, drop);
  } while(moved == 0 && stuck <= 4);
}
