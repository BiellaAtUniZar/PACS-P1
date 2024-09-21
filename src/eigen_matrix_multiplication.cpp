#include <chrono>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <random>

using namespace std;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

typedef Eigen::MatrixXd Mat;
/**
 * Fills the square matrix of dimension SIZExSIZE of random values between -10
 * and 10 included
 * @param matrix one dimensional pointer to the matrix
 * @param SIZE size of the matrix
 */
Mat fill_matrix(const size_t SIZE) {
  Eigen::MatrixXd mat = Eigen::MatrixXd::Random(SIZE, SIZE);
  return mat;
}

/**
 * Performs multiplication and returns address of resulting matrix
 * @param matrix1
 * @param matrix2
 * @param SIZE
 */
Mat mul_matrix(Mat mat1, Mat mat2) { return mat1 * mat2; }

void print_matrix(Mat mat1) { std::cout << mat1 << std::endl; }

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

  // Fills matrices
  Mat m1 = fill_matrix(SIZE);
  Mat m2 = fill_matrix(SIZE);

  // matrix multiplication
  double mean_time = 0;
  std::vector<double> times;
  for (int i = 0; i < iteration; i++) {
    auto t1 = high_resolution_clock::now();
    Mat result = mul_matrix(m1, m2);
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
  std::cout << "Mean=" << mean_time << "ms ; Standard Deviation=" << stand_dev
            << "ms" << std::endl;

  return 0;
}
