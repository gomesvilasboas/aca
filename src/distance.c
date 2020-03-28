#include "aca.h"

double manhattan_distance(double *item_value1, double *item_value2, const int n)
{
  int i;
  double sum = 0.0;
  for(i = 0; i < n; ++i)
  {
    sum += fabsf(item_value1[i]-item_value2[i]);
  }
  return sum/(double)n;
}

double euclidian_distance(double *item_value1, double *item_value2, const int n)
{
  int i;
  double sum = 0.0;

  for (i = 0; i < n; i++)
  {
    sum += pow(item_value1[i] - item_value2[i], 2);
  }
  return sqrt(sum/(double)n);
}
