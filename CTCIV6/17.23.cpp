#include <iostream>
#include <vector>
// BF
struct Square {
	int row, col, sz;

	Square(const int r = -1, const int c = -1, const int s = -1) : row(r), col(c), sz(s) {}
	Square(const Square& s) : row(s.row), col(s.col), sz(s.sz) {}
	Square& operator = (const Square & s) = delete;
	~Square() {}
};

bool isValidRow(const std::vector<std::vector<int>>& m, const size_t rowStart, const size_t colStart, const size_t numElem) {
	for(size_t cnt = 0; cnt < numElem; ++cnt) {
		if(m[rowStart][colStart + cnt] == 0) {
			return false;
		}
	}
	return true;
}

bool isValidCol(const std::vector<std::vector<int>>& m, const size_t rowStart, const size_t colStart, const size_t numElem) {
	for(size_t cnt = 0; cnt < numElem; ++cnt) {
		if(m[rowStart + cnt][colStart] == 0) {
			return false;
		}
	}
	return true;
}

bool isValidSquare(const std::vector<std::vector<int>>& m, const size_t row, const size_t col, const size_t sz) {
	return isValidRow(m, row, col, sz) && isValidRow(m, row + sz - 1, col, sz) && isValidCol(m, row, col, sz) && isValidCol(m, row, col + sz - 1, sz);
}

Square findSquare(const std::vector<std::vector<int>>& m) {
	for(size_t n = m.size(); n > 0; --n) { // size_t ok as n won't be decremented after it reaches 0
		for(size_t row = 0; row + n <= m.size(); ++row) {
			for(size_t col = 0; col + n <= m.size(); ++col) {
				if(isValidSquare(m, row, col, n)) {
					return Square(row, col, n);
				}
			}
		}
	}
	return Square();
}

// Opt. O(N^3) time, O(N^2) space
struct Cell {
	int right, bottom;

	Cell(const int r = -1, const int b = -1) : right(r), bottom(b) {}
	Cell(const Cell& c) : right(c.right), bottom(c.bottom) {}
	Cell& operator =(const Cell& c) = delete;
	~Cell() {}
};

bool isValidSquareOpt(const std::vector<std::vector<Cell>>& p, const size_t row, const size_t col, const size_t sz) {
	const auto& topLeft = p[row][col], bottomLeft = p[row + sz - 1][col], topRight = p[row][col + sz - 1];
	return topLeft.right >= sz && topLeft.bottom >= sz && bottomLeft.right >= sz && topRight.bottom >= sz;
}

void printPreprocMatrix(const std::vector<std::vector<Cell>>& p) {
	for(size_t i = 0; i < p.size(); ++i) {
		for(size_t j = 0; j < p[0].size(); ++j) {
			std::cout << p[i][j].right <<  ":" << p[i][j].bottom << " ";
		}
		std::cout << '\n';
	}
}

std::vector<std::vector<Cell>> preprocess(const std::vector<std::vector<int>>& m) {
	std::vector<std::vector<Cell>>res (m.size(), std::vector<Cell>(m.size()));
	// The two iterations below can be combined - see page 610 for an elegant traversal.
  for(int row = m.size() - 1; row >=0; --row) {
		size_t cntRow = 0;
		for(int col = m.size() - 1; col >= 0; --col) {
			if(m[row][col] == 1) {
				++cntRow;
			} else {
				cntRow = 0;
			}
			res[row][col].right = cntRow;
		}
	}
	for(int col = m.size() - 1; col >=0; --col) {
		size_t cntCol = 0;
		for(int row = m.size() - 1; row >= 0; --row) {
			if(m[row][col] == 1) {
				++cntCol;
			} else {
				cntCol = 0;
			}
			res[row][col].bottom = cntCol;
		}
	}
	return res;
}

Square findSquareOpt(const std::vector<std::vector<int>>& m) {
	const auto& preprocMatrix = preprocess(m);
	printPreprocMatrix(preprocMatrix);
	for(size_t n = m.size(); n > 0; --n) { // size_t ok as n won't be decremented after it reaches 0
		for(size_t row = 0; row + n <= m.size(); ++row) {
			for(size_t col = 0; col + n <= m.size(); ++col) {
				if(isValidSquareOpt(preprocMatrix, row, col, n)) {
					return Square(row, col, n);
				}
			}
		}
	}
	return Square();
}
int main() {
	const std::vector<std::vector<int>> m{{0, 1, 1}, {1, 1, 0}, {1, 1, 1}};
	const auto& res = findSquare(m);
	const auto& res2 = findSquareOpt(m);
	std::cout << "\nAnswer: " << res.row << " " << res.col << " " << res.sz << '\n';
	std::cout << "\nAnswer: " << res2.row << " " << res2.col << " " << res2.sz;
}
