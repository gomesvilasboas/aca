#include "aca.h"

int ant_has_item(Ant *ant)
{
  int res = (ant->item == NULL) ? 0 : 1;
  return res;
}

double f(Cell **B, double *item, const int x, const int y, const int nb, const int m, const int s_items, const double a)
{
  int i, j;
  double sum = 0.0, r;
  for (i = x - nb; i < x + nb; i++)
    for (j = y - nb; j < y + nb; j++)
    {
      if (i >= 0 && i < m && j >= 0 && j < m)
      {
        if (cell_has_item(i, j, B) == 1)
        {
          sum += 1 - (euclidian_distance(item, B[i][j].item, s_items) / a);
          //sum += manhattan_distance(item, B[i][j].item, s_items);
        }
      }
    }
    r = sum/(nb*nb);
    return (r > 0) ? r : 0;
}

void ant_dynamic(Ant *ant, Cell **B, const int m, const int nb, const int s_items,
                 const double kp, const double kd, const double a,
                 const double pick, const double drop)
{
  double pp, pd, fi;
  size_t size = sizeof(double)*s_items;

  //Probability of the ant drop the item
  if (ant_has_item(ant) == 1 && cell_has_item(ant->x, ant->y, B) == 0)
  {
    fi = f(B, ant->item, ant->x, ant->y, nb, m, s_items, a);
    //printf("fi = %.2f\n", fi);
    pd = (fi < kd) ? 2.0*fi : 1.0;
    //printf("pd = %.2f\n", pd);
    //fprintf(stderr, "\tDrop; pd: %f\n", pd);
    if (pd >= drop)
    {
      //printf("Largou -> %d\n", ant->item_id);
      B[ant->x][ant->y].item = (double*)malloc(size);
      memcpy(B[ant->x][ant->y].item, ant->item, size);
      free(ant->item);
      ant->item = NULL;
      B[ant->x][ant->y].item_id = ant->item_id;
      ant->item_id = -1;
      //fprintf(stdout, "\tDroped item %d on cell [%d, %d] with pd = %f.\n", B[ant->x][ant->y].item_id, ant->x, ant->y, pd);
    }
    return;
  }

  // Probability of the ant pick the item
  if (ant_has_item(ant) == 0 && cell_has_item(ant->x, ant->y, B) == 1)
  {
    fi = f(B, B[ant->x][ant->y].item, ant->x, ant->y, nb, m, s_items, a);
    //printf("fi = %.2f\n", fi);
    pp = powf(kp / (kp + fi), 2);
    //printf("pp = %.2f\n", pp);
    //fprintf(stderr, "\tPick; pp: %f\n", pp);
    if (pp >= pick)
    {
      ant->item = (double*)malloc(size);
      memcpy(ant->item, B[ant->x][ant->y].item, size);
      free(B[ant->x][ant->y].item);
      B[ant->x][ant->y].item = NULL;
      ant->item_id = B[ant->x][ant->y].item_id;
      B[ant->x][ant->y].item_id = -1;
      //printf("Pegou -> %d\n", ant->item_id);
      //fprintf(stdout, "\tPicked item %d on cell [%d, %d] with pp = %f.\n", ant->item_id, ant->x, ant->y, pp);
    }
    return;
  }
}

void move_ant(Ant *ant, Cell **B, const int m, const int nb, const int s_items,
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
          if (B[ant->x-step][ant->y].has_ant == 0)
          {
            B[ant->x][ant->y].has_ant = 0;
            ant->x -= step;
            B[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 1: // Move down [x+1,y];
        stuck += 1;
        if ((ant->x + step) < m)
        {
          if (B[ant->x+step][ant->y].has_ant == 0)
          {
            B[ant->x][ant->y].has_ant = 0;
            ant->x += step;
            B[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 2: // Move right [x,y+1];
        stuck += 1;
        if ((ant->y + step) < m)
        {
          if (B[ant->x][ant->y+1].has_ant == 0)
          {
            B[ant->x][ant->y].has_ant = 0;
            ant->y += step;
            B[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
      case 3: // Move left [x,y-1];
        stuck += 1;
        if ((ant->y - step) >= 0)
        {
          if (B[ant->x][ant->y-step].has_ant == 0)
          {
            B[ant->x][ant->y].has_ant = 0;
            ant->y -= step;
            B[ant->x][ant->y].has_ant = 1;
            moved = 1;
          }
        }
      break;
    }
    ant_dynamic(ant, B, m, nb, s_items, kp, kd, a, pick, drop);
  } while(moved == 0 && stuck <= 4);
}
