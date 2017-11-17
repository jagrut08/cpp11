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


lnPtr mergeLists(const lnPtr& l1, const lnPtr& l2) {
	if(!l1) {
		return l2;
	} else if(!l2) {
		return l1;
	}

	lnPtr head = nullptr, tail = nullptr, t1 = l1, t2 = l2; // t1 and t2 are tmp ptrs over the list

	while(t1 && t2) {
		if(t1->val < t2->val) {
			if(!head) {
				head = t1;
				tail = t1;
			} else {
				tail->next = t1;
				tail = t1;
			}
			t1 = t1->next;
		} else {
			if(!head) {
				head = t2;
				tail = t2;
			} else {
				tail->next = t2;
				tail = t2;
			}
			t2 = t2->next;
		}
	}

	tail->next = (t1 ? t1 : t2);
	return head;
}

lnPtr findMidAndSplit(const lnPtr& head) {
	lnPtr fast = head, slow = head, prev = nullptr;

	while(fast && fast->next) {
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	// prev and slow are adjacent, break the link. Slow is the mid point.
	prev->next = nullptr;
	return slow;
}

void mergeSortSLL(lnPtr& head) {
	if(!head || !head->next) {
		return;
	}

	lnPtr mid = findMidAndSplit(head);
	mergeSortSLL(head);
	mergeSortSLL(mid);
	head = mergeLists(head, mid);
}

int main() {
	std::vector<std::vector<int>> v{
		{},
		{1},
		{2, 1},
		{1, 2},
		{1, 2, 2},
		{2, 2, 5, 1, 3},
		{5, 1, 3, 2, 2},
		{4, 2, 3, 5},
		{5, 4, 1},
	};

	for(const auto& val : v) {
		lnPtr h = createListForward(val);
		std::cout << "Before sorting: ";
		printList(h);
		mergeSortSLL(h);
		std::cout << "After sorting: ";
		printList(h);
		std::cout << '\n';
	}
}
