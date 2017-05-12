#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <set>
#include <list>

int findSeq(const std::unordered_set<int>& numSet, const std::vector<int>& longer, const size_t i) {
	std::unordered_set<int> tempSet{numSet};
	for(size_t start = i; start < longer.size(); ++start) {
		if(tempSet.count(longer[start])) {
			tempSet.erase(longer[start]);
		}
		if(tempSet.empty()) {
			return start;
		}
	}
	return -1;
}

std::unordered_set<int> createSet(const std::vector<int>& v) {
	std::unordered_set<int> res;
	for(const auto& elem : v) {
		res.insert(elem);
	}
	return res;
}

std::pair<int, int> findShortestSuperseqBF(const std::vector<int>& shorter, const std::vector<int>& longer) {
	int resBegin = -1, resEnd = -1, resLen = std::numeric_limits<int>::max();

	if(shorter.size() > longer.size()) {
		throw std::runtime_error("Shorter array is longer than the longer array");
	}
	const std::unordered_set<int> numSet = createSet(shorter);
	for(int i = 0; i <= longer.size() - shorter.size(); ++i) {
		if(!numSet.count(longer[i])) {
			continue;
		}
		const int end = findSeq(numSet, longer, i);
		if(end != -1 && end - i + 1 < resLen) {
			resLen = end - i + 1;
			resEnd = end;
			resBegin = i;
		}
	}
	return std::make_pair(resBegin, resEnd);
}

// O(S * L) time, O(S * L) space
std::pair<int, int> findShortestSuperseqOpt(const std::vector<int>& shorter, const std::vector<int>& longer) {
	std::vector<std::vector<int>>temp(shorter.size(), std::vector<int>(longer.size() + 1, -1));
	for(size_t j = 0; j < shorter.size(); ++j) {
		for(int i = longer.size() - 1; i >= 0; --i) {
			temp[j][i] = (longer[i] == shorter[j] ? i : temp[j][i + 1]);
		}
	}
	int minLen = std::numeric_limits<int>::max(), resEnd = -1, resBeg = -1;
	for(size_t i = 0; i < longer.size(); ++i) {
		int maxIdx = std::numeric_limits<int>::min();
		bool isValid = true;
		for(size_t j = 0; j < shorter.size(); ++j) {
			if(temp[j][i] == -1) {
				isValid = false;
				break;
			}
			maxIdx = std::max(temp[j][i], maxIdx);
		}
		if(isValid && maxIdx - i + 1 < minLen) {
			minLen = maxIdx - i + 1;
			resBeg = i;
			resEnd = maxIdx;
		}
	}
	return std::make_pair(resBeg, resEnd);
}

// O(S * L) time, O(L) space
std::pair<int, int> findShortestSuperseqOpt2(const std::vector<int>& shorter, const std::vector<int>& longer) {
	std::vector<int> temp(longer.size(), 0);
	for(size_t i = 0; i < shorter.size(); ++i) {
		int nextVal = -1;
		for(int j = longer.size() - 1; j >= 0; --j) {
			if(longer[j] == shorter[i]) {
				nextVal = j;
			}
			if((nextVal == -1 || temp[j] < nextVal) && temp[j] != -1) {
				temp[j] = nextVal;
			}
		}
		std::cout << "\nAfter processing " << shorter[i] << " : ";
		for(const auto& val : temp) {
			std::cout << val << " ";
		}
	}
	int resBeg = -1, resEnd = -1, minLen = std::numeric_limits<int>::max();
	for(size_t i = 0; i < temp.size(); ++i) {
		if(temp[i] != -1 && temp[i] - i < minLen) {
			resBeg = i;
			resEnd = temp[i];
			minLen = temp[i] - i;
		}
	}
	return std::make_pair(resBeg, resEnd);
}

// Most optional. Space = O(L + S), Time = O(logS * L)
struct Node {
	int longerIdx, shorterVal; // longerIdx is index of a value from the shorter array (shorterVal) in the longer array
	Node(const int i = -1, const int j = -1) : longerIdx(i), shorterVal(j) {}
	Node(const Node& n) : longerIdx(n.longerIdx), shorterVal(n.shorterVal){}
	~Node() {}
	Node& operator =(const Node& n) = delete;

};
typedef std::shared_ptr<Node> NodePtr;
typedef std::list<NodePtr> NodePtrList;

struct NodeComparator {
	bool operator ()(const NodePtr& a, const NodePtr& b) const {
		return a->longerIdx < b->longerIdx;
	}
};

std::pair<int, int> findShortestSuperseqOpt3(const std::vector<int>& shorter, const std::vector<int>& longer) {
	int resBeg = -1, resEnd = -1, minIdx = -1, maxIdx = -1, minLen = std::numeric_limits<int>::max();

	// Map of <value in shorter array, pointer to a list, the list contains pointers to Node objects
	std::unordered_map<int, std::unique_ptr<NodePtrList>> sMap;
	for(const auto& val : shorter) {
		sMap[val] = nullptr;
	}
	std::set<NodePtr, NodeComparator> minHeap;
	for(int i = 0; i < longer.size(); ++i) {
		const int val = longer[i];
		if(sMap.count(val)) { // This value was in the shorter array
			const NodePtr newNodePtr = std::make_shared<Node>(Node(i, val));
			if(!sMap[val]) { // If value doesn't already have a list of indexes associated with it
				sMap[val] = std::make_unique<NodePtrList>();
				minHeap.insert(newNodePtr);
				maxIdx = std::max(maxIdx, i);
			}
			// Add pointer to new node to the list for val.
			sMap[val]->push_back(newNodePtr);
		}
	}
	for(const auto& it : sMap) {
		std::cout << it.first << " : ";
		const NodePtrList lst = *(it.second);
		for(auto& ptr : lst) {
			std::cout << ptr->longerIdx << " ";
		}
		std::cout << '\n';
	}
	while(!minHeap.empty()){
		const NodePtr& minNodePtr = *(minHeap.begin());
		minIdx = minNodePtr->longerIdx;
		minHeap.erase(minHeap.begin());
		std::cout << "minIdx " << minIdx << " maxIdx " << maxIdx << '\n';
		if(maxIdx - minIdx < minLen) {
			minLen = maxIdx - minIdx;
			resBeg = minIdx;
			resEnd = maxIdx;
		}
		NodePtrList& lst = *(sMap[minNodePtr->shorterVal]);
		lst.pop_front();
		if(!lst.empty()) {
			const NodePtr& temp = lst.front();
			minHeap.insert(temp);
			maxIdx = std::max(maxIdx, temp->longerIdx);
		} else {
			break;
		}
	}
	return std::make_pair(resBeg, resEnd);
}

int main() {
//	const std::vector<int> shorter{2, 3}, longer{1, 2, 4, 5, 2, 3}; // Ans is 4, 5
	const std::vector<int> shorter{1, 5, 9}, longer{7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7}; // Ans is 7, 10

//	const auto& res = findShortestSuperseqBF(shorter, longer);
//	const auto& res = findShortestSuperseqOpt(shorter, longer);
//	const auto& res = findShortestSuperseqOpt2(shorter, longer);
	const auto& res = findShortestSuperseqOpt3(shorter, longer);

	std::cout << "\nAnswer: " << res.first << ", " << res.second << '\n';
}
