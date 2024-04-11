#ifndef READ_CSV_H
#define READ_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 1000

typedef struct {
  double** model_matrix;
  double* observations;
} RegressionInfo;

static int count_lines(FILE* f) {
  int count = 0;
  char buffer[MAX_CHAR];
  while (!feof(f)) {
    fgets(buffer, MAX_CHAR, f);
    count++;
  }
  fseek(f, 0L, SEEK_SET);
  return count;
}

static char** get_lines(FILE* f, int line_count) {
  char** lines = (char**)malloc( sizeof(char*) * line_count);
  for(int i = 0; i < line_count - 1; i++) {
    lines[i] = (char*)malloc(sizeof(char) * MAX_CHAR + 1);
    fgets(lines[i], MAX_CHAR, f);
  }
  return lines;
}

static int count_parameters(char* first_line) {
  int parameters = 0;
  int char_idx = 0;
  char c = first_line[0];
  while (c != '\0') {
    if (c == ',') {
      parameters++;
    }
    char_idx++;
    c = first_line[char_idx];
  }
  return parameters - 1;
}

static double** get_matrix(char** raw_content, int line_count, int parameter_count) {
  int p;
  double value;
  double** parameters = (double**)malloc(sizeof(double*) * (line_count - 1));
  char line_content[MAX_CHAR];
  char* delim = ",";
  char* token;
  for (int line = 1; line < line_count - 1; line++) {
    p = line - 1;
    parameters[p] = (double*)malloc(sizeof(double) * (parameter_count + 1));
    strcpy(line_content, raw_content[line]);
    strtok(line_content, delim);
    parameters[p][0] = 1;
    for (int i = 0; i < parameter_count; i++) {
      token = strtok(NULL, delim);
      value = atof(token);
      parameters[p][i + 1] = value;
    }
  }
  return parameters;
}

double* get_observations(char** raw_content, int line_count, int parameter_count) {
  double* observations = (double*)malloc(sizeof(double) * (line_count - 1));
  double value;
  char* delim = ",";
  char line[MAX_CHAR];
  char* token;
  for (int i = 1; i < line_count - 1; i++) {
    strcpy(line, raw_content[i]);
    strtok(line, delim);
    for (int j = 0; j < parameter_count; j++) {
      token = strtok(NULL, delim);
    }
    token = strtok(NULL, delim);
    value = atof(token);
    observations[i - 1] = value;
  }
  return observations;
}

RegressionInfo read_csv(char* path) {
  FILE* fp;
  fp = fopen(path, "r");
  int lines = count_lines(fp);
  char** content = get_lines(fp, lines);
  int parameters = count_parameters(content[0]);
  double** model_matrix = get_matrix(content, lines, parameters);
  double* observations = get_observations(content, lines, parameters);
  RegressionInfo ri;
  ri.model_matrix = model_matrix;
  ri.observations = observations;
  return ri;
}

#endif