#include <iostream>
#include <string>
#include <vector>

void printRect(const size_t h, const std::vector<std::string> dict, std::vector<std::string> curRect) {
	if(curRect.size() == h) {
		for(const auto& s : curRect) {
			std::cout << s << '\n';
		}
		std::cout << '\n';
		return;
	}

	for(size_t i = 0; i < dict.size(); ++i) {
		curRect.push_back(dict[i]);
		printRect(h, dict, curRect);
		curRect.pop_back();
	}
}

int main() {
	const std::vector<std::string> dict{"ab", "cd", "ef", "gh"};
	std::vector<std::string> curRect;
	printRect(3, dict, curRect);

}
