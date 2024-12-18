#include <iostream>
#include "Vector.h"
#include "Matrix2.h"
#include "LinSolve.h"
#include <vector>

int main() {
    double input[9] = {-1, -2, 1, 2, 3, 0, 0, 1, -2};
    Matrix2<double> a(3, 3, input);

    std::vector<double> inputVector = {-1, 2, 0};

    abVector<double> b(inputVector);

    abVector<double> solution(3);

    int ans = LinSolve(a, b, solution);

    std::cout << ans << std::endl;
    std::cout << solution << std::endl;

    double input2[9] = {2, 4, 6, 8, 1, 3, 5, 7};
    Matrix2<double> c(2, 4, input2);
    Matrix2<double>d = c.RowEchelon();

    Matrix2<double> e = a.RowEchelon();

    std::cout << d << std::endl;

    // std::cout << e << std::endl;
    // std::cout << "IS ROW ECH: " << e.IsRowEchelon() << std::endl;
    // std::cout << e.Rank() << std::endl;
    return 0;
}