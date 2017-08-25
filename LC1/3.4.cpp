#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

std::string padString(const std::string& str, const size_t n) {
	std::stringstream ss; // If you construct ss as ss(std::string(n, '0')), and do ss << str, str overwrites original content
	ss << std::string(n, '0') << str;
	return ss.str();

	/*
	std::string buf(n, '0');
	buf.append(str);
	return buf;
	*/
}

std::string addBinary(const std::string& first, const std::string& second) {
	if(first.empty()) {
		return second;
	} else if(second.empty()) {
		return first;
	}

	std::string firstNew = first, secondNew = second;

	if(first.size() > second.size()) {
		secondNew = padString(second, first.size() - second.size());
	} else if(second.size() > first.size()) {
		firstNew = padString(first, second.size() - first.size());
	}

//	std::cout << firstNew << " : " << secondNew << '\n';
	std::string res(firstNew.size() + 1, '0');
	int carry = 0;

	for(int i = firstNew.size() - 1; i >= 0; --i) {
		int sum = carry + (firstNew[i] - '0') + (secondNew[i] - '0');

		switch (sum) {
			case 0: {
						carry = 0;
						res[i + 1] = '0'; // Index into res is 1 more than index into firstNew and secondNew!
						break;
					}
			case 1: {
						carry = 0; // Carry is actually sum / 2
						res[i + 1] = '1'; // res[i + 1] is actually sum % 2
						break;
					}
			case 2: {
						carry = 1;
						res[i + 1] = '0';
						break;
					}
			case 3: {
						carry = 1;
						res[i + 1] = '1';
						break;
					}
			default: {
						throw std::runtime_error("Unexpected characters in input");
					}
		}

	//	std::cout << "Added " << firstNew[i] << " and " << secondNew[i] << ", result is " << res[i] << " carry " << carry << '\n';
	}

	if(carry == 1) {
		res[0] = '1';
	}
	return res;
}

int main() {
//	const std::string first = "11", second = "1";
//	const std::string first = "1", second = "1";
	const std::string first = "11", second = "11";

	std::cout << addBinary(first, second);
}
