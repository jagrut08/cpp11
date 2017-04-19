#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>

std::unordered_set<std::string> createSet(const std::vector<std::string>& wds) {
	std::unordered_set<std::string> res;
	for(const auto& wd : wds) {
		res.insert(wd);
	}
	return res;
}
// Sort descending by string (word) size
bool wdsComparator(const std::string& wd1, const std::string& wd2) {
	return wd1.size() > wd2.size();
}

bool isValidCompositeWd(const std::string& wd, const std::unordered_set<std::string>& dict, const bool isMainWd) {
	if(!isMainWd) {
		return dict.count(wd) > 0;
	}

	for(size_t i = 0; i < wd.size(); ++i) {
		const std::string left = wd.substr(0, i);
		const std::string rt = wd.substr(i);
		if(dict.count(left) && isValidCompositeWd(rt, dict, false)) {
			return true;
		}
	}
	return false;
}

std::string findLongestWdRecur(std::vector<std::string>& wds) {
	std::unordered_set<std::string> dict = createSet(wds);
	std::sort(wds.begin(), wds.end(), wdsComparator);
	for(const auto& wd : wds) {
	//	std::cout << "Trying " << wd << '\n';
		if(isValidCompositeWd(wd, dict, true)) {
			return wd;
		}
	}
	return "";
}

std::string findLongestWdIter(std::vector<std::string>& wds) {
	std::unordered_set<std::string> dict = createSet(wds);
	std::sort(wds.begin(), wds.end(), wdsComparator); // If it's a list, can do l.sort(l.begin(), l.end(), wdsComparator)

	for(const auto& wd : wds) {
		//std::cout << "Trying " << wd << '\n';
		size_t count = 0, start = 0;
		for(size_t end = 0; end < wd.size(); ++end) {
			const std::string left = wd.substr(start, end);
			if(dict.count(left)) {
				count += end - start + 1;
				start = end;
			}
		}
		if(count == wd.size()) {
			return wd;
		}
	}
	return "";
}

int main() {
	//std::vector<std::string> wds {"the", "fox", "jump", "jumped", "jumpedover", "foxthe"};
	//std::vector<std::string> wds {"the", "fox", "jumped", "thefox"};
	std::vector<std::string> wds {};

	std::cout << "Answer (recursive): " << findLongestWdRecur(wds) << '\n';
	std::cout << "Answer (iterative): " << findLongestWdIter(wds);

}
