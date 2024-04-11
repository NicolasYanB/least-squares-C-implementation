#include "read_csv.h"

int main() {
  RegressionInfo reg_info = read_csv("data/diabetes_train.csv");
  printf("%f\n", reg_info.observations[0]);
  return 0;
}