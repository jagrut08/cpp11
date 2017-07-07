#include <iostream>
#include <string>
#include <cctype>

bool isValidPalindromeExAlpha(const std::string& str) {
	if(str.empty()) {
		return true;
	}

	for(size_t startIdx = 0, endIdx = str.size() - 1; startIdx < endIdx; ) {
		if(std::isalnum(str[startIdx]) && std::isalnum(str[endIdx])) {
			if(std::tolower(str[startIdx]) != std::tolower(str[endIdx])) {
				return false;
			} else {
				++startIdx;
				--endIdx;
			}
		} else if(!std::isalnum(str[startIdx])) {
			++startIdx;
		} else {
			--endIdx;
		}
	}
	return true;
}

int main() {
	const std::string str{"a man, a plan, a canal: panama"};
	std::cout << isValidPalindromeExAlpha(str) << '\n';
}
