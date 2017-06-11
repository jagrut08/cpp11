#include <iostream>
#include <stdexcept>
#include <vector>

// O(N*M) time, where N = num rows, M = num cols. O(1) space.
void zeroCol(std::vector<std::vector<int>>& m, const size_t col) {
	for(size_t row = 0; row < m.size(); ++row) {
		m[row][col] = 0;
	}
}

void zeroRow(std::vector<std::vector<int>>& m, const size_t row) {
	for(size_t col = 0; col < m[0].size(); ++col) {
		m[row][col] = 0;
	}

}

void zeroMatrix(std::vector<std::vector<int>>& m) {
	if(m.empty()) {
		throw std::runtime_error("Empty input");
	}
	bool firstRowZero = false, firstColZero = false;

	for(size_t col = 0; col < m[0].size(); ++col) {
		if(m[0][col] == 0) {
			firstRowZero = true;
			break;
		}
	}
	for(size_t row = 0; row < m.size(); ++row) {
		if(m[row][0] == 0) {
			firstColZero = true;
      break;
		}
	}
	for(size_t row = 1; row < m.size(); ++row) {
		for(size_t col = 1; col < m[0].size(); ++col) {
			if(m[row][col] == 0) {
				m[row][0] = 0;
				m[0][col] = 0;
			}
		}
	}
	for(size_t col = 1; col < m[0].size(); ++col) {
		if(m[0][col] == 0) {
			zeroCol(m, col);
		}
	}
	for(size_t row = 1; row < m.size(); ++row) {
		if(m[row][0] == 0) {
			zeroRow(m, row);
		}
	}
	if(firstRowZero) {
		zeroRow(m, 0);
	}
	if(firstColZero) {
		zeroCol(m, 0);
	}
}

void printMatrix(std::vector<std::vector<int>>& m) {
	for(const auto& row : m) {
		for(const auto& col : row) {
			std::cout << col << " ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int main() {
	std::vector<std::vector<int>> m{{1, 0, 3}, {8, 6, 5}, {6, 7, 5}};
//	std::vector<std::vector<int>> m{{0}};

	printMatrix(m);
	zeroMatrix(m);
	printMatrix(m);
}
