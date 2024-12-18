#ifndef LINSOLVE_H
#define LINSOLVE_H

#include <stdexcept>
#include <vector>
#include <math.h>
#include <iostream>

#include "Matrix2.h"
#include "Vector.h"

constexpr int LINSOLVE_NO_UNIQUE_SOLUTION = -1;
constexpr int LINSOLVE_NO_SOLUTION = -2;

template <typename T>
int LinSolve(const Matrix2<T> &aMatrix, const abVector<T> &bVector, abVector<T> &output) {
    Matrix2<T> inputMatrix = aMatrix;

    int numDims = bVector.GetNumDims();
    std::vector<T> bData;
    for(int i = 0; i < numDims; i++) {
        bData.push_back(bVector.GetElement(i));
    }

    Matrix2<T> rowEchelonBeforeJoin = inputMatrix.RowEchelon();

    int rankBefore = rowEchelonBeforeJoin.Rank();

    Matrix2<T> bMatrix(numDims, 1, bData);

    inputMatrix.JoinMatrix(bMatrix);

    Matrix2<T> rowEchelon = inputMatrix.RowEchelon();

    int rankAfter = rowEchelon.Rank();

    if(rankBefore == rankAfter && rankBefore < inputMatrix.GetNumRows()) {
        return LINSOLVE_NO_UNIQUE_SOLUTION;
    } else if(rankBefore < rankAfter) {
        return LINSOLVE_NO_SOLUTION;
    } else {
        int nRows = rowEchelon.GetNumRows();
        int nCols = rowEchelon.GetNumCols();

        for(int i = nRows - 1; i >= 0; i--) {
            T currRes = rowEchelon.GetElement(i, nCols - 1);
            T cumSum = static_cast<T>(0.0);

            for(int j = i + 1; j < nRows; j++) {
                cumSum += rowEchelon.GetElement(i, j) * output.GetElement(j);
            }

            T finalAns = (currRes - cumSum) / rowEchelon.GetElement(i, i);

            output.SetElement(i, finalAns);
        }

        return 1;
    }
    
}

#endif