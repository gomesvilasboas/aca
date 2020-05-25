#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

#pragma acc routine vector
void unreference(Item *items, int n)
{
  int i;

  for(i = 0; i < n; i++)
  {
    items[i].numeric = NULL;
    items[i].string = NULL;
  }
}

#pragma acc routine seq
double is_numeric(const char *s)
{
  if (s == NULL || *s == '\0' || isspace(*s))
    return (double)0;
  char *p;
  return strtod (s, &p);;
}

int get_number_of_lines(char *fileName)
{
   char temp[64], cmd[512];
   FILE  *in;
   strcpy(cmd, "wc -l ");
   strcat(cmd, fileName);
   in = popen(cmd, "r");
   fgets(temp, 64, in);
   fclose(in);
   return atoi(temp);
}

Item *read_csv(char *filename, int *n_items)
{
  int n = get_number_of_lines(filename);
  Item *items = (Item*)malloc(sizeof(Item) * n);
  int numeric_count = 0, string_count = 0, string_count_total = 0, items_count = 0;
  FILE *file;
  char *line = NULL, *content = NULL;
  size_t len, string_size = sizeof(char);
  size_t size;

  unreference(items, n);

  if ((file = fopen(filename, "r")) == NULL) exit(EXIT_FAILURE);

  while ((len = getline(&line, &size, file)) != -1)
  {
    numeric_count = 0;
    string_count = 0;
    content = strtok(line, ",");
    while (content != NULL)
    {
      if (is_numeric(content))
      {
        items[items_count].numeric = (double*)realloc(items[items_count].numeric, sizeof(double) * (numeric_count + 1));
        items[items_count].numeric[numeric_count] = atof(content);
        numeric_count++;
      }
      /*else
      {
        items[items_count].string = (char**)realloc(items[items_count].string, sizeof(char));
        items[items_count].string[string_count] = (char*)malloc(sizeof(content));
        strcpy(items[items_count].string[string_count], content);
        //string_size += sizeof(content) * (string_count_total + 1);
        //printf("%s, ", items[items_count].string[string_count]);
        string_count++;
        //string_count_total++;
      }*/
      content = strtok(NULL, ",");
    }
    items[items_count].len = numeric_count;
    items[items_count].label = -1;
    items_count++;
  }

  *n_items = items_count;
  return items;
}
