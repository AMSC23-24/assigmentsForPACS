# Assigment.1 Armijo Rule and Gradient Descent Algorithm

## Overview
This implementation is my solution to assigment.1, which is to implement  function that takes in input two function wrappers that defines f, ∇f, the initial condition, the tolerances, the initial step α^0, the maximal number of iterations and all other
needed parameters and returns the computed minumum. 

## Functions

### `armijoRule`
- **Purpose**: Adjusts the step size (`alpha`) to meet the Armijo condition for sufficient decrease.
- **Parameters**:
  - `f`: The objective function to minimize.
  - `grad_f`: The gradient of the function `f`.
  - `xk`: Current position vector.
  - `alpha0`: Initial step size.
  - `sigma`: Fractional reduction parameter (between 0 and 0.5).
- **Process**: Repeatedly halves `alpha` and checks the Armijo condition against the decrease in `f`. The loop exits when the decrease is sufficient.

### `gradientDescent`
- **Purpose**: Minimizes the function `f` starting from an initial point (0,0).
- **Parameters**:
  - `f`: The function to minimize.
  - `grad_f`: The gradient of `f`.
  - `x0`: The starting point vector.
  - `alpha0`: Initial step size.
  - `eps_r`: The threshold for the gradient norm (termination criterion).
  - `eps_s`: The threshold for the change in function value (termination criterion).
  - `k_max`: Maximum number of iterations.
- **Process**: Applies the gradient descent method using the Armijo rule to adjust `alpha`. Stops when the gradient norm or function improvement is below specified thresholds.

## Usage
To run the program, type in `make then ./a1`. The program will output the coordinates of the minimum found for the defined function `f`. Using armijoRule and gradientDescent-algorithm. The result should be: `Minimum found at: (-0.590551, 0.295275)` for given `f` in this assigment. 

## Note
- This implementation assumes a two-dimensional space.
- The function `f` and its gradient `grad_f` are hardcoded due to the spesific task of this assigment. You can define them in the main function
