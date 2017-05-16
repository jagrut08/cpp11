#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

unsigned long long calcExpSum(const std::vector<int>& v) {
	const size_t N = v.size() + 2;
	return N * (N + 1) / 2;
}

unsigned long long calcActualSum(const std::vector<int>& v) {
	unsigned long long res = 0;
	for(const auto& val : v) {
		res += val;
	}
	return res;
}

unsigned long long calcExpSqSum(const std::vector<int>& v) {
	const size_t N = v.size() + 2;
	unsigned long long res = 0;
	for(size_t i = 1; i <= N; ++i) {
		res += i * i;
	}
	return res;
}

unsigned long long calcActualSqSum(const std::vector<int>& v) {
	unsigned long long res = 0;
	for(const auto& val : v) {
		res += val * val;
	}
	return res;
}

void findMissingTwo(const std::vector<int>& v) {
	if(v.empty()) {
		throw std::runtime_error("Empty input");
	}

	const unsigned long long q = calcExpSum(v) - calcActualSum(v);
	std::cout << "q = " << q << '\n';

	const unsigned long long sumOfSqMissing = calcExpSqSum(v) - calcActualSqSum(v);
	std::cout << "sumOfSqMissing = " << sumOfSqMissing << '\n';

	const double p = (q * q - sumOfSqMissing) / 2.0;
	std::cout << "p = " << p << '\n';

	const double secTerm = std::sqrt(double(q * q - 4 * p)) / 2.0;
	std::cout << "secTerm = " << secTerm << '\n';

	std::cout << "\nAnswer " << (q / 2.0) + secTerm << ", " << (q / 2.0) - secTerm << '\n';
}

int main() {
	const std::vector<int> v{2, 3, 4, 6, 7};
	findMissingTwo(v); // 5, 1
}
