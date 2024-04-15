#include "read_csv.h"

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

int main() {
  RegressionData data = read_csv("data/diabetes_train.csv");
  double** model_matrix = data.model_matrix;
  double* observations = data.observations;
  int p = data.parameter_count;
  int y = data.observation_count;
  double** model_matrix_T = transpose(model_matrix, y, p);
  double** model_matrix_squared = multiply(model_matrix_T, p, y, model_matrix, y, p);
  return 0;
}


/*
[[1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]]

    X

[[3, 6, 9],
 [2, 5, 8],
 [1, 4, 7]]
*/