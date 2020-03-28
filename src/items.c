#include "aca.h"

Item* items_allocation(char *filename, int *number_of_items, int *elemts_per_item)
{
  Item *items, st;
  int i, j;

  //st = omp_get_wtime();
  Data *data = read_csv(filename, number_of_items);
  //printf("Reading time: %f\n", omp_get_wtime() - st);

  *elemts_per_item = data[0].len;
  size_t size = *elemts_per_item * sizeof(double);
  items = (Item*)malloc(*number_of_items * sizeof(Item));

  for (i = 0; i < *number_of_items; i++)
  {
      items[i].value = (double*)malloc(size);
      memcpy(items[i].value, data[i].numeric, size);
  }

   return items;
}

//void items_group(Cell **grid, int m)
//{
//  int i, j, group = 0;
//
//  for (i = 0; i < m; i++)
//  {
//    for (j = 0; j < m; j++)
//    {
//      if (cell_has_item(i,j, grid))
//      {
//        if (i > 0 && cell_has_item(i-1, j, grid))
//        {
//          grid[i][j].item.group = group;
//        }
//        else
//        {
//
//        }
//      }
//    }
//  }
//}
