#include <iostream>
#include <stdexcept>
#include <vector>

// D = num digits. O(D) time and space.
std::vector<int> addOne(const std::vector<int>& digits) {
	if(digits.empty()) {
		throw std::runtime_error("Empty input");
	}
	std::vector<int> res(digits.size() + 1, 0);
	int resIdx = digits.size(), carry = 1;
	for(int i = digits.size() - 1; i >= 0; --i) {
		const int newRes = carry + digits[i];
		res[resIdx--] = newRes % 10;
		carry = (newRes > 9? 1 : 0); // At this point, if you write newRes back into digits, it can be done in place with O(1) space
	}
	if(carry) {
		res[resIdx] = carry;
	} else {
		res.erase(res.begin());
	}
	return res;
}

int main() {
	//const std::vector<int> digits{3, 9};
	const std::vector<int> digits{1, 0, 3};
//	const std::vector<int> digits{9};

	const auto& res = addOne(digits);
	for(const auto& d : res) {
		std::cout << d;
	}
}
