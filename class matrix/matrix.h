#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED
#include <cstdint>
#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, size_t N, size_t M>
class Matrix {
public:
  T array[N][M];

  size_t RowsNumber() const;
  size_t ColumnsNumber() const;

  T& At(size_t row, size_t column);
  T& operator()(size_t row, size_t column);

  const T& At(size_t row, size_t column) const;
  const T& operator()(size_t row, size_t column) const;

  Matrix& operator+=(const Matrix &matrix);
  Matrix& operator-=(const Matrix &matrix);
  template <size_t K>
  Matrix<T, N, K>& operator*=(const Matrix<T, M, K> &matrix);
};

template <typename T, size_t N, size_t M> size_t Matrix<T, N, M>::RowsNumber() const {
  return N;
}

template <typename T, size_t N, size_t M> size_t Matrix<T, N, M>::ColumnsNumber() const {
  return M;
}

template <typename T, size_t N, size_t M> T& Matrix<T, N, M>::operator()(size_t row, size_t column) {
  return array[row][column];
}

template <typename T, size_t N, size_t M> T& Matrix<T, N, M>::At(size_t row, size_t column) {
  if (row > N - 1 || column > M - 1) {
    throw MatrixOutOfRange();
  }
  return array[row][column];
}

template <typename T, size_t N, size_t M> const T& Matrix<T, N, M>::operator()(size_t row, size_t column) const {
  return array[row][column];
}

template <typename T, size_t N, size_t M> const T& Matrix<T, N, M>::At(size_t row, size_t column) const {
  if (row > N - 1 || column > M - 1) {
    throw MatrixOutOfRange();
  }
  return array[row][column];
}

template <typename T, size_t N, size_t M> Matrix<T, M, N> GetTransposed(Matrix<T, N, M>& matrix) {
  Matrix<T, M, N> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      result.array[j][i] = matrix.array[i][j];
    }
  }
  return result;
}

// Операторы для матриц.
template <typename T, size_t N, size_t M> Matrix<T, N, M> operator+(const Matrix<T, N, M>& matrix, const Matrix<T, N, M>& matrix2) {
  Matrix<T, N, M> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      result.array[i][j] = matrix2.array[i][j] + matrix.array[i][j];
    }
  }
  return result;
}

template <typename T, size_t N, size_t M> Matrix<T, N, M> operator-(const Matrix<T, N, M>& matrix2, const Matrix<T, N, M>& matrix) {
  Matrix<T, N, M> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      result.array[i][j] = matrix2.array[i][j] - matrix.array[i][j];
    }
  }
  return result;
}

template <typename T, size_t N, size_t M, size_t K> Matrix<T, N, K> operator*(const Matrix<T, N, M>& matrix2, const Matrix<T, M, K> &matrix) {
  Matrix<T, N, K> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < K; j++) {
      result.array[i][j] = 0;
      for (size_t p = 0; p < M; p++) {
        result.array[i][j] += matrix2.array[i][p] * matrix.array[p][j];
      }
    }
  }
  return result;
}

// Присваивающие версии операторов для матриц.
template <typename T, size_t N, size_t M> Matrix<T, N, M> & Matrix<T, N, M>::operator+=(const Matrix &matrix) {
  *this = *this + matrix;
  return *this;
}

template <typename T, size_t N, size_t M> Matrix<T, N, M> & Matrix<T, N, M>::operator-=(const Matrix &matrix) {
  *this = *this - matrix;
  return *this;
}

template <typename T, size_t N, size_t M> template<size_t K> Matrix<T, N, K>& Matrix<T, N, M>::operator*=(const Matrix<T, M, K> &matrix) {
  *this = *this * matrix;
  return *this;
}

// Умножение и деление на число.
template <typename T, size_t N, size_t M> Matrix<T, N, M> operator*(const  Matrix<T, N, M> &matrix, const int64_t& num) {
  Matrix<T, N, M> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      result.array[i][j] = matrix.array[i][j] * num;
    }
  }
  return result;
}

template <typename T, size_t N, size_t M> Matrix<T, N, M> operator*(const int64_t& num, const  Matrix<T, N, M> &matrix) {
  return matrix * num;
}

template <typename T, size_t N, size_t M> Matrix<T, N, M> operator/(const Matrix<T, N, M> &matrix, const int64_t& num) {
  Matrix<T, N, M> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      result.array[i][j] = matrix.array[i][j] / num;
    }
  }
  return result;
}

// Присваивающие версии операторов для чисел.
template <typename T, size_t N, size_t M> Matrix<T, N, M>& operator*=(Matrix<T, N, M> &matrix, const int64_t& num) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      matrix.array[i][j] *= num;
    }
  }
  return matrix;
}

template <typename T, size_t N, size_t M> Matrix<T, N, M>& operator/=(Matrix<T, N, M> &matrix, const int64_t& num) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      matrix.array[i][j] /= num;
    }
  }
  return matrix;
}

// Сравнение.
template <typename T, size_t N, size_t M> bool operator==(const Matrix<T, N, M>& matrix, const Matrix<T, N, M>& matrix2) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      if (matrix.array[i][j] != matrix2.array[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <typename T, size_t N, size_t M> bool operator!=(const Matrix<T, N, M>& matrix, const Matrix<T, N, M>& matrix2) {
 return !(matrix2 == matrix);
}

// Перегрузка сдвига.
template <typename T, size_t N, size_t M> std::ostream& operator<<(std::ostream &os, const Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M - 1; j++) {
      os << matrix.array[i][j] << ' ';
    }
    os << matrix.array[i][M - 1] << '\n';
  }
  return os;
}

template <typename T, size_t N, size_t M> std::istream& operator>>(std::istream &is, Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      is >> matrix.array[i][j];
    }
  }
  return is;
}

template <typename T, size_t N>
void Transpose(Matrix<T,N,N>& matrix) {
  matrix = GetTransposed(matrix);
}

template <typename T, size_t N>
T Trace(const Matrix<T,N,N>& matrix) {
  T ans = 0;
  for (size_t i = 0; i < N; i++) {
    ans += matrix.array[i][i];
  }
  return ans;
}

template <typename T>
T Determinant(const Matrix<T,1,1>& matrix) {
  return matrix.array[0][0];
}

template <typename T, size_t N>
Matrix<T, N - 1, N - 1> GetMatrixWithoutRowAndColumn(const Matrix<T,N,N>& matrix, size_t row, size_t column) {
  Matrix<T, N - 1, N - 1> ans;
  int di = 0;
  int dj = 0;
  for (size_t i = 0; i < N - 1; i++) {
    if (i == row) {
      di = 1;
    }
    dj = 0;
    for (size_t j = 0; j < N - 1; j++) {
      if (j == column) {
        dj = 1;
      }
      ans.array[i][j] = matrix.array[i + di][j + dj];
    }
  }
  return ans;
}

template <typename T, size_t N>
T Determinant(Matrix<T,N,N> matrix) {
  T det = 0;
  for (size_t i = 0; i < N; i++) {
    Matrix<T, N - 1, N - 1> other = GetMatrixWithoutRowAndColumn(matrix, 0, i);
    det += ((i % 2 == 0) ? matrix.array[0][i] : -matrix.array[0][i]) * Determinant(other);
  }
  return det;
}


template <typename T>
Matrix<T,1,1> GetInversed(const Matrix<T,1,1>& matrix) {
  if (Determinant(matrix) == 0) {
    throw MatrixIsDegenerateError{};
  }
  return Matrix<T,1,1>{T{1} / matrix.array[0][0]};
}

template <typename T, size_t N>
Matrix<T,N,N> GetInversed(const Matrix<T,N,N>& matrix) {
  if (Determinant(matrix) == 0) {
    throw MatrixIsDegenerateError{};
  }
  T det = Determinant(matrix);
  Matrix<T,N,N> inverse_matrix;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      Matrix<T, N - 1, N - 1> tmp = GetMatrixWithoutRowAndColumn(matrix, i, j);
      inverse_matrix.array[i][j] = Determinant(tmp);
      if ((i + j) % 2 == 1) {
        inverse_matrix.array[i][j] = -inverse_matrix.array[i][j];
      }
      inverse_matrix.array[i][j] /= det;
    }
  }
  return GetTransposed(inverse_matrix);
}

template <typename T, size_t N>
void Inverse(Matrix<T,N,N>& matrix) {
  matrix = GetInversed(matrix);
}
#endif //MATRIX_H
