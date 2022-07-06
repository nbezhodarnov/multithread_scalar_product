#include <random>
#include <vector>
#include <iostream>

#include <omp.h>

double InnerProduct(const std::vector<double> &first, const std::vector<double> &second) {
	if (first.size() != second.size()) {
		std::cerr << "Sizes of vectors are not equal!\n";
		return 0;
	}
	double result = 0;
	unsigned int i;
	#pragma omp for private(i) reduction(+:result)
	for (i = 0; i < first.size(); i++) {
		result += first[i] * second[i];
	}
	return result;
}

int main() {
	unsigned int n;
	std::cout << "Input number of elements: ";
	std::cin >> n;
	
	std::default_random_engine dre(0);
    std::uniform_real_distribution<> uid(-10, 10);
	std::vector<double> vector1(n), vector2(n);
	for (unsigned int i = 0; i < n; i++) {
		vector1[i] = uid(dre);
		vector2[i] = uid(dre);
	}
	
	std::cout << "First vector: ";
	for (unsigned int i = 0; i < n; i++) {
		std::cout << vector1[i] << ' ';
	}
	std::cout << '\n';
	std::cout << "Second vector: ";
	for (unsigned int i = 0; i < n; i++) {
		std::cout << vector2[i] << ' ';
	}
	std::cout << '\n';
	
	std::cout << "Inner product: " << InnerProduct(vector1, vector2) << '\n';
	
	return 0;
}
