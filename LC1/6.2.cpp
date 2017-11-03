#include <iostream>
#include <memory>
#include <vector>

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

lnPtr mergeSortedSLLs(lnPtr& h1, lnPtr& h2) {
	if(!h1 && !h2) {
		return nullptr;
	} else if(!h1) {
		return h2;
	} else if(!h2) {
		return h1;
	}

	lnPtr l1Nxt = h1, l2Nxt = h2, cur, retHead;

	if(l1Nxt->val < l2Nxt->val) {
		cur = l1Nxt;
		l1Nxt = l1Nxt->next;
	} else {
		cur = l2Nxt;
		l2Nxt = l2Nxt->next;
	}

	retHead = cur;

	while(l1Nxt || l2Nxt) {

//		std::cout << "cur value " << (cur ? cur->val : -1) << " l1Nxt value " << (l1Nxt ? l1Nxt->val : -1) << " l2Nxt value " << (l2Nxt ? l2Nxt->val : -1) << '\n';

		if(l1Nxt && l2Nxt) {
			if(l1Nxt->val < l2Nxt->val) {
				cur->next = l1Nxt;
				l1Nxt = l1Nxt->next;
			} else {
				cur->next = l2Nxt;
				l2Nxt = l2Nxt->next;
			}
			cur = cur->next; // Missed this! Algo had it
		} else if(l1Nxt) {
			cur->next = l1Nxt;
			break;
		} else {
			cur->next = l2Nxt;
			break;
		}
	}
	return retHead;
}

int main() {
	std::vector<std::vector<int>> l1s = {
	{1, 10},
	{},
	{},
	{1, 10},
	{1},
	{2},
	{1, 2},
	{10, 11},
	{1, 100},
	{20},
	{2, 3, 5},
	{1, 100},
	};

	std::vector<std::vector<int>> l2s = {
		{3, 20},
		{},
		{1, 10},
		{},
		{2},
		{1},
		{10},
		{11},
		{1, 2},
		{20},
		{1, 100},
		{3, 4}
	};

	for(size_t i = 0; i < l1s.size(); ++i) {
		lnPtr h1 = createListForward(l1s[i]), h2 = createListForward(l2s[i]);
		printList(h1);
		printList(h2);
		lnPtr newHead = mergeSortedSLLs(h1, h2);
		std::cout << "Merged list: ";
		printList(newHead);
		std::cout << '\n';
	}
}

