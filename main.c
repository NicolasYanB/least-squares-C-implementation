#include "read_csv.h"
#include "matrix_operations.h"
#include "save.h"

double** calculate_least_squares(RegressionData data) {
  double** model_matrix = data.model_matrix;
  double* observations = data.observations;
  int p = data.parameter_count;
  int y = data.observation_count;
  double** model_matrix_T = transpose(model_matrix, y, p);
  double** model_matrix_squared = multiply(model_matrix_T, p, y, model_matrix, y, p);
  double** inversed_model_matrix_squared = inverse(model_matrix_squared, p);
  double** final_model_matrix = multiply(inversed_model_matrix_squared, p, p, model_matrix_T, p, y);
  double** observations_vector = malloc(sizeof(double*));
  observations_vector[0] = observations;
  double** observations_matrix = transpose(observations_vector, 1, y);
  double** model_parameters = multiply(final_model_matrix, p, y, observations_matrix, y, 1);

  free(model_matrix);
  free(observations);
  free(model_matrix_T);
  free(model_matrix_squared);
  free(inversed_model_matrix_squared);
  free(final_model_matrix);
  free(observations_vector);
  free(observations_matrix);

  return model_parameters;
}

int main() {
  RegressionData data = read_csv("data/diabetes_train.csv");
  double** model_parameters = calculate_least_squares(data);
  char* serialized_model = serialize_parameters(model_parameters, data.parameter_count);
  printf("%s\n", serialized_model);
  save_to_file(serialized_model, "results.txt");
  free(serialized_model);
  return 0;
}