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

void swapNodePairs(lnPtr& head) {
	for(lnPtr p = head, q{}, prev{}; p; p = p->next) {
		q = p->next;
		if(!q) {
			throw std::runtime_error("Odd sized list!");
		}
		p->next = q->next;
		q->next = p;

		if(head == p) {
			head = q;
		}

		if(prev) {
			prev->next = q;
		}
		prev = p;
	}
}

int main() {
	const std::vector<std::vector<int>> v{{1, 2, 3, 4}, {1, 2}, {}, {1}};

	for(const auto& arr : v) {
		lnPtr head = createListForward(arr);
		std::cout << "Before: ";
		printList(head);
		swapNodePairs(head);
		std::cout << "After: ";
		printList(head);
	}
}
