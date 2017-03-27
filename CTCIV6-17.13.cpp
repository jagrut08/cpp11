#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_set>
#include <limits>
#include <unordered_map>

struct Result {
	std::string parsed;
	size_t mismatch;

	Result() : parsed(""), mismatch(0) {}

	Result(const std::string& r, const size_t mm) : parsed(r), mismatch(mm) {}

	Result(const Result& r) : parsed(r.parsed), mismatch(r.mismatch) {}

	~Result() {}

	Result& operator =(const Result& r) {

		if(this == &r) {
			return *this;
		}

		parsed = r.parsed;
		mismatch = r.mismatch;
		return *this;
	}
};

Result doUnconcat(const std::unordered_set<std::string>& dict, const std::string& str, std::unordered_map<std::string, Result>& table) {

	if(table.count(str)) {
		return table[str];
	}

	Result result {str, str.size()};

	for(size_t i = 1; i <= str.size(); ++i) {
		const std::string prefix = str.substr(0, i);
		const std::string suffix = str.substr(i);

		const size_t mismatchPre = (!dict.count(prefix) ? prefix.size() : 0);
		const Result sufResult = doUnconcat(dict, suffix, table);

		if(mismatchPre + sufResult.mismatch < result.mismatch) {
			result.mismatch =  mismatchPre + sufResult.mismatch;
			result.parsed = prefix + " " + sufResult.parsed;
		}
	}

	table[str] = result;

	return table[str];
}

void printTable(std::unordered_map<std::string, Result>& table) {

	std::cout << "\nPrinting table:\n";

	for(const auto& it : table) {
		std::cout << it.second.parsed << ", " << it.second.mismatch << '\n';
	}
}
std::string unconcat(const std::unordered_set<std::string>& dict, const std::string& str) {

	if(dict.empty() || str.empty()) {
		return str;
	}

	std::unordered_map<std::string, Result> table;

	const Result result = doUnconcat(dict, str, table);

	std::cout << "\nAnswer: " << result.parsed << ", " << result.mismatch << '\n';
	printTable(table);
	return result.parsed;
}

int main() {
	//std::unordered_set<std::string> dict{"looked", "just", "like", "her", "brother"};
	//std::string str {"jesslookedjustliketimherbrother"};


	std::unordered_set<std::string> dict{"this", "is", "awesome", "a", "we", "some"};
	std::string str {"thisisawesome"};

//	std::unordered_set<std::string> dict{"a", "dog", "to"};
//	std::string str {"ad"};

	unconcat(dict, str);
}

