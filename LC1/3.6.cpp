#include <iostream>
#include <vector>
#include <string>

bool isMatch(const char* s, const char* p) {

	if(!*s && *p == '*' && !*(p + 1)) {
		return true;
	}
	for(; *s && *p; ++s, ++p) {
		if(*p == '*') {

			for(; *p == '*'; ++p)
			{}
			if(!*p) {
				return true;
			}
			for(; *s && *s != *p; ++s)
			{}
			if(!*s) {
				return false;
			}
		} else if(*s != *p && *p != '?') {
			return false;
		}
	}

	return (*p || *s) ? false : true;
}

int main() {
//	std::vector<std::string> s{"abc", "abc", "abc", "abc", "abc", "abcd", "abc", "abc"};
//	std::vector<std::string> p{"abc", "def", "?bc", "a?c", "ab?", "?bc", "??c", "??d"};

	std::vector<std::string> s{"abc", "abc", "abc", "abc", "abc", "abcd", "abc", "ac", "" };
	std::vector<std::string> p{"*bc", "a*c", "ab*", "a*",   "*b*", "ab*d", "a*d", "a*c", "*"};

//	std::vector<std::string> s{"aa", "aa", "ab", "aab", "abc" };
//	std::vector<std::string> p{"a",  "*", "?*", "c*a*b", "a*b*c" };
	for(size_t i = 0; i < s.size(); ++i) {
		std::cout << s[i] << " - " << p[i] << " : " << isMatch(s[i].c_str(), p[i].c_str()) << '\n';
	}
}
