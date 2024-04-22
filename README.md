A C implementation of least squares multiple linear regression
# Least squares
Least squares is a method to fit a line into given data observations and have the following formula
$$\beta = (X^TX)^{-1}X^Ty$$
where $\beta$ is the coeficients of the model, $y$ is the vector of the observations and $X$ is the model matrix with the observed coeficients

# The program
``/data/diabetes.ipynb`` prepares a csv with a train sample of the diabetes dataset from scikit-learn. The code then reads the file ``diabetes_train.csv`` to extract the observations vector ($y$) and the model matrix ($X$).

The results are then computed and the coefficients are saved in a txt file, (``results.txt``)

You can compare the results of the C implementation with the results from scikit-learn on the notebook ``/data/regression.ipynb`` 
# modules
The code is separated in 3 parts, besides ``main.c``
- ``read_csv.h`` has the code used to read the csv file and return all the information needed to compute the result
- ``matrix_operations.h`` has all the matrix operations needed, they are:
  -   matrix transposition
  -   matrix multiplication
  -   matrix inversion
-   ``save.h`` simply has the function to store the results in a plain text file
