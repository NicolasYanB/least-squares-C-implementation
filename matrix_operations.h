#ifndef MATRIX_OP_H
#define MATRIX_OP_H

#include <stdlib.h>

double** transpose(double** matrix, int lines, int columns) {
  double** transposed = (double**)malloc(sizeof(double*) * columns);
  for (int i = 0; i < columns; i++) {
    transposed[i] = (double*)malloc(sizeof(double) * lines);
    for (int j = 0; j < lines; j++) {
      transposed[i][j] = matrix[j][i];
    }
  }
  return transposed;
}

double** multiply(double** matrix1, int lines1, int columns1, double** matrix2, int lines2, int columns2) {
  double** result = (double**)malloc(sizeof(double*) * lines1);
  double x, y;
  for (int a = 0; a < lines1; a++) {
    result[a] = (double*)malloc(sizeof(double) * columns2);
    for (int b = 0; b < columns2; b++) {
      result[a][b] = 0;
      for (int c = 0; c < lines2; c++) {
        x = matrix1[a][c];
        y = matrix2[c][b];
        result[a][b] += x * y;
      }
    }
  }
  return result;
}

static double** get_indentity(int size) {
  double** identity = (double**)malloc(sizeof(double*) * size);
  for (int i=0; i<size; i++){
    identity[i] = (double*)malloc(sizeof(double) * size);
  }

  for (int i=0; i<size; i++){
    for (int j=0; j<size; j++) {
      if (i == j) {
        identity[i][j] = 1;
        continue;
      }
      identity[i][j] = 0;
    }
  }

  return identity;
}

double** inverse(double** matrix, int size) {
  double** identity = get_indentity(size);
  double value;
  for (int k=0; k<size; k++){
    value = matrix[k][k];
    for (int j=0; j<size; j++){
      matrix[k][j] /= value;
      identity[k][j] /= value;
    }
    for (int i=0; i<size; i++) {
      value = matrix[i][k];
      for (int j=0; j<size; j++) {
        if (i==k) break;
        matrix[i][j] -= matrix[k][j]*value;
        identity[i][j] -= identity[k][j]*value;
      }
    }
  }
  return identity;
}

#endif