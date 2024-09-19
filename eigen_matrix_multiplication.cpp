#include <iostream>
using namespace std;

#include <iostream>
#include <random>

/**
 * Fills the square matrix of dimension SIZExSIZE of random values between -10 and 10 included
 * @param matrix one dimensional pointer to the matrix
 * @param SIZE size of the matrix
 */
void fill_matrix(double *matrix, const size_t SIZE) {
	//We could make the random number generator global to avoid creating it multiple times
	//...but it's not worth the hastle
	random_device rd;       //Setup of number generator
	mt19937 gen(rd());
	uniform_real_distribution<> double_dist(-10.0, 10.0);


	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			matrix[i * SIZE + j] = double_dist(gen);  // Filling the array with random doubles
		}
	}
}

/**
 * Performs multiplication and returns address of resulting matrix
 * @param matrix1
 * @param matrix2
 * @param SIZE
 */
double *mul_matrix(const double* matrix1, const double* matrix2, const size_t SIZE) {

	auto *result = static_cast<double *>(malloc(sizeof(double) * SIZE * SIZE));


	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			for (size_t k = 0; k < SIZE; k++) {
				result[i * SIZE + j] += matrix1[i * SIZE + k] * matrix2[k * SIZE + j];
			}
		}
	}

	return result;
}

void print_matrix(const double* matrix, size_t SIZE) {
	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			std::cout << matrix[i * SIZE + j] << " ";
		}
		std::cout << std::endl;
	}
}

int main(const int argc, string argv[]) {
	int SIZE;
	bool AUTO_MODE = argc != 2;
	if (AUTO_MODE) {
		SIZE = 2;
		//perror("Usage: \"./program N\", with N being the size of the matrixes");
	} else {
		SIZE = stoi(argv[1]); //Parses parameter, throws exception if not int
	}

	double *m1;
	double *m2;

	//Fills the matrixes with numbers from 1 to 4 and 5 to 8, like in the GitHub example
	if(AUTO_MODE) {
		m1 = static_cast<double *>(malloc(sizeof(double) * 4 ));
		m2 = static_cast<double *>(malloc(sizeof(double) * 4 ));
		for (size_t i = 0; i < 4; i++) {
			m1[i] = i+1;
			m2[i] = i+4+1;
		}
	} else {
		m1 = static_cast<double *>(malloc(sizeof(double) * SIZE * SIZE));
		m2 = static_cast<double *>(malloc(sizeof(double) * SIZE * SIZE));
		fill_matrix(m1, SIZE);
		fill_matrix(m2, SIZE);
	}

	//print_matrix(m1, SIZE);
	//print_matrix(m2, SIZE);

	double *result = mul_matrix(m1, m2, SIZE);

	print_matrix(result, SIZE);

}
