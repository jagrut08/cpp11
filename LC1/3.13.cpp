#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

std::unordered_map<std::string, std::vector<size_t>> createFreqTableMap(const std::vector<std::string>& v) {
	std::unordered_map<std::string, std::vector<size_t>> res;

	for(const auto& it : v) {
		std::vector<size_t> freqTable(26, 0);
		for(const auto& c : it) {
			if(c != ' ') {
				++freqTable[c - 'a'];
			}
		}
		res[it] = freqTable;
	}
	return res;
}

bool freqTablesMatch(const std::vector<size_t>& v1, const std::vector<size_t>& v2) {
	if(v1.size() != v2.size()) {
		throw std::runtime_error("Invalid frequency tables");
	}

	for(size_t i = 0; i < v1.size(); ++i) {
		if(v1[i] != v2[i]) {
			return false;
		}
	}
	return true;
}

std::vector<std::vector<std::string>> createVectorOfVectors(const std::unordered_map<std::string, std::vector<std::string>>& m) {
	std::vector<std::vector<std::string>> res; // If you initialize res as res(m.size), you cannot use emplace_back() below as that adds to
											   // the vector after its reserved capacity.
//	std::cout << " m size is " << m.size() << '\n';
	for(const auto& it : m) {
		if(!it.second.empty()) {
	//		std::cout << "\nAdding anagrams for " << it.first << '\n';
			res.emplace_back(it.second);
		//	res.push_back(it.second);
		}
	}
	return res;
}

// Time is O(N^2 + N*M) space is O(N*M). Another approach is to sort each string, and create a map of <sorted string, vector of original/unsorted strings>
// But that doesn't take advantage of the fact that input is guaranteed to be lower case letters or space.
std::vector<std::vector<std::string>> findAnagrams(const std::vector<std::string>& v) {
	std::unordered_map<std::string, std::vector<size_t>> mapFreqTable = createFreqTableMap(v);
	std::unordered_map<std::string, std::vector<std::string>> res;

	for(auto it = begin(mapFreqTable); it != end(mapFreqTable); ++it) { // O(N^2) time
		for(auto sec = next(it); sec != end(mapFreqTable); ) {
			if(freqTablesMatch(it->second, sec->second)) {
				if(!res.count(it->first)) {
					res[it->first] = std::vector<std::string>{it->first};
				}
				res.at(it->first).emplace_back(sec->first);
				sec = mapFreqTable.erase(sec);
			} else {
				++sec;
			}

		}
	}

	return createVectorOfVectors(res); // O(N*M) time
}


int main() {
	const std::vector<std::vector<std::string>> v{{"a", "abc", "bca"}, {"ab", "b a", "abc", "bca", "abb"}, {"a", "ab"}};
	for(const auto& strs : v) {
		std::cout << "\nStrings: ";
		for(const auto& str : strs) {
			std::cout << str << " ";
		}
		const auto& res = findAnagrams(strs);
		std::cout << "\nFound " << res.size() << " anagram groups: ";
		for(const auto& anagramGroup : res) {
			for(const auto& str : anagramGroup) {
				std::cout << str << " ";
			}
			std::cout << ", ";

		}
	}
}
