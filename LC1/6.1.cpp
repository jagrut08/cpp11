#include <iostream>
#include <vector>

void mergeSortedArrays(std::vector<int>& a, const std::vector<int>& b) {

	int ai = a.size() - 1; // Get the last location of a
	a.resize(a.size() + b.size());  // Now make a bigger so that it can accommodate b

	int bi = b.size() - 1, dst = a.size() - 1; // Get the last location of b and expanded a.

//	std::cout << "Indexes: " << ai << " " << bi << " " << dst << '\n';
	while(ai >= 0 && bi >= 0) {
		a[dst--] = a[ai] > b[bi] ? a[ai--] : b[bi--];
	}

	while(bi >= 0) {
		a[dst--] = b[bi--];
	}
}

void printArray(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{}\n";
		return;
	}

	for(const auto& val : v) {
		std::cout << val << " ";
	}
	std::cout << '\n';
}

int main() {
	const std::vector<std::vector<int>> as = {
		{1, 5, 10},
				{2, 6},
				{},
				{2, 6},
				{1},
				{2},
				{2},
				{100, 200},
				{1, 5},
				{1, 100},
				{10, 20},


	};

	const std::vector<std::vector<int>> bs = {
		{2, 6},
			{1, 5, 10},
	{2, 6},
	{},
	{2},
	{1},
	{2},
	{1, 5},
	{100, 200},
	{10, 20},
	{1, 100},


	};

	for(size_t i = 0; i < as.size(); ++i) {
		printArray(as[i]);
		printArray(bs[i]);
		std::vector<int> newA = as[i];
	//	newA.reserve(as[i].size() + bs[i].size()); // Not useful; writes to locations beyond a.size() - 1 are ignored.
		mergeSortedArrays(newA, bs[i]);
		std::cout << "After: ";
		printArray(newA);
		std::cout << '\n';
	}
}

