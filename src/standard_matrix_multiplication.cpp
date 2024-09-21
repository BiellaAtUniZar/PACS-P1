#include <assert.h>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

typedef std::vector<std::vector<double>> Mat;
typedef std::vector<double> Row;
/**
 * Fills the square matrix of dimension SIZExSIZE of random values between -10
 * and 10 included
 * @param matrix one dimensional pointer to the matrix
 */
void fill_matrix(Mat &matrix) {
  random_device rd; // Setup of number generator
  mt19937 gen(rd());
  uniform_real_distribution<> double_dist(-10.0, 10.0);
  int k = 0;
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      // matrix[i][j] = double_dist(gen);  // Filling the array with random
      // doubles
      k++;
      matrix[i][j] = k;
    }
  }
}

/**
 * Performs multiplication and returns address of resulting matrix
 * @param matrix1
 * @param matrix2
 */
void mul_matrix(const Mat &matrix1, const Mat &matrix2, Mat &result) {
  // Assuming NxN matrices
  assert(matrix1.size() == matrix2.size());
  assert(matrix1[0].size() == matrix2[0].size());
  assert(matrix1[0].size() == matrix1.size());
  assert(matrix2[0].size() == matrix2.size());
  for (size_t i = 0; i < matrix1.size(); i++) {
    for (size_t j = 0; j < matrix1.size(); j++) {
      for (size_t k = 0; k < matrix1.size(); k++) {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
}

void print_matrix(const Mat &matrix) {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  int SIZE;
  bool AUTO_MODE = argc != 3;
  int iteration;
  if (AUTO_MODE) {
    iteration = 10;
    SIZE = 2;
  } else {
    SIZE = stoi(argv[1]); // Parses parameter, throws exception if not int
    iteration = stoi(argv[2]);
  }

  // initialize matrices
  Mat m1(SIZE, Row(SIZE, 0.));
  Mat m2(SIZE, Row(SIZE, 0.));
  Mat result(SIZE, Row(SIZE, 0.));

  // Fills matrices
  fill_matrix(m1);
  fill_matrix(m2);
  // matrix multiplication
  double mean_time = 0;
  std::vector<double> times;
  for (int i = 0; i < iteration; i++) {
    auto t1 = high_resolution_clock::now();
    mul_matrix(m1, m2, result);
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;
    mean_time += ms_double.count();
    times.push_back(ms_double.count());
  }
  mean_time /= iteration * 1.;
  double stand_dev = 0.;
  for (size_t i = 0; i < times.size(); i++) {
    stand_dev +=
        (times[i] - mean_time) * (times[i] - mean_time) / times.size() * 1.0;
  }

  stand_dev = sqrt(stand_dev);
  std::cout << "Mean="<< mean_time << "ms ; Standard Deviation="<< stand_dev <<"ms"<<std::endl;
  
  return 0;
}
