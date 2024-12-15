#include <iostream>
#include "Vector.h"

int main() {
    std::vector<double> inputData = {1.0, 12.0, 89.0};
    std::vector<double> inputData2 = {-10.0, 32.0, 89.0};
    abVector<double> v1(inputData);
    abVector<double> v2(inputData2);

    abVector<double> sum = v1 + v2;
    abVector<double> diff = v1 - v2;

    std::cout << "SUM: " << std::endl;
    std::cout << sum << std::endl;

    std::cout << "DIFF: " << std::endl;
    std::cout << diff << std::endl;

    std::cout << "SCALAR MULT: " << std::endl;
    std::cout << v1 * 5.0 << std::endl;
    std::cout << 5.0 * v1 << std::endl;

    std::cout << "DOT: " << std::endl;
    std::cout << v1.dot(v1, v2) << std::endl;

    std::cout << "CROSS: " << std::endl;
    std::cout << v1.cross(v1, v2) << std::endl;



    return 0;
}