#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
// BF: Find all substrings, O(N^2). Check each for validity.
// Keep incrementing maxLen seen. Total time complexity: O(N^2), space O(N)
// if using stack to validate well-formed string


// Time O(1.5N) as worst case, you traverse half the string to find center
// Then traverse the entire string from center outwards
size_t longestValidParen(const std::string& str) {
	if(str.empty()) {
		return 0;
	}

	size_t runLen = 0, maxLen = 0;
	int prev = -1;

	for(size_t i = 0; i < str.size() - 1; ) {
		if(str[i] == '(' && str[i + 1] == ')') {
			int first = i, last = i + 1;
			for( ; str[first] == '(' && str[last] == ')' && first >= 0 &&
				last < str.size(); --first, ++last) {}
			++first;
			--last;
			const size_t cnt = last - first + 1;
			if(prev + 1 == first) { // Continuation of previous valid seq
				runLen += cnt;
			} else {
				runLen = cnt; // New valid seq
			}

			maxLen = std::max(maxLen, runLen);
			prev = last;
			i = last + 1;
		} else {
			++i;
		}
	}
	return maxLen;
}


// From GfG. O(N) time, O(N) space
size_t longestValidParenOpt(const std::string& str) {
    int n = str.length();

    // Create a stack and push -1 as initial index to it.
    std::stack<int> stk;
    stk.push(-1);

    // Initialize result
    int result = 0;

    // Traverse all characters of given string
    for (int i=0; i<n; i++)
    {
    	// If opening bracket, push index of it
    	if (str[i] == '(')
    		stk.push(i);

    	else // If closing bracket, i.e.,str[i] = ')'
    	{
    		// Pop the previous opening bracket's index
    		stk.pop();

    		// Check if this length formed with base of
    		// current valid substring is more than max
    		// so far
    		if (!stk.empty())
    			result = std::max(result, i - stk.top());

    		// If stack is empty. push current index as
    		// base for next valid substring (if any)
    		else stk.push(i);
    	}
    }

    return result;
}
int main() {
	const std::vector<std::string> v{
		"(",
		")",
		"",
		"()",
		"()()",
		"(())",
		"(()",
		")()",
		"()(())",
		"())()",
		"()(()",
		"()((())",
		"())(())",
		")(",
		"))((",
		"))((()",
		"()(()))))",
		"((()()",
	};

	for(const auto& str : v) {
		std::cout << str << " : " << longestValidParen(str) << " : " << longestValidParenOpt(str) << '\n';
	}
}
