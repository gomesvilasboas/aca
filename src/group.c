#include "aca.h"

int label_items(Cell **grid, int m, Item *items, int r)
{
  int i, j, k, l, group_id = 0, change_group = 0, item_grouped = 0;

  for (i = 0; i < m; i++)
  {
    for (j = 0; j < m; j++)
    {
      item_grouped = 0;
      if (cell_has_item(i, j, grid))
      {
        for (k = i-r; k < i+r; k++)
        {
          for (l = j-r; l < j+r; l++)
          {
            if (k >= 0 && k < m && l >= 0 && l < m)
            {
              if (cell_has_item(k, l, grid) && items[grid[k][l].item_id].label != -1)
              {
                items[grid[i][j].item_id].label = items[grid[k][l].item_id].label;
                item_grouped = 1;
              }
              if (item_grouped == 1)
              {
                break;
              }
            }
          }// End for l
        } // End for k
        if (item_grouped == 0)
        {
          group_id++;
          items[grid[i][j].item_id].label = group_id; // First group's element
        }
      }// End if cell_has_item
    }// End for j
  }// End for i

  return group_id;
}

void print_items_label(Item *items, int number_of_items)
{
  int i;

  for(i = 0; i < number_of_items; i++)
    printf("Item[%d].label = %d\n", i, items[i].label);
}

void print_items_label(Item *items, int number_of_items, int label)
{
  int i;

  for(i = 0; i < number_of_items; i++)
    if (items[i].label == label)
      printf("Item[%d].label = %d\n", i, items[i].label);
}
