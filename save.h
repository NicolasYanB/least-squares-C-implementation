#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* serialize_parameters(double** parameters, int parameter_count) {
  int precision = 10;
  int size = (precision * parameter_count) + parameter_count;
  char num[precision];
  char* string = (char*)malloc(sizeof(char) * size);
  for (int i=0; i<parameter_count;i++) {
    snprintf(num, precision, "%.10f", parameters[i][0]);
    if (i == 0) {
      strcpy(string, num);
    } else {
      strcat(string, num);
    }
    strcat(string, "\n");
  }

  return string;
}

void save_to_file(char* serialized_values, char* filename) {
  FILE* fptr;
  fptr = fopen(filename, "w");
  fprintf(fptr, "%s", serialized_values);
  fclose(fptr);
}

#endif