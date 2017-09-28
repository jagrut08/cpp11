#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <map>
#include <vector>

std::string toRoman(const int n) {
	if(n < 1 || n > 3999) {
		throw std::runtime_error("Invalid input");
	}

	const std::map<int, std::string> rMap{
		{1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, {10, "X"}, {40, "XL"},
		{50, "L"}, {90, "XC"},  {100, "C"}, {400, "CD"}, {500, "D"}, {900, "CM"},  {1000, "M"}
	};
	std::stringstream ret;
	std::map<int, std::string>::const_reverse_iterator iter = crbegin(rMap);

	for(int tmp = n; tmp; tmp -= iter->first) {
		for(; tmp < iter->first; ++iter) {
		}
		ret << iter->second;
	}
	return ret.str();
}

int main() {
	const std::vector<int> v{1, 3999, 33, 16, 100, 65};

	for(const auto& val : v)
		std::cout << val << " : " << toRoman(val) << '\n';
}

/*
1 => I
10 => X
3999 => MMMCMXCIX
33 => XXXIII
16 => XVI
65 => LXV
*/
