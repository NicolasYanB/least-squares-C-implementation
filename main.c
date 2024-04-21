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

double** get_indentity(int size) {
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

int main() {
  RegressionData data = read_csv("data/diabetes_train.csv");
  double** model_matrix = data.model_matrix;
  double* observations = data.observations;
  int p = data.parameter_count;
  int y = data.observation_count;
  double** model_matrix_T = transpose(model_matrix, y, p);
  double** model_matrix_squared = multiply(model_matrix_T, p, y, model_matrix, y, p);
  double** inversed_model_matrix_squared = inverse(model_matrix_squared, p);
  double** final_model_matrix = multiply(inversed_model_matrix_squared, p, p, model_matrix_T, p, y);
  double** observations_matrix = malloc(sizeof(double*));
  observations_matrix[0] = observations;
  double** model_parameters = multiply(final_model_matrix, p, y, transpose(observations_matrix, 1, y), y, 1);
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