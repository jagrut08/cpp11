#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// O(2^N) time and space
void printLastNBits(const std::vector<int>& v, const int n) {
	std::ostringstream op;
	for(const auto& val : v) {
		int temp = val;
		std::ostringstream tmpStr;
		for(int i = 0; i < n; ++i){
			tmpStr << (temp & 1 ? '1' : '0');
			temp >>= 1;
		}
		std::string tmpString = tmpStr.str();
		std::reverse(tmpString.begin(), tmpString.end());
		op << tmpString<< '\n';
	}
	std::cout << op.str();
}

std::vector<int> grayCodeOpt(const int n) {
	if(n <= 0) {
		throw std::runtime_error("Invalid input");
	}
	std::vector<int> res(1 << n, 0);
	if(n == 1) {
		res[1] = 1;
	} else if(n > 1) {
		const auto& prev = grayCodeOpt(n - 1);
		size_t idx = 0;
		for(const auto& p : prev) {
			res[idx++] = p;
		}
		for(auto it = prev.crbegin(); it != prev.crend(); ++it) {
			res[idx++] = (*it | (1 << (n - 1)));
		}
	}
	return res;
}

int main() {
	const int n = 4;
	const auto& res = grayCodeOpt(n);
	printLastNBits(res, n);
}
