#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <list>

//std::string simplifyPath(const std::string& path) {
std::string simplifyPath(const std::vector<std::string>& tokens) {
//	const std::vector<std::string> tokens = tokenizePath(path); // std::getline() from <iostream> preferred to tokenize
	std::list<std::string> lst;
	std::stringstream res;

	for(const auto& token : tokens) {
		if(token == ".") {
			continue;
		} else if(token == "..") {
			if(!lst.empty()){
				lst.pop_back();
			}
		} else {
			lst.push_back(token);
		}
	}

	if(lst.empty()) {
		res << "/";
	} else {
		for(const auto& str : lst){
			res << str << "/";
		}
	}
	return res.str();
}

int main() {
	std::vector<std::vector<std::string>> paths{

		{".."}, // returns /
		{"home"},
		{"a", "b", "c"},
		{"a", ".", "b", "..", "..", "c"},
		{"/"},
		{""},

	//	{"a", "..", ".."}, // Invalid path not handled!
		{"a", "..", "a"},
		{"a", ".."},

	};

	for(const auto& pathTokens : paths) {
		for(const auto& tok : pathTokens)
			std::cout << tok << "/";
		std::cout << " => " << simplifyPath(pathTokens) << '\n';
	}
}


