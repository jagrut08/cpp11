#include <iostream>
#include <string>
#include <vector>

std::string findLongestHelper(const size_t left, const size_t right, const std::string& s) {
	int l = left, r = right;
//	std::cout << "Starting " << left << " : " << right << '\n';

	for(; l >= 0 && r < s.size() && s[l] == s[r]; ++r, --l)
	{}

	// l or r exceeded bounds, or characters mis-matched. Go back to last match
	++l;
	--r;
//	std::cout << l << " : " << r << " : " << s.substr(l, r - l + 1) << '\n';

	return s.substr(l, r - l + 1);
}

// O(N^2) time
std::string findLongestPalSubstr(const std::string& s) {
	std::string res{};
	if(s.empty()) {
		return s;
	} else {
		res = s.substr(0, 1); // For a 1 character string, longest palindromic string is 1 char
	}

	for(size_t i = 1; i < s.size() - 1; ++i) {
		const std::string longestOdd = findLongestHelper(i - 1, i + 1, s);
		if(longestOdd.size() > res.size()) {
			res = longestOdd;
		}
		const std::string longestEven = findLongestHelper(i, i + 1, s);
		if(longestEven.size() > res.size()) {
			res = longestEven;
		}
		if(res.size() == s.size()) {
			return res;
		}
	}
	return res;
}

int main() {
	std::vector<std::string> inputs{"abcbad", "", "a", "ab", "abc", "abcb", "aba", "abbb", "abbbb", "bbbba"};
	for(const auto& input : inputs)
		std::cout << input << " : " << findLongestPalSubstr(input) << '\n';
}
