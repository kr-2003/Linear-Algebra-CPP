#include <iostream>
#include "Vector.h"
#include "Matrix2.h"
#include "LinSolve.h"
#include <vector>

int main() {
    double input[9] = {5, 3, 9, -2, 3, -1, -1, -4, 5};
    Matrix2<double> a(3, 3, input);

    std::vector<double> inputVector = {-1, -2, 1};

    abVector<double> b(inputVector);

    abVector<double> ans = LinSolve(&a, &b);

    std::cout << ans << std::endl;

    return 0;
}