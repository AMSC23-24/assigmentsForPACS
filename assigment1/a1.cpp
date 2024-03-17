#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <numeric>

// Armijo Rule Function taking in (F, Gradient of F, Iterations, Alpha ^ 0 and sigma-value [0,0.5])
double armijoRule(std::function<double(std::vector<double>)> f,
                  std::function<std::vector<double>(std::vector<double>)> grad_f,
                  std::vector<double> xk, double alpha0, double sigma)
{
    double alpha = alpha0;
    std::vector<double> x_next;
    std::vector<double> grad_at_xk;

    // generates alpha (alpha_k) using the The armijoRule.
    do
    {
        alpha /= 2;              // Half alpha to ensure the step is small enough to meet the Armijo condition.
        x_next = xk;             // Prepare next point by starting at the current point.
        grad_at_xk = grad_f(xk); // Compute gradient at current point.

        // Exit loop if encountering empty vectors to prevent errors. Got segmentations failiure without this error-check
        if (x_next.empty() || grad_at_xk.empty())
        {
            std::cerr << "Error: One of the vectors is empty." << std::endl;
            break;
        }

        // Move towards the direction of steepest descent by updating x_next.
        for (std::vector<double>::size_type i = 0; i < x_next.size(); ++i)
        {
            x_next[i] -= alpha * grad_at_xk[i];
        }

        // Continue until the decrease in the function's value satisfies the Armijo condition. I choose to use Approximate line search
    } while (f(xk) - f(x_next) < sigma * alpha * std::inner_product(grad_at_xk.begin(), grad_at_xk.end(), grad_at_xk.begin(), 0.0));

    return alpha; // Return the adjusted step size.
}

// Gradient Descent Algorithm
std::vector<double> gradientDescent(std::function<double(std::vector<double>)> f,
                                    std::function<std::vector<double>(std::vector<double>)> grad_f,
                                    std::vector<double> x0, double alpha0, double eps_r, double eps_s, int k_max)
{
    std::vector<double> x = x0;     // staring point
    double alpha = alpha0;          // alpha ^ 0
    for (int k = 0; k < k_max; ++k) // iterate up to k_max (max iterations)
    {
        std::vector<double> grad = grad_f(x); // adjust step size using the Armijo rule.
        double norm_grad = std::sqrt(std::inner_product(grad.begin(), grad.end(), grad.begin(), 0.0));

        // gradient method: control on the step length condition
        if (norm_grad < eps_r)
            break;

        alpha = armijoRule(f, grad_f, x, alpha0, 0.5); // usage of Armijo rule with sigma = 0.5. I Choose as fixed at sigma = 0.5 because sigma limits are [0,0.5]
        for (std::vector<double>::size_type i = 0; i < x.size(); ++i)
        {
            x[i] -= alpha * grad[i];
        }

        // gradient method: control on the residual condition
        if (std::sqrt(std::inner_product(grad.begin(), grad.end(), grad.begin(), 0.0)) < eps_s)
            break;
    }
    return x; // Return the position of the minimum found.
}

// Main Function
int main()
{

    // Implementing the function F
    auto f = [](std::vector<double> x) -> double
    {
        return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0];
    };

    // Implementing the gradient of the function F
    auto grad_f = [](std::vector<double> x) -> std::vector<double>
    {
        return {16 * pow(x[0], 3) + x[1] + 3, x[0] + 2 * x[1]};
    };

    // implement init-value
    std::vector<double> x0 = {0, 0}; // starting point
    double alpha0 = 1.0; // alpha ^ 0
    double eps_r = 1e-6; // tolerence for e_r
    double eps_s = 1e-6; // tolerence for e_s
    int k_max = 10000; // max-iterations

    std::vector<double> x_min = gradientDescent(f, grad_f, x0, alpha0, eps_r, eps_s, k_max); // calculating the minimum using F and Gradient F
    std::cout << "Minimum found at: (" << x_min[0] << ", " << x_min[1] << ")" << std::endl;

    return 0;
}
