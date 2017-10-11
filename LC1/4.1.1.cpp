#include <iostream>
#include <string>
#include <list>
#include <vector>

bool isOpeningBrace(const char c) {
	return c == '{' || c == '(' || c == '[';
}

bool isValidPair(const char o, const char c) {
	return (o == '{' && c == '}') || (o == '(' && c == ')') || (o == '[' && c == ']');
}

bool isValid(const std::string& str) {
	if(str.size() % 2) { // Optimization
		return false;
	}

	std::list<char> stk;

	for(const auto& c : str) {
		if(isOpeningBrace(c)) {
			stk.push_back(c);
		} else {
			if(stk.empty()) {
				return false;
			}
			const char p = stk.back();
			stk.pop_back();
			if(!isValidPair(p, c)) {
				return false;
			}
		}
	}
	return stk.empty(); // This is required to handle cases like "(){{"
}

// Another neat solution:
/*
 * public boolean isValid(String s) {
	Stack<Character> stack = new Stack<Character>();
	for (char c : s.toCharArray()) {
		if (c == '(')
			stack.push(')');
		else if (c == '{')
			stack.push('}');
		else if (c == '[')
			stack.push(']');
		else if (stack.isEmpty() || stack.pop() != c)
			return false;
	}
	return stack.isEmpty();
}
 */


int main() {
	const std::vector<std::string> v{
		"()",
		"()[]",
		"([])",
		"{[}]", // This should be false. You could use 3 counters and track the last seen opening brace. However,
				// tracking the last seen opening brace will require storage as it could be several chars behind.
				// Any time an opening-closing pair are matched off, the last seen needs to go one before last seen,
				// requiring a linked list or stack type of storage
		"{",
		"",
		"{]{",
		"({})",
		"([]{[]})",
		"(){{"
	};
	std::cout << std::boolalpha;

	for(const auto& str : v) {
		std::cout << str << " : " << isValid(str) << '\n';
	}
}


