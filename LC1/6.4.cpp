#include <iostream>
#include <memory>
#include <vector>

struct ListNode {
	int val;
	std::shared_ptr<ListNode> next;

	ListNode(const int i, const std::shared_ptr<ListNode> nxt = nullptr) : val(i), next(nxt) {}
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

lnPtr getDst(const lnPtr& head, const lnPtr& n) {
	lnPtr prev = nullptr, cur = head;

	while(cur->val <= n->val && cur != n) {
		prev = cur;
		cur = cur->next;
	}
	return prev;
}

// O(N^2) time, O(1) space
void insertionSort(lnPtr& head) {
	if(!head) {
		return;
	}

	lnPtr prev = head, cur = head->next;

	while(cur) {
		lnPtr dst = getDst(head, cur);

		if(dst == prev) {
			prev = cur;
		} else if(!dst) { // This could be merged with the below block if we use a dummy node before head
			prev->next = cur->next;
			cur->next = head;
			head = cur;
		} else {
			prev->next = cur->next;
			cur->next = dst->next;
			dst->next = cur;
		}
		cur = prev->next;
	}
}

int main() {
	const std::vector<std::vector<int>> v{
		{},
		{1},
		{2, 1},
		{1, 2},
		{2, 2},
		{3, 3, 1, 9, 5, 5},
		{1, 10, 5},
		{1, 5, 10},
		{10, 1, 5},
		{10, 5, 1},
		{5, 1, 10},
		{5, 10, 1},

	};
	for(const auto& arr : v) {
		lnPtr head = createListForward(arr);
		std::cout << "\nBefore sorting: ";
		printList(head);
		insertionSort(head);
		std::cout << "After sorting: ";
		printList(head);
		std::cout << '\n';
	}
}
