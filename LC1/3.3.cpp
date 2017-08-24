#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <limits>

bool isDigit(const char c) {
	return c >= '0' && c <= '9';
}

int atoiNew(const char* s) {
	const int base = 10;
	int negFlag = 1;
	const char* p = s;
	for(; *p; ++p) {
		if(*p == ' ') {
			continue;
		} else if(*p == '-') {
			negFlag = -1;
			++p;
			break;
		} else if(*p == '+') {
			++p;
			break;
		} else if(isDigit(*p)) {
			break;
		} else {
			return 0;
		}
	}

	if(!*p) {
		return 0;
	}

	int retVal = 0;
	int intMax = std::numeric_limits<int>::max();

	for(; *p; ++p) {
		if(isDigit(*p)) {

			// If the correct value is > INT_MAX or < INT_MIN, return INT_MAX or INT_MIN

			if(retVal > intMax / 10 || (retVal == intMax / 10 && (*p - '0') > intMax % 10) ) {
				return negFlag == 1 ? intMax : std::numeric_limits<int>::min();
			} else {
				retVal = retVal * base + (*p - '0');
			}
		}
		else {
			break;
		}
	}

	return retVal * negFlag;
}

int main() {

//	const char* str = "12";
//	const char* str = "-12";
//	const char* str = "12.34";
//	const char* str = "12.99";
//	const char* str = "  12";
//	const char* str = "12 ";
//	const char* str = "1 2";
//	const char* str = " ";
//	const char* str = "";
//	const char* str = "*12";
//	const char* str = "2e3";
//	const char* str = "+12";
const char* str = "2147483648"; // INT_MAX + 1

	std::cout << atoi(str) << std::endl;
	std::cout << atoiNew(str);
}
