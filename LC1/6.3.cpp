#include <iostream>
#include <memory>
#include <vector>
#include <set>

struct ListNode {
	int val;
	std::shared_ptr<ListNode> next;

	ListNode(const int v) : val(v), next(nullptr) {}
	ListNode(const ListNode& n) : val(n.val), next(n.next) {}
	~ListNode() {}
	ListNode& operator =(const ListNode& n) = delete;
};

typedef std::shared_ptr<ListNode> lnPtr;

void printList(const lnPtr head) {
	if(!head) {
		std::cout << "{}\n";
		return;
	}
	for(lnPtr tmp = head; tmp; tmp = tmp->next) {
		std::cout << tmp->val;
		if(tmp->next) {
			std::cout << "->";
		}
	}
	std::cout << '\n';
}

// {1, 2, 3} => 1 -> 2 -> 3
lnPtr createListForward(const std::vector<int>& v) {
	lnPtr tailPtr{nullptr}, headPtr{nullptr};
	for(const auto& val : v) {
		if(!tailPtr) {
			tailPtr = std::make_shared<ListNode>(val);
			headPtr = tailPtr;
		} else {
			tailPtr->next = std::make_shared<ListNode>(val);
			tailPtr = tailPtr->next;
		}
	}
	return headPtr;
}
struct ListNodeComparator{
	bool operator <(const lnPtr& p1, const lnPtr& p2) const {
		return p1->val < p2->val;
	}
} listNodeComparator;

/*
 * K lists, N nodes max. Each node inserted into bst once.
Time: O(KN) + (logK * KN) = KN(1 + logK)
Space: O(KN) due to return data structure space + O(K) space of bst
 *
 * */
lnPtr mergeKSortedLists(const std::vector<lnPtr>& v) {
	std::set<lnPtr, listNodeComparator> bst; // If you don't provide a comparator it should still work, but sort based on shared_ptr addresses!
	lnPtr rHead{nullptr}, rTail{nullptr};

	for(lnPtr h : v) {
		if(h) {
			bst.insert(h);
		}
	}

	while(!bst.empty()) {
		lnPtr nxt = *bst.begin();
		if(!rHead) {
			rHead = nxt;
			rTail = nxt;
		} else {
			rTail->next = nxt;
			rTail = rTail->next;
		}
		bst.erase(bst.begin()); // Confirm if iterator works
		if(nxt->next) {
			bst.insert(nxt->next);
		}
	}
	return rHead;
}

int main() {
	const std::vector<std::vector<int>> vals{
		{1, 10, 100},
		{15, 25}
	}

	std::vector<lnPtr> lists;
	for(const auto & val : vals) {
		lnPtr h = createForwardList(val);
		printList(h);
		lists.emplace_back(h);
	}

	lnPtr res = mergeKSortedLists(lists);
	std::cout << "Merged:\n";
	printList(res);
}

///
lnPtr mergeKSortedLists(const std::vector<lnPtr>& v)
--

{1, 10, 100}
{15, 25} 		=> {1, 10, 15, 25, 100}

{1, 10} => {1, 10}
{} => {}

{}
{1, 5} => {1, 5}

{1, 5} 
{10, 20} => {1, 5, 10, 20}

{10, 20}
{1, 5, 7} => {1, 5, 7, 10, 20}

{1, 4}
{1, 4} => {0, 1, 1, 4, 4, 7}
{0, 7}

{1, 7} => 1, 7

{1, 5, 89}
{9, 78}
{0, 7 100}
{7 45}
--
BF

	iterate over all lists, add head to wLst 
	
	while(wLst not empty)
		find the smallest element of wLst // O(K)
		remove it from wLst and replace with its successor // O(1)
		add it to return list // O(1)
	
	return rHead
--
Time: O(KN) nodes processed + O(K) linear search for each node, so O(K^2N + KN))
Space: O(KN) + O(K) of wLst
 	
--
--

