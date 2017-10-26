#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

long long int evalOp(const std::string& op, const long long int opnd1, const long long int opnd2) {
	if(op == "*") {
		return opnd1 * opnd2;
	} else if(op == "+") {
		return opnd1 + opnd2;
	} else if(op == "-") {
		return opnd1 - opnd2;
	} else if(op == "/") {
		if(opnd2 == 0) {
			throw std::runtime_error("Divide by 0");
		} else {
			return opnd1 / opnd2;
		}
	} else {
		throw std::runtime_error("Invalid operand " + op);
	}
}

bool isOperator(const std::string& str) {
	return str == "*" || str == "/" || str == "+" || str == "-";
}

long long int evalRPN(const std::vector<std::string>& v) {
	std::list<long long int> stk;

	for(const auto& tok : v) {
		if(isOperator(tok)){
			if(stk.size() < 2) {
				throw std::runtime_error("Too few operands");
			}
			const long long int opnd2 = stk.back();
			stk.pop_back();
			const long long int opnd1 = stk.back();
			stk.pop_back();
			stk.push_back(evalOp(tok, opnd1, opnd2));
		} else {
			stk.push_back(std::stoll(tok));
		}
	}

	if(stk.empty()) {
		return 0;
	} else if(stk.size() != 1) {
		throw std::runtime_error("Invalid expression");
	} else {
		return stk.back();
	}
}

int main() {
	const std::vector<std::vector<std::string>> in {
		{"10", "5", "/"},
		{"2", "1", "+", "3", "*"}, // 9
		{"4", "13", "5", "/", "+"}, // 6
		{"-1", "+", "45"}, // 44
		{}, // 0
		{"1"}, // throw ex
		{"+"}, // throw ex
		{"1", "3"}, // throw ex
		{"3", "+", "+"}, //throw
		{"3", "3", "4"}, // throw
		{"5", "0", "/"}, //throw
		{"6", "-132", "/"} // 0
	};

	for(const auto& v : in) {
		for(const auto& tok : v) {
			std::cout << tok << " ";
		}
		std::cout << " : ";
		long long int res = 0;
		try {
			res = evalRPN(v);
			std::cout << res << '\n';
		} catch(const std::exception& e) {
			std::cout << e.what() << '\n';
		}
	}
}
