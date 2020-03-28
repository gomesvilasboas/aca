#ifndef _TYPES_H_
#define _TYPES_H_

typedef struct Data
{
  int len;
  float *numeric;
  char **string;
} Data;

typedef struct Item
{
  double *value;
  int group;
  int item_id;
} Item;

typedef struct Cell
{
  Item item;
  int has_ant;
} Cell;

typedef struct Ant
{
  int x, y;
  Item item;
  int veloc;
} Ant;

#endif
