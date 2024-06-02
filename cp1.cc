/*
This is the function you need to implement. Quick reference:
- input rows: 0 <= y < ny
- input columns: 0 <= x < nx
- element at row y and column x is stored in data[x + y*nx]
- correlation between rows i and row j has to be stored in result[i + j*ny]
- only parts with 0 <= j <= i < ny need to be filled
*/
#include <vector>

#include "math.h"
#include "stdlib.h"

void correlate(int ny, int nx, const float *data, float *result) {
  std::vector<double> A((ny * nx), 0.0);

  // normalize input rows so that mean = 0
  for (int y = 0; y < ny; y++) {
    double sum = 0;
    double mean;
    for (int x = 0; x < nx; x++) {
      sum += data[x + y * nx];
    }
    mean = sum / nx;

    for (int x = 0; x < nx; x++) {
      A[x + y * nx] = data[x + y * nx] - mean;
    }
  }
  // normalize input rows so that sum of squares = 1
  for (int y = 0; y < ny; y++) {
    double squaredsum = 0;
    for (int x = 0; x < nx; x++) {
      squaredsum += A[x + y * nx] * A[x + y * nx];
    }
    for (int x = 0; x < nx; x++) {
      A[x + y * nx] = A[x + y * nx] / sqrt(squaredsum);
    }
  }

  // compute the matrix product of A * A^T without explicitly computing A^T.
  // i traverses rows of A, j traverses columns of A^T, and e traverses the
  // specific elements to multiply. We only want the upper triangular matrix
  // part, and we store correlation between row i and row j in result[i + j*ny].
  // Therefore, 0 <= i < ny and 0 <= j <= i < ny.
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j <= i; j++) {
      double sum = 0;
      for (int e = 0; e < nx; e++) {
        sum += A[e + i * nx] * A[e + j * nx];
      }
      result[i + j * ny] = sum;
    }
  }
}
