#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#define nCols 3

void sortColors(std::vector<int>& v) {
		std::array<int, nCols> f{}; // nCols should be compile time constant. Cannot use a defaulted second input arg.
		// Can also use 3 variables to track frequencies

		for(size_t i = 0; i < v.size(); ++i) {
			++f[v[i]];
		}

		size_t dst = 0;

		for(size_t j = 0; j < f.size(); ++j) {
			while(f[j]) {
				v[dst++] = j;
				--f[j];
			}
		}
}

// Partition an array into 3 sections in a single pass
void sortColorsOpt(std::vector<int>& v) {
	if(v.empty()) {
		return;
	}
	size_t li = 0, ri = v.size() - 1; // left index and right index

	for(size_t i = 0; i <= ri; ) {
		if(v[i] == 0) { // value to be moved to left section
			std::swap(v[i], v[li]);
			++i; // Increment both i and li
			++li;
		} else if (v[i] == 1) { // value to remain in middle section
			++i;
		} else { // values to move to right section
			std::swap(v[i], v[ri]);
			--ri; // Note - only right index decremented. i not incremented.
		}
	}
}

void printVector(const std::vector<int>& v, const std::string& s) {
	std::cout <<  '\n' << s << '\n';

	if(!v.size()){
		std::cout << "{}\n";
		return;
	}

	for(const auto& e : v) {
		std::cout << e << ", ";
	}
}

int main() {
	std::vector<std::vector<int>> v{
		{0, 2, 2, 1, 0, 1}, //{0, 0, 1, 1, 2, 2}
		{}, // {}
		{1},
		{1, 3},
		{0, 1, 2}, // => same
		{0, 0 , 0},
		{2, 1, 0},
		{0, 1, 2, 0},
		{2, 2, 1, 0},

	};

	for(auto& a : v) {
		printVector(a, "Before sorting: ");
		sortColorsOpt(a);
		printVector(a, "After sorting: ");
	}
}

