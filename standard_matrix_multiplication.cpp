#include <iostream>
#include <random>
#include <vector>
#include <assert.h>
using namespace std;
typedef std::vector<std::vector<double>> Mat;
typedef std::vector<double> Row;
/**
 * Fills the square matrix of dimension SIZExSIZE of random values between -10 and 10 included
 * @param matrix one dimensional pointer to the matrix
 */
void fill_matrix(Mat &matrix) {
	random_device rd;       //Setup of number generator
	mt19937 gen(rd());
	uniform_real_distribution<> double_dist(-10.0, 10.0);
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix[0].size(); j++) {
			matrix[i][j] = double_dist(gen);  // Filling the array with random doubles
		}
	}
}

/**
 * Performs multiplication and returns address of resulting matrix
 * @param matrix1
 * @param matrix2
 */
	void mul_matrix(const Mat &matrix1, const Mat &matrix2, Mat &result) {
	//Assuming NxN matrices
	assert(matrix1.size()==matrix2.size());
	assert(matrix1[0].size()==matrix2[0].size());
	assert(matrix1[0].size()==matrix1.size());
	assert(matrix2[0].size()==matrix2.size());
	for (size_t i = 0; i < matrix1.size(); i++) {
		for (size_t j = 0; j < matrix1.size(); j++) {
			for (size_t k = 0; k < matrix1.size(); k++) {
			result[i][j]+=matrix1[i][k]*matrix2[k][j];
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

int main(int argc, char * argv[]) {
	int SIZE;
	bool AUTO_MODE = argc != 2;
	if (AUTO_MODE) {
		SIZE = 2;
	} else {
		SIZE = stoi(argv[1]); //Parses parameter, throws exception if not int
	}

	//initialize matrices
	Mat m1 (SIZE, Row(SIZE,0.) );
	Mat m2 (SIZE, Row(SIZE,0.) );
	Mat result (SIZE, Row(SIZE,0.) );

	//Fills matrices 
	fill_matrix(m1);
	fill_matrix(m2);
	std::cout<<"Mat1="<<std::endl;
	print_matrix(m1);
	std::cout<<"Mat2="<<std::endl;
	print_matrix(m2);
	//matrix multiplication 
	mul_matrix(m1, m2, result);
	std::cout<<"Result="<<std::endl;
	print_matrix(result);
	return 0;
}
