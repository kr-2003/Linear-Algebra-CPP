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

    private:
        int Sub2Ind(int row, int col) const;
    
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
            m_matrixData[i * m_nRows + j] = inputMatrix.GetElement(i, j);
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
    return row * m_nRows + col;
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



