#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// BF. Time = O(2^N), space = O(2^N)
bool populateNumber(const int x, const int idx, const size_t num, size_t &row, std::vector<std::vector<int>>& res) {
	int cnt = 0;
	for(; cnt < x && row < res.size(); ++cnt, ++row) {
			res[row][idx] = num;
	}
	return row < res.size()? true : false;
}

void populateBits(const int x, const int idx, std::vector<std::vector<int>>& res) {
	size_t row = 0;
	while(true) {
		if(!populateNumber(x, idx, 0, row, res)) {
			return;
		}
		if(!populateNumber(x, idx, 1, row, res)) {
			return;
		}
		if(!populateNumber(x, idx, 1, row, res)) {
			return;
		}
		if(!populateNumber(x, idx, 0, row, res)) {
			return;
		}
	}
}

void printGrayCode(const int numBits) {
	std::vector<std::vector<int>> temp(1 << numBits, std::vector<int>(numBits, 0));
	int numOnesZeroes = 1;
	for(int col = temp[0].size() - 1; col >= 0; --col, numOnesZeroes <<= 1) {
		populateBits(numOnesZeroes, col, temp);
	}
	for(const auto& row : temp) {
		for(const auto& colVal : row) {
			std::cout << colVal << " ";
		}
		std::cout << '\n';
	}
}

// O(2^N) time and space (space is 2^N + N for recursive calls)
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

std::vector<int> printgrayCodeOpt(const int n) {
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
//	const auto& res = printGrayCode(n);
	const auto& res = printGrayCodeOpt(n);

	printLastNBits(res, n);
}
