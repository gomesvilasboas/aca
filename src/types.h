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
