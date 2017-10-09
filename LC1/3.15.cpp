#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

size_t lengthOfLastWord(const std::string& str) {

	std::string::const_reverse_iterator end{}, start{}, it{};
	/*Notes
	1) The helper crbegin(str) doesn't exist!
	2) Reverse iteration is also from rbegin()->rend()!
	3) Prefer an index-based solution, without iterators first.
	Iterators have many syntax gotchas.
	*/

	// This is similar to find_if(rbegin(), rend(), ::isalpha);
	for(it = str.crbegin(); it != str.crend(); ++it) {
		if(*it != ' ') {
			end = it;
			break;
		}
	}

	if(it == str.crend()) {
		return 0;
	}

	// This is similar to find_if_not(start, rend(), ::isalpha);
	for(; it != str.crend(); ++it) {
		if(*it == ' ') {
			start = it;
			break;
		}
	}

	if(it == str.crend()) {
		start = str.crend();
	}

//	std::cout << *start << " : " << *end << '\n';
	// distance requires positive increment from first to second
	// end -> start is positive if iterators are reverse iterators
	// It returns num chars between start and end, including char at
	// start location but not at end
	return std::distance(end, start);
}

size_t lengthOfLastWordSimple(const std::string& str) {
	int it = -1, start = -1, end = -1;

	for(it = str.size() - 1; it >= 0; --it) {
		if(str[it] != ' ') {
			end = it;
			break;
		}
	}

	// Ending char not found
	if(it == -1) {
		return 0;
	}

	for(; it >= 0; --it) {
		if(str[it] == ' ') {
			start = it + 1;
			break;
		}
	}

	// Ending char found, but not starting char, so
	// Assume starting char is first char
	if(it == -1) {
		start = 0;
	}

//	std::cout << start << " " << end << '\n';
	return end - start + 1;
}

size_t lengthOfLastWordOpt(const std::string& str) {
	auto first = std::find_if(str.rbegin(), str.rend(), ::isalpha);
	auto last = std::find_if_not(first, str.rend(), ::isalpha);
	return std::distance(first, last);
}

int main() {
	const std::vector<std::string> v{
		"Hello World", "Hello", " Hello",
		"Hello ",
		"Hel lo", "", " "
	};
	for(const auto& val : v) {
		std::cout << val << " : " << lengthOfLastWord(val) << '\n';
		std::cout << val << " : " << lengthOfLastWordSimple(val) << '\n';
		std::cout << val << " : " << lengthOfLastWordOpt(val) << '\n';

		std::cout << '\n';
	}
}
