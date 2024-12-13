#ifndef MATRIX2_H
#endif

template<class T>
class Matrix2 
{
    public:
        Matrix2();
        Matrix2(int nRows, int nCols);
        Matrix2(int nRows, int nCols, const T *inputData);
        Matrix2(const Matrix2<T>& inputMatrix);

        ~Matrix2();

        T GetElement(int row, int col) const;
        bool SetElement(int row, int col, T data);
        int GetNumRows() const;
        int GetNumCols() const;

        bool operator== (const Matrix2<T>& rhs);
        template<class U> 
        friend std::ostream& operator<< (std::ostream& os, const Matrix2<U>& matrix);

        template<class U> 
        friend Matrix2<U> operator+ (const Matrix2<U>& lhs, const Matrix2<U>& rhs);
        template<class U> 
        friend Matrix2<U> operator+ (const U& lhs, const Matrix2<U>& rhs);
        template<class U> 
        friend Matrix2<U> operator+ (const Matrix2<U>& lhs, const U& rhs);

        template<class U> 
        friend Matrix2<U> operator- (const Matrix2<U>& lhs, const Matrix2<U>& rhs);
        template<class U> 
        friend Matrix2<U> operator- (const U& lhs, const Matrix2<U>& rhs);
        template<class U> 
        friend Matrix2<U> operator- (const Matrix2<U>& lhs, const U& rhs);

        template<class U> 
        friend Matrix2<U> operator* (const Matrix2<U>& lhs, const Matrix2<U>& rhs);
        template<class U> 
        friend Matrix2<U> operator* (const U& lhs, const Matrix2<U>& rhs);
        template<class U> 
        friend Matrix2<U> operator* (const Matrix2<U>& lhs, const U& rhs);

        bool GetIdentityMatrix();

        bool invertMatrix();

    public:
        int Sub2Ind(int row, int col) const;
        bool SwapRows(int r1, int r2) const;
        bool MultiplyRow(int r, T fact) const;
        bool MultiplyRowAndAdd(int r1, int r2, T fact) const;
        int MaxElementRow(int c) const;
        bool JoinMatrix(const Matrix2<T>& rhs);
        bool SeparateMatrix(int col);
    
    private:
        T *m_matrixData;
        int m_nRows, m_nCols, m_nElements;
};


template<class T>
Matrix2<T>::Matrix2() {
    m_nRows = 1;
    m_nCols = 1;
    m_nElements = 1;
    m_matrixData = new T[m_nElements];
    m_matrixData[0] = 0.0;
}

template<class T>
Matrix2<T>::Matrix2(int nRows, int nCols) {
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for(int i = 0; i < m_nElements; i++) {
        m_matrixData[i] = 0.0;
    }
}

template<class T>
Matrix2<T>::Matrix2(int nRows, int nCols, const T *inputData) {
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for(int i = 0; i < m_nElements; i++) {
        m_matrixData[i] = inputData[i];
    }
}

template<class T>
Matrix2<T>::Matrix2(const Matrix2<T>& inputMatrix) {
    m_nRows = inputMatrix.GetNumRows();
    m_nCols = inputMatrix.GetNumCols();
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for(int i = 0; i < m_nRows; i++) {
        for(int j = 0; j < m_nCols; j++) {
            m_matrixData[i * m_nCols + j] = inputMatrix.GetElement(i, j);
        }
    }
}


template<class T>
Matrix2<T>::~Matrix2() {
    if(m_matrixData != nullptr) {
        delete[] m_matrixData;
    }
}

template<class T>
T Matrix2<T>::GetElement(int row, int col) const {
    int ind = Sub2Ind(row, col);
    return m_matrixData[ind];
}

template<class T>
int Matrix2<T>::Sub2Ind(int row, int col) const {
    return row * m_nCols + col;
}

template<class T>
bool Matrix2<T>::SwapRows(int r1, int r2) const {
    int rows = GetNumRows();
    if(r1 >= rows || r2 >= rows || r1 < 0 || r2 < 0) return false;
    int cols = GetNumCols();
    for(int j = 0; j < cols; j++) {
        int temp = m_matrixData[r2 * cols + j];
        m_matrixData[r2 * cols + j] = m_matrixData[r1 * cols + j];
        m_matrixData[r1 * cols + j] = temp;
    }
    return true;
}

template<class T>
bool Matrix2<T>::MultiplyRow(int r, T fact) const {
    int rows = GetNumRows();
    if(r >= rows || r < 0) return false;
    int cols = GetNumCols();
    for(int j = 0; j < cols; j++) {
        m_matrixData[r * cols + j] *= fact;
    }
    return true;
}

template<class T>
bool Matrix2<T>::MultiplyRowAndAdd(int r1, int r2, T fact) const {
    int rows = GetNumRows();
    if(r1 >= rows || r2 >= rows || r1 < 0 || r2 < 0) return false;
    int cols = GetNumCols();
    for(int j = 0; j < cols; j++) {
        m_matrixData[r2 * cols + j] += fact * m_matrixData[r1 * cols + j];
    }
    return true;
}

template<class T>
int Matrix2<T>::MaxElementRow(int c) const {
    int rows = GetNumRows();
    int ind = 0;
    int cols = GetNumCols();
    T maxel = m_matrixData[0 * cols + c];
    for(int i = 0; i < rows; i++) {
        if(m_matrixData[i * cols + c] > maxel) {
            maxel = m_matrixData[i * cols + c];
            ind = i;
        }
    }
    return ind;
}

template<class T>
bool Matrix2<T>::JoinMatrix(const Matrix2<T>& rhs) {
    int lhs_rows = GetNumRows();
    int rhs_rows = rhs.GetNumRows();
    if(lhs_rows != rhs_rows) {
        throw std::invalid_argument("Attempt to join matrices with different number of rows is invalid.");
    }
    int lhs_cols = GetNumCols();
    int rhs_cols = rhs.GetNumCols();
    T* temp_data = new T[lhs_rows * (lhs_cols + rhs_cols)];
    int temp_ind = 0;
    for(int i = 0; i < lhs_rows; i++) {
        for(int j = 0; j < (lhs_cols + rhs_cols); j++) {
            temp_ind = i * (lhs_cols + rhs_cols) + j;
            if(j < lhs_cols) {
                temp_data[temp_ind] = m_matrixData[i * lhs_cols + j];
            } else {
                temp_data[temp_ind] = rhs.m_matrixData[i * rhs_cols + j - lhs_cols];
            }

            // std::cout << temp_ind << " ";
        } 

        // std::cout << std::endl;
    }

    m_nCols = lhs_cols + rhs_cols;
    m_nElements = m_nRows * m_nCols;
    delete[] m_matrixData;
    m_matrixData = new T[m_nElements];
    for(int i = 0; i < m_nElements; i++) {
        m_matrixData[i] = temp_data[i];
        
    }
    delete[] temp_data;

    return true;
}


template<class T>
bool Matrix2<T>::SeparateMatrix(int col) {
    int rows = GetNumRows();
    int cols = GetNumCols();

    T* temp_data = new T[rows * (cols - col)];

    // std::cout << cols << std::endl;

    for(int i = 0; i < rows; i++) {
        for(int j = col; j < cols; j++) {
            temp_data[i * (cols - col) + j - col] = m_matrixData[i * cols + j];
        }
    }

    m_nCols = cols - col;
    m_nElements = m_nRows * m_nCols;
    delete[] m_matrixData;
    m_matrixData = new T[m_nElements];
    for(int i = 0; i < m_nElements; i++) {
        m_matrixData[i] = temp_data[i];
    }
    delete[] temp_data;
    return true;
}


template<class T>
bool Matrix2<T>::SetElement(int row, int col, T data) {
    if(row < m_nRows && col < m_nCols && row >= 0 && col >= 0) {
        int ind = Sub2Ind(row, col);
        m_matrixData[ind] = data;
        return true;
    }
    return false;
}

template<class T>
int Matrix2<T>::GetNumRows() const {
    return m_nRows;
}

template<class T>
int Matrix2<T>::GetNumCols() const {
    return m_nCols;
}

template<class T>
bool Matrix2<T>::operator== (const Matrix2<T>& rhs) {
    if(rhs.GetNumCols() == m_nCols && rhs.GetNumRows() == m_nRows) {
        for(int i = 0; i < m_nRows; i++) {
            for(int j = 0; j < m_nCols; j++) {
                if(GetElement(i, j) != rhs.GetElement(i, j)) {
                    return false;
                }
            }
        }
        return true;
    } 
    return false;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix2<T>& matrix) {
    int rows = matrix.GetNumRows();
    int cols = matrix.GetNumCols();
    
    os << "Matrix (" << rows << " x " << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            os << matrix.GetElement(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

template<class T>
Matrix2<T> operator+ (const Matrix2<T>& lhs, const Matrix2<T>& rhs) {
    int lhs_rows = lhs.GetNumRows();
    int rhs_rows = rhs.GetNumRows();
    int lhs_cols = lhs.GetNumCols();
    int rhs_cols = rhs.GetNumCols();

    if(lhs_rows != rhs_rows || lhs_cols != rhs_cols) {
        throw std::invalid_argument("Matrices dimensions must match for addition.");
    }

    Matrix2<T> result(lhs_rows, lhs_cols);
    for(int i = 0; i < lhs_rows; i++) {
        for(int j = 0; j < lhs_cols; j++) {
            result.SetElement(i, j, lhs.GetElement(i, j) + rhs.GetElement(i, j));
        }
    }

    return result;
}

template<class T>
Matrix2<T> operator+ (const T& lhs, const Matrix2<T>& rhs) {
    int rhs_rows = rhs.GetNumRows();
    int rhs_cols = rhs.GetNumCols();

    Matrix2<T> result(rhs_rows, rhs_cols);
    for(int i = 0; i < rhs_rows; i++) {
        for(int j = 0; j < rhs_cols; j++) {
            result.SetElement(i, j, lhs + rhs.GetElement(i, j));
        }
    }
    return result;
}

template<class T>
Matrix2<T> operator+ (const Matrix2<T>& lhs, const T& rhs) {
    int lhs_rows = lhs.GetNumRows();
    int lhs_cols = lhs.GetNumCols();

    Matrix2<T> result(lhs_rows, lhs_cols);
    for(int i = 0; i < lhs_rows; i++) {
        for(int j = 0; j < lhs_cols; j++) {
            result.SetElement(i, j, rhs + lhs.GetElement(i, j));
        }
    }
    return result;
}

template<class T>
Matrix2<T> operator- (const Matrix2<T>& lhs, const Matrix2<T>& rhs) {
    int lhs_rows = lhs.GetNumRows();
    int rhs_rows = rhs.GetNumRows();
    int lhs_cols = lhs.GetNumCols();
    int rhs_cols = rhs.GetNumCols();

    if(lhs_rows != rhs_rows || lhs_cols != rhs_cols) {
        throw std::invalid_argument("Matrices dimensions must match for subtraction.");
    }

    Matrix2<T> result(lhs_rows, lhs_cols);
    for(int i = 0; i < lhs_rows; i++) {
        for(int j = 0; j < lhs_cols; j++) {
            result.SetElement(i, j, lhs.GetElement(i, j) - rhs.GetElement(i, j));
        }
    }

    return result;
}

template<class T>
Matrix2<T> operator- (const T& lhs, const Matrix2<T>& rhs) {
    int rhs_rows = rhs.GetNumRows();
    int rhs_cols = rhs.GetNumCols();

    Matrix2<T> result(rhs_rows, rhs_cols);
    for(int i = 0; i < rhs_rows; i++) {
        for(int j = 0; j < rhs_cols; j++) {
            result.SetElement(i, j, lhs - rhs.GetElement(i, j));
        }
    }
    return result;
}

template<class T>
Matrix2<T> operator- (const Matrix2<T>& lhs, const T& rhs) {
    int lhs_rows = lhs.GetNumRows();
    int lhs_cols = lhs.GetNumCols();

    Matrix2<T> result(lhs_rows, lhs_cols);
    for(int i = 0; i < lhs_rows; i++) {
        for(int j = 0; j < lhs_cols; j++) {
            result.SetElement(i, j, lhs.GetElement(i, j) - rhs);
        }
    }
    return result;
}

template<class T>
Matrix2<T> operator* (const Matrix2<T>& lhs, const Matrix2<T>& rhs) {
    int lhs_rows = lhs.GetNumRows();
    int rhs_rows = rhs.GetNumRows();
    int lhs_cols = lhs.GetNumCols();
    int rhs_cols = rhs.GetNumCols();

    if(lhs_cols != rhs_rows) {
        throw std::invalid_argument("Left matrice's number of columns should match with right matrice's number of rows for multiplication.");
    }

    Matrix2<T> result(lhs_rows, rhs_cols);
    for(int i = 0; i < lhs_rows; i++) {
        for(int j = 0; j < rhs_cols; j++) {
            T tempAns = 0.0;
            for(int k = 0; k < lhs_cols; k++) {
                tempAns += lhs.GetElement(i, k) * rhs.GetElement(k, j);
            }
            result.SetElement(i, j, tempAns);
        }
    }

    return result;
}

template<class T>
Matrix2<T> operator* (const T& lhs, const Matrix2<T>& rhs) {
    int rhs_rows = rhs.GetNumRows();
    int rhs_cols = rhs.GetNumCols();

    Matrix2<T> result(rhs_cols, rhs_cols);
    for(int i = 0; i < rhs_rows; i++) {
        for(int j = 0; j < rhs_cols; j++) {
            result.SetElement(i, j, lhs * rhs.GetElement(i, j));
        }
    }
    return result;
}

template<class T>
Matrix2<T> operator* (const Matrix2<T>& lhs, const T& rhs) {
    int lhs_rows = lhs.GetNumRows();
    int lhs_cols = lhs.GetNumCols();

    Matrix2<T> result(lhs_cols, lhs_cols);
    for(int i = 0; i < lhs_rows; i++) {
        for(int j = 0; j < lhs_cols; j++) {
            result.SetElement(i, j, lhs.GetElement(i, j) * rhs);
        }
    }
    return result;
}


template<class T>
bool Matrix2<T>::GetIdentityMatrix() {
    if(m_nCols != m_nRows) {
        throw std::invalid_argument("The matrix should be square matrix to get its identity.");
    }

    for(int i = 0; i < m_nElements; i++) {
        m_matrixData[i] = 0.0;
    }

    for(int i = 0; i < m_nRows; i++) {
        m_matrixData[i * m_nCols + i] = 1.0;
    }
    
    return true;
}

template<class T>
bool Matrix2<T>::invertMatrix() {
    if(m_nCols != m_nRows) {
        throw std::invalid_argument("The matrix should be square matrix to get its inversion.");
    }

    int n = m_nCols;

    Matrix2<T> identity_matrix(m_nRows, m_nRows);
    identity_matrix.GetIdentityMatrix();

    std::cout << "IDENTITY: " << std::endl;
    std::cout << identity_matrix << std::endl;

    JoinMatrix(identity_matrix);

    std::cout << "AUGMENTED: " << std::endl;

    for (int i = 0; i < m_nRows; ++i) {
        for (int j = 0; j < m_nCols; ++j) {
            std::cout << m_matrixData[i * m_nCols + j] << " ";
        }
        std::cout << std::endl;
    }

    int currRow = 0, currCol = 0;
    while(currRow < n && currCol < n) {
        T currPivotVal = GetElement(currRow, currCol);
        if(currPivotVal != 0) {
            T fact = 1.0 / currPivotVal;
            MultiplyRow(currRow, fact);

            for(int r = 0; r < n; r++) {
                if(r != currRow) {
                    T fact = -GetElement(r, currCol);
                    MultiplyRowAndAdd(currRow, r, fact);
                }
            }
        } else {
            int ind = MaxElementRow(currCol);
            SwapRows(ind, currRow);
            continue;
        }
        currRow++;
        currCol++;

    //     std::cout << "AUGMENTED: " << std::endl;

    // for (int i = 0; i < m_nRows; ++i) {
    //     for (int j = 0; j < m_nCols; ++j) {
    //         std::cout << m_matrixData[i * m_nCols + j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    }


    // std::cout << "AUGMENTED: " << std::endl;

    // for (int i = 0; i < m_nRows; ++i) {
    //     for (int j = 0; j < m_nCols; ++j) {
    //         std::cout << m_matrixData[i * m_nCols + j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    SeparateMatrix(n);
    return true;
}


