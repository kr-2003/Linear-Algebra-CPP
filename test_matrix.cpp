#include <iostream>
#include "Matrix2.h"

int main() {
    // Test default constructor
    Matrix2<double> mat1;
    std::cout << "Default Matrix: " << mat1.GetElement(0, 0) << std::endl;

    // Test constructor with dimensions
    Matrix2<int> mat2(3, 3);
    mat2.SetElement(1, 1, 42);
    std::cout << "Matrix (1,1): " << mat2.GetElement(1, 1) << std::endl;

    // Test constructor with input data
    int inputData[4] = {1, 2, 3, 4};
    Matrix2<int> mat3(2, 2, inputData);
    std::cout << "Matrix (0,1): " << mat3.GetElement(0, 1) << std::endl;

    // Test copy constructor
    Matrix2<int> mat4(mat3);
    std::cout << "Copied Matrix (0,1): " << mat4.GetElement(0, 1) << std::endl;

    std::cout << mat3 << std::endl;

    std::cout << mat4 << std::endl;

    // Test equality operator
    if (mat3 == mat4) {
        std::cout << "Matrix 3 and Matrix 4 are equal." << std::endl;
    } else {
        std::cout << "Matrix 3 and Matrix 4 are not equal." << std::endl;
    }

    return 0;
}
