#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include <algorithm>

std::string longestCommonPrefix(const std::vector<std::string>& v) {
	if(v.empty()) {
		throw std::runtime_error("Empty input");
	}

	size_t cnt = 0, minLen = std::numeric_limits<size_t>::max();

	for(const auto& str : v) { // O(N), N = number of strings
		minLen = std::min(minLen, str.size());
	}

	for(; cnt < minLen; ++cnt) { // O(X * N), X = min length of string
		const char c = v[0][cnt];
		for(size_t i = 1; i < v.size(); ++i) {
			if(v[i][cnt] != c) {
				break;
			}
		}
	}
	return v[0].substr(0, cnt);
}

int main() {

	const std::vector<std::vector<std::string>> in{
		{"abcd", "abc", "abe"}, {"abc", "abc", "abc"}, {"abc", "a"}, {""}, {"abc", "def", "ghi"}, {"pqr"}, {"abc", ""}};
	for(const auto& vec : in) {
		std::cout << longestCommonPrefix(vec) << '\n';
	}
}
