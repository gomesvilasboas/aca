#ifndef _TYPES_H_
#define _TYPES_H_

typedef struct Item
{
  int len;
  double *numeric;
  char **string;
  int group;
} Item;

typedef struct Cell
{
  int item_id;
  int has_ant;
} Cell;

typedef struct Position
{
  int x;
  int y;
} Position;

typedef struct Ant
{
  Position position;
  int item_id;
  int veloc;
} Ant;

#endif
