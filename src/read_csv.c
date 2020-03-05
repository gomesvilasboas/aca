#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

void unreference(Data *data, int n)
{
  int i;

  for(i = 0; i < n; i++)
  {
    data[i].numeric = NULL;
    data[i].string = NULL;
  }
}

int is_numeric(const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
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

Data *read_csv(char *filename, int *n_items)
{
  int n = get_number_of_lines(filename);
  Data *data = (Data*)malloc(sizeof(Data) * n);
  int numeric_count = 0, string_count = 0, string_count_total = 0, data_count = 0;
  FILE *file;
  char *line = NULL, *content = NULL;
  size_t len, string_size = sizeof(char);
  __ssize_t size;

  unreference(data, n);

  if ((file = fopen(filename, "r")) == NULL) exit(EXIT_FAILURE);

  while ((len = getline(&line, &size, file)) != -1)
  {
    numeric_count = 0;
    string_count = 0;
    content = strtok(line, " ");
    while (content != NULL)
    {
      if (is_numeric(content))
      {
        data[data_count].numeric = (float*)realloc(data[data_count].numeric, sizeof(float) * (numeric_count + 1));
        data[data_count].numeric[numeric_count] = atof(content);
        numeric_count++;
      }
      /*else
      {
        data[data_count].string = (char**)realloc(data[data_count].string, sizeof(char));
        data[data_count].string[string_count] = (char*)malloc(sizeof(content));
        strcpy(data[data_count].string[string_count], content);
        //string_size += sizeof(content) * (string_count_total + 1);
        //printf("%s, ", data[data_count].string[string_count]);
        string_count++;
        //string_count_total++;
      }*/
      content = strtok(NULL, " ");
    }
    data[data_count].len = numeric_count;
    data_count++;
    //puts("");
  }

  *n_items = data_count;
  return data;
}
