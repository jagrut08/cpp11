
#include <iostream>
#include <vector>
#include <stdexcept>

size_t removeElement(const int k, std::vector<int>& v) {

	if(v.empty()) {
		throw std::runtime_error("Empty input");
	}

	size_t dst = 0;
	for(size_t src = 0; src < v.size(); ++src) {
		if(v[src] != k) {
			if(src != dst) {
				v[dst] = v[src];
			}
			++dst;
		}
	}

	return dst;
}

int main() {

	std::vector<int> v{2, 3, 4, 3, 5, 3, 3, 6};
	const int k = 3;
	const size_t len = removeElement(k, v);

	for(size_t i = 0; i < len; ++i) {
		std::cout << v[i] << " ";
	}
}