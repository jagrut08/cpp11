#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// BF. O(N^6) time.
struct SubMatrix {
	int startRow, endRow, startCol, endCol;
	long long elemSum;

	SubMatrix(int sr = -1, int er = -1, int sc = -1, int ec = -1, long long es = std::numeric_limits<int>::min()) : startRow(sc), endRow(er), startCol(sc), endCol(ec), elemSum(es) {}
	SubMatrix(const SubMatrix& s) : startRow(s.startRow), endRow(s.endRow), startCol(s.startCol), endCol(s.endCol), elemSum(s.elemSum) {}
	~SubMatrix() {}
	SubMatrix& operator =(const SubMatrix& s) {
		if(this != &s) {
			startRow = s.startRow;
			endRow = s.endRow;
			startCol = s.startCol;
			endCol = s.endCol;
			elemSum = s.elemSum;
		}
		return *this;
	}
};

SubMatrix findSubMatrixSum(const size_t startRow, const size_t endRow, const size_t startCol, const size_t endCol, const std::vector<std::vector<int>>& m) {
	long long res = 0;
	//std::cout << "\nAdding: (" << startRow << ", " << startCol << ") until (" << endRow << ", " << endCol << ")\n";
	for(size_t i = startRow; i <= endRow; ++i) {
		for(size_t j = startCol; j <= endCol; ++j) {
		//	std::cout << "(" << i << ", "<< j<< ") = " << m[i][j];
			res += m[i][j];
		}
	}
	//std::cout << " Sum is " << res << '\n';
	return SubMatrix(startRow, endRow, startCol, endCol, res); // Return object by value, calls cctor to copy over object
}

SubMatrix findMaxSum(const std::vector<std::vector<int>>& m) {
	SubMatrix res;
	for(size_t rowStart = 0; rowStart < m.size(); ++rowStart) {
		for(size_t rowEnd = rowStart; rowEnd < m.size(); ++rowEnd) {
			for(size_t colStart = 0; colStart < m[0].size(); ++colStart) {
				for(size_t colEnd = colStart; colEnd < m[0].size(); ++colEnd) {
					const auto& tempRes = findSubMatrixSum(rowStart, rowEnd, colStart, colEnd, m);
				//	std::cout << "\nTemp Answer: " << tempRes.startRow << ", " << tempRes.startCol << " - " << tempRes.endRow << ", " << tempRes.endCol << " - " << tempRes.elemSum << '\n';
					if(res.elemSum < tempRes.elemSum) {
						res = tempRes; // Copy assign
					//	std::cout << "\nNew Answer: " << res.startRow << ", " << res.startCol << " - " << res.endRow << ", " << res.endCol << " - " << res.elemSum << '\n';
					}
				}
			}
		}
	}
	return res;
}

// Opt. O(N^3) time, O(N) space.
SubMatrix findMaxSubArray(const size_t rowStart, const size_t rowEnd, const std::vector<long long>& cumArr) {
	long long runSum = 0, maxSeen = std::numeric_limits<long long>::min();
	int start = -1, end = -1, maxStart = -1, maxEnd = -1;
	for(size_t i = 0; i < cumArr.size(); ++i) {
		runSum += cumArr[i];
		if(runSum < 0) {
			runSum = 0;
			start = end = -1;
		} else{
			if(-1 == start) {
				start = i;
			}
			end = i;
			if(runSum > maxSeen) {
				maxSeen = runSum;
				maxStart = start;
				maxEnd = end;
			}
		}
	}
	return SubMatrix(rowStart, rowEnd, maxStart, maxEnd, maxSeen);
}

SubMatrix findMaxSumOpt(const std::vector<std::vector<int>>& m) {
	SubMatrix res;
	std::vector<long long> cumArr(m.size(), 0);
	for(size_t rowStart = 0; rowStart < m.size(); ++rowStart) {
		std::fill(cumArr.begin(), cumArr.end(), 0);
		for(size_t rowEnd = rowStart; rowEnd < m.size(); ++rowEnd) {
			for(size_t col = 0; col < m[0].size(); ++col) {
				cumArr[col] += m[rowEnd][col];
			}

			const auto& tempRes = findMaxSubArray(rowStart, rowEnd, cumArr);
			//	std::cout << "\nTemp Answer: " << tempRes.startRow << ", " << tempRes.startCol << " - " << tempRes.endRow << ", " << tempRes.endCol << " - " << tempRes.elemSum << '\n';
			if(res.elemSum < tempRes.elemSum) {
					res = tempRes; // Copy assign
				//	std::cout << "\nNew Answer: " << res.startRow << ", " << res.startCol << " - " << res.endRow << ", " << res.endCol << " - " << res.elemSum << '\n';
			}
		}
	}
	return res;
}

int main() {
	const std::vector<std::vector<int>> m{{1, 2, 3}, {-1, 5, 4}, {6, 7, 0}};
	const auto& res = findMaxSum(m);
	std::cout << "\nAnswer: (" << res.startRow << "," << res.startCol << ") - (" << res.endRow << "," << res.endCol << "): " << res.elemSum << '\n';
	const auto& resOpt = findMaxSumOpt(m);
	std::cout << "\nAnswer: (" << resOpt.startRow << "," << resOpt.startCol << ") - (" << resOpt.endRow << "," << resOpt.endCol << "): " << resOpt.elemSum << '\n';
}



