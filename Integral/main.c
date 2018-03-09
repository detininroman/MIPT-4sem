#include <stdio.h>

double f(double x)
{
    return x*x;
}

double integrate(double a, double b)
{
    double result = 0, N = 1e+9, dx = (b-a)/N;
    
    for (double x = a; x < b; x += dx)
        result += f(x) * dx;
    
    return result;
}

int main(void)
{
    printf("Result: %lg\n", integrate(0.00, 5.00));
    return 0;
}
