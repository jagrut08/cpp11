#include <iostream>
#include <vector>
#include <string>

// Compare with strtod in cstdlib
bool isNumeric(const char* str) {

	const char* p = str;
	bool dotSeen = false, sciExpr = false, digitSeen = false;

	// Skip leading spaces
	for(; *p == ' '; ++p)
	{}

	// Skip + or -, check first digit otherwise
	if(*p == '-' || *p == '+') {
		++p;
	} else if(!(*p >= '0' && *p <= '9')){
		return false;
	}

	// Central portion, the number
	for(; *p; ++p) {
		if(*p >= '0' && *p <= '9') {
			digitSeen = true;
			continue;
		} else if(*p == '.') {
			if(dotSeen || sciExpr) {
				return false;
			} else {
				dotSeen = true;
			}
		} else if(*p == 'e' || *p == 'E') {
			if(sciExpr || dotSeen) {
				return false;
			} else {
				sciExpr = true;
			}
		} else if(*p == '+' || *p == '-'){ //+ or - in central portion must be after e/E
			if(*(p - 1) != 'e' && *(p - 1)!= 'E') {
				return false;
			}
		} else {
			break; // We've hit a character that wasn't expected or the trailing spaces.
		}
	}

	// Skip trailing spaces. If the central portion had some other character, p won't move forward.
	// If p reached the end, it would be NULL char, and won't move further
	for(; *p == ' '; ++p)
	{}

	// Return true if p has reached the end and a digit was seen
	return (!*p) && digitSeen;
}

int main() {
	std::vector<std::string> v{ "0", "0.1", "8.6.9", "a67", "", " ", "1 7", "1e4", "14e", "1e.4", "1e4e5",
	"-13", "- 13", " -13", "-", ".", "e", "-e", ".e", "-.", "1e-17", "1-17", "1e+15" };

	for(const auto& str : v) {
		std::cout << str << " : " << isNumeric(str.c_str()) << '\n';
	}
}
