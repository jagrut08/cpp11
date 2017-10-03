#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

// Time complexity is O(N^2). Space appears to be more than O(N^2)..inconclusive.
std::string decorate(const std::string& str) {
	std::stringstream ss;
	//std::cout <<str << '\n';
	for(size_t start = 0, end = 0; end < str.size(); ) {
		for(; end < str.size() && str[start] == str[end]; ++end) {}
		ss << (end - start) << str[start]; // Note how it's end - start and not end - start + 1
										// end has advanced 1 position when the condition fails
		start = end;
	}

	//std::cout << ss.str() << '\n' << '\n';
	return ss.str();
}

std::string countAndSay(const int n) {
	if(n <= 0) {
		throw std::runtime_error("Invalid input");
	}
	std::string res{"1"};

	for(int i = 1; i < n; ++i) {
		res = decorate(res);
	}
	return res;
}

int main() {
	const int end = 50;
	for(int i = 1; i <= end; ++i) {
		const auto& res = countAndSay(i);
		std::cout << i << " : " << res.size() << '\n';
	}
}

