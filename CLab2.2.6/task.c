#include <math.h>
#include "clab2.h"

#define M_PI 3.14159265358979323846

int factorial(int num) {

    if (num >= 1)
        return num * factorial(num - 1);
    else
        return 1;
}

int are_roughly_equal(double x, double y, double epsilon)
{
    double difference = x - y;

    if (difference < epsilon && -difference < epsilon)
        return 1;
    
    return 0;
}

void task(double epsilon)
{
    double iteration = M_PI / 360;

    double angle = 0;
    for (; angle < M_PI / 2 || are_roughly_equal(angle, M_PI / 2, DOUBLE_EPS); angle += iteration)
    {
        int n = 1;
        double sine = sin(angle), calculated_sine = 0;

        for (; !are_roughly_equal(sine, calculated_sine, epsilon); n++)
        {
            calculated_sine += pow(-1, n - 1) * pow(angle, 2 * n - 1) / factorial(2 * n - 1);
        }

        printf("For the angle of %.2f degrees and the epsilon of %f "
               "the n is %d; sine ~ calculated sine: %f ~ %f\n",
               angle * 180 / M_PI, epsilon, n, sine, calculated_sine);
    }
}
