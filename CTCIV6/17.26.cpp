#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

struct Doc {
	int id;
	std::vector<int> data;

	Doc(const int idInput = -1, const std::vector<int>& dataInput = std::vector<int>{}) : id(idInput), data(dataInput) {}
	Doc(const Doc& in) : id(in.id), data(in.data) {};
	~Doc() {}
	Doc& operator =(const Doc& in) = delete;
};

// BF. Time O(N^2 * S), N = number of docs, S = max size of a doc's list of numbers, O(S) space
void printIfSimilar(const Doc& d1, const Doc& d2) {
	std::unordered_set<int> s;
	for(const auto& val : d1.data) {
		s.insert(val);
	}
	size_t matches = 0;
	for(const auto& val : d2.data) {
		if(s.count(val)){
			++matches;
		}
	}
	if(matches) {
		std::cout << d1.id << " : " << d2.id << " : " <<  static_cast<double>(matches) / (d1.data.size() + d2.data.size() - matches) << '\n';
	}
}

void testSimilar(const std::vector<Doc>& docs) {
	for(size_t i = 0; i < docs.size(); ++i) {
		for(size_t j = i + 1; j < docs.size(); ++j) {
			printIfSimilar(docs[i], docs[j]);
		}
	}
}

// Opt. Exploits the fact that most docs don't have overlapping data, uses reverse hash table.
std::unordered_map<int, size_t> createSizeMap(const std::vector<Doc>& docs) {
	std::unordered_map<int, size_t> res;
	for(const auto& doc : docs) {
		res[doc.id] = doc.data.size();
	}
	return res;
}

std::unordered_map<int, std::vector<int>> createRevMap(const std::vector<Doc>& docs) {
	std::unordered_map<int, std::vector<int>> res;
	for(const auto& doc : docs) {
		for(const auto& dataVal : doc.data) {
			if(!res.count(dataVal)) {
				res[dataVal] = std::vector<int>{};
			}
			res[dataVal].emplace_back(doc.id);
		}
	}
	return res;
}

struct PairMapHash {
	size_t operator()(const std::pair<int, int>& p) const {
		return p.first * 10  + p.second * 100;
	}
};

struct PairMapEquals {
	bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) const {
			return p1.first == p2.first && p1.second == p2.second;
	}
};

void incrementDocPairCounts(const std::vector<int>& docIds, std::unordered_map<std::pair<int, int>, size_t, PairMapHash, PairMapEquals>& cntMap) {
	for(size_t i = 0; i < docIds.size(); ++i) {
		for(size_t j = i + 1; j < docIds.size(); ++j) {
			std::pair<int, int> p = std::make_pair(std::min(docIds[i], docIds[j]), std::max(docIds[i], docIds[j])); // Hash is order dependent
		//	std::cout << "Pair elements are " << p.first << ", " << p.second << '\n';
			if(!cntMap.count(p)) {
				cntMap[p] = 0;
			}
			++cntMap[p];
		}
	}
}

void testSimilarOpt(const std::vector<Doc>& docs) {
	std::unordered_map<int, size_t> sizeMap = createSizeMap(docs);
	const std::unordered_map<int, std::vector<int>> revMap = createRevMap(docs);
	std::unordered_map<std::pair<int, int>, size_t, PairMapHash, PairMapEquals> cntMap;

	for(const auto& it : revMap) {
		const auto& docIds = it.second;
		if(docIds.size() > 1) {
			incrementDocPairCounts(docIds, cntMap);
		}
	}

	for(const auto& it : cntMap) {
		const auto& docId1 = it.first.first;
		const auto& docId2 = it.first.second;
		const auto& cnt = it.second;
		std::cout << docId1 << " : " << docId2 << " : " << static_cast<double>(cnt) / (sizeMap[docId1] + sizeMap[docId2] - cnt) << '\n';
	}
}

// Opt2.

int main() {
	std::vector<Doc> docs;
	docs.emplace_back(Doc(13, std::vector<int>{14, 15, 100, 9, 3}));
	docs.emplace_back(Doc(16, std::vector<int>{32, 1, 9, 3, 5}));
	docs.emplace_back(Doc(19, std::vector<int>{15, 29, 2, 6, 8, 7}));
	docs.emplace_back(Doc(24, std::vector<int>{7, 10}));
//	testSimilar(docs);
	testSimilarOpt(docs);
}
