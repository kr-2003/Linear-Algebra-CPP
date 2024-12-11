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
        friend std::ostream& operator<<(std::ostream& os, const Matrix2<U>& matrix);

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