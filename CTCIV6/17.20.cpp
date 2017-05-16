#include <iostream>
#include <stdexcept>
#include <set>

// BF
class MedianCalc {
	std::multiset<int> s;

	public:
	void addToDataset(const int i);
	double getMedian() const;
	void printSet() const;

	MedianCalc() {}
	MedianCalc(const MedianCalc& c) = delete;
	~MedianCalc() {}
	MedianCalc& operator =(const MedianCalc& c) = delete;
};

// log(K), K = input size, space is K
void MedianCalc::addToDataset(const int i) {
	s.insert(i);
}

void MedianCalc::printSet() const {
	std::cout << "\nContents of set: ";
	for(auto it = s.cbegin(); it != s.cend(); ++it) {
		std::cout << *it << ", ";
	}
	std::cout << '\n';
}
// log(K)
double MedianCalc::getMedian() const {
	if(s.empty()){
		throw std::runtime_error("No data");
	}
	printSet();
	std::multiset<int>::iterator it = s.cbegin();
	for(size_t cnt = 0; it != s.cend() && cnt < s.size() / 2; ++it, ++cnt) {}
	const int cur = *it;
//	std::cout << "cur = " << cur << " s.size() = " << s.size() << '\n';
	if(s.size() % 2 != 0) {
		return cur;
	} else {
		const int prev = *(--it);
		return (cur + prev) / 2.0;
	}
}

// Opt
struct MaxHeapComparator {
	bool operator()(const int i, const int j) const {
		return !(i < j);
	}
};

class MedianCalcOpt {
	std::multiset<int> minHeap;
	std::multiset<int, MaxHeapComparator> maxHeap;

	public:
	double getMedian() const;
	void addToDataset(const int i);

	MedianCalcOpt() {}
	MedianCalcOpt(const MedianCalcOpt& c) = delete;
	~MedianCalcOpt() {}
	MedianCalcOpt& operator =(const MedianCalcOpt& c) = delete;
};

// O(1)
double MedianCalcOpt::getMedian() const {
	if(minHeap.empty() && maxHeap.empty()) {
		throw std::runtime_error("No data");
	}
	else if(minHeap.size() == maxHeap.size()) {
		return (*minHeap.begin() + *maxHeap.begin()) / 2.0;
	} else {
		return (*maxHeap.begin());
	}
}
// log(N) + log(M). N and M roughly equal, so log(K/2) where K = input size
void MedianCalcOpt::addToDataset(const int i) {
	if(maxHeap.empty()) { // When starting out
		maxHeap.insert(i);
		return;
	}
	if(minHeap.size() == maxHeap.size()) { // Median will top top of maxHeap. Ensure that the maxHeap has 1 more element than minHeap
		if(i < *minHeap.begin()) { // i should be placed in maxHeap itself, and highest value of maxHeap will bubble up
			maxHeap.insert(i);
		} else { // i should be placed in minHeap as it is greater than its smallest value. An element from minHeap should be moved to maxHeap so that maxHeap's size exceeds minHeap's size by 1.
				 // The value that originally was minHeap.top() will now become maxHeap.top(), and also the median.
			maxHeap.insert(*minHeap.begin());
			minHeap.erase(minHeap.begin());
			minHeap.insert(i);
		}
	} else { // Median will be avg of top of maxHeap and top of minHeap
		if(i > *maxHeap.begin()) { // i should be in minHeap. maxHeap is already larger than minHeap by 1 element, so just insert into minHeap.
			minHeap.insert(i);
		} else { // i should be min maxHeap. maxHeap is already larger than minHeap by 1 element, so transfer an element from maxHeap to minHeap.
			minHeap.insert(*maxHeap.begin());
			maxHeap.erase(maxHeap.begin());
			maxHeap.insert(i);
		}
	}
}
int main() {
	MedianCalc m;
	MedianCalcOpt o;
	//std::cout << m.getMedian() << '\n';
	m.addToDataset(1);
	o.addToDataset(1);
	std::cout << m.getMedian() << " - " << o.getMedian() << '\n';

	m.addToDataset(4);
	o.addToDataset(4);
	std::cout << m.getMedian() << " - " << o.getMedian() << '\n';

	m.addToDataset(7);
	o.addToDataset(7);
	std::cout << m.getMedian() << " - " << o.getMedian() << '\n';

	m.addToDataset(3);
	m.addToDataset(9);
	o.addToDataset(3);
	o.addToDataset(9);
	std::cout << m.getMedian() << " - " << o.getMedian() << '\n';

	m.addToDataset(9);
	o.addToDataset(9);
	std::cout << m.getMedian() << " - " << o.getMedian() << '\n';

	m.addToDataset(-1);
	o.addToDataset(-1);
	std::cout << m.getMedian() << " - " << o.getMedian() << '\n';

}
