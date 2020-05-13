#include "clab2.h"

int main()
{
    double eps;

    do {
        printf("Enter epsilon: ");
        scanf("%lf", &eps);
    } while (are_roughly_equal(eps, 0, DOUBLE_EPS));

    task(eps);

    fflush(stdin);

    return 0;
}