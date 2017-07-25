#include <iostream>
#include <cstring>

int strMatch(const char* s, const char* p, size_t k) {
	for(; k > 0 && *s && *p; --k, ++p, ++s) {
		if(*s != *p) {
			return 1;
		}
	}
	return (k > 0 ? 1 : 0);
}

char* strStr(const char* s, const char* p) {
	size_t sizeOfS = 0, sizeOfP = 0;

	if(!s || !p) {
		return NULL;
	} else {
		sizeOfS = std::strlen(s);
		sizeOfP = std::strlen(p);
		if(sizeOfP > sizeOfS) {
			return NULL;
		}
	}

	for(; *s; ++s) {
		if(!strMatch(s, p, sizeOfP)) {
			return (char*)s;
		}
	}

	return NULL;
}

int strMatch2(const char* sIter, const char* sEnd, const char* pIter) {
	for(; sIter <= sEnd; ++sIter, ++pIter) {
		if(*sIter != *pIter) {
			return 1;
		}
	}
	return 0;
}
char* strStrWithoutStrlen(const char* s, const char* p) {
	if(!s || !p) {
		return NULL;
	}

	// Maintain a rolling window marked by sBegin and sEnd
	const char* sBegin = s;
	const char* sEnd = s;
	const char* pIter = p;

	for( ; *pIter && *sEnd; ++pIter, ++sEnd) {}

	// Move sEnd one back as our checking is sBegin through sEnd, end points included
	--sEnd;

	// After traversing through s and p, p still has more characters, so p is longer than s
	if(*pIter) {
		return NULL;
	}

	for( ; *sEnd; ++sBegin, ++sEnd) {
		//std::cout << "sEnd is " << *sEnd << '\n';
		if(!strMatch2(sBegin, sEnd, p)) {
			return (char*)sBegin;
		}
	}

	return NULL;
}
int main() {
	char s[] = "abdef";
	char p[] = "ab";

	std::cout << std::strstr(s, p) << " : " << strStr(s, p) << " : " << strStrWithoutStrlen(s, p) << std::endl;
}
