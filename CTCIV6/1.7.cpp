#include <iostream>
#include <vector>

void printMatrix(const std::vector<std::vector<int>>& v) {
	for(size_t i = 0; i < v.size(); ++i) {
		for(size_t j = 0; j < v[0].size(); ++j) {
			std::cout << v[i][j] << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void rotateInPlace(std::vector<std::vector<int>>& v) {
	for(size_t start = 0, end = v.size() - 1; start < v.size() / 2; ++start, --end) { // end is last row/column, start is first row/col
		for(size_t offset = 0; offset < end - start; ++offset) { // start + offset should not reach end
			const int temp = v[start][start + offset]; // swap counter clockwise for clockwise rotation of matrix (90 degrees)
			v[start][start + offset] = v[end - offset][start];
			v[end - offset][start] = v[end][end - offset];
			v[end][end - offset] = v[start + offset][end];
			v[start + offset][end] = temp;
		}
	}
}

int main() {
	std::vector<std::vector<int>> v{{1, 2}, {3, 4}};
	//std::vector<std::vector<int>> v{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//		std::vector<std::vector<int>> v{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

	printMatrix(v);
	rotateInPlace(v);
	printMatrix(v);
}

