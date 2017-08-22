#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>

struct ListNode {
	int val;
	std::shared_ptr<ListNode> next;

	ListNode(const int i, const std::shared_ptr<ListNode> nxt = nullptr) : val(i), next(nxt) {}
	ListNode(const ListNode& n) : val(n.val), next(n.next) {}
	~ListNode() {
		std::cout << "dtr for " << val << '\n';
	}
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

void removeDups(const lnPtr head) {
	if(!head) {
		throw std::runtime_error("head is null!");
	}

	for(lnPtr p1 = head, p2 = head->next; p2; p2 = p2->next) {
		if(p1->val == p2->val) {
			p1->next = p2->next; // The sub-list starting from p1->next will be isolated and
								// get reclaimed by RAII (no external refs)
		} else {
			p1 = p2;
		}
	}
}

int main() {
//	const std::vector<int> v{1, 1, 3};
//	const std::vector<int> v{1, 2, 2};
//	const std::vector<int> v{1, 2, 2, 3};

//	const std::vector<int> v{1, 1, 1, 3};
//	const std::vector<int> v{1, 2, 2, 2};
//	const std::vector<int> v{1, 2, 2, 2, 3, 3};
	const std::vector<int> v{1, 2, 2, 2, 3, 4, 4, 4};

	lnPtr head = createListForward(v);
	std::cout << "Before: ";
	printList(head);
	removeDups(head);
	std::cout << "After: ";
	printList(head);
}
