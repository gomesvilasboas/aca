#include "aca.h"

double manhattan_distance(double *item1, double *item2, const int n)
{
  int i;
  double sum = 0.0;
  for(i = 0; i < n; ++i)
  {
    sum += fabsf(item1[i]-item2[i]);
  }
  return sum/(double)n;
}

double euclidian_distance(double *item1, double *item2, const int n)
{
  int i;
  double sum = 0.0;

  for (i = 0; i < n; i++)
  {
    sum += pow(item1[i] - item2[i], 2);
  }
  return sqrt(sum/(double)n);
}