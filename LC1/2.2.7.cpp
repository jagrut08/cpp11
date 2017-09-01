#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

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
void removeFromEnd(lnPtr& head, const int n) {
	if(!head) {
		throw std::runtime_error("Invalid list");
	}
	lnPtr cur = head, tmp = head;
	for(size_t i = 0; i < n; ++i) {
		cur = cur->next;
	}

	if(cur) {
		for(; cur->next; cur = cur->next, tmp = tmp->next)
		{}
		tmp->next = nullptr;
	} else {
		head = nullptr;
	}
}

int main() {
//	const std::vector<int> v{1, 2, 3}, n{1, 2, 3};
	const std::vector<int> v{1, 2, 3, 4, 5, 6}, n{1, 2, 3};

	for(const auto& val : n) {
		lnPtr head = createListForward(v);
		std::cout << "Before: ";
		printList(head);
		removeFromEnd(head, val);
		std::cout << "After: ";
		printList(head);
	}
}
