#include "read_csv.h"
#include "matrix_operations.h"

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