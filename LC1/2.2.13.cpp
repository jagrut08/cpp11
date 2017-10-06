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

lnPtr reverseList(lnPtr& start) {
	lnPtr prev = nullptr, cur = start, next = start;

	while(cur) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	return prev;
}

void reorderList(const lnPtr& head) {
	if(!head || !head->next) {
		return;
	}

	lnPtr slow = head, fast = head, prev = nullptr;

	while(fast && fast->next){
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	lnPtr secHead = reverseList(prev->next);
	prev->next = nullptr;

	for(lnPtr p1 = head, p2 = secHead, p1Next = nullptr, p2Next = nullptr; p1 && p2; p1 = p1Next, p2 = p2Next) {
		p1Next = p1->next;
		p2Next = p2->next;

		p1->next = p2;
		if(p2 && p1Next) {
			p2->next = p1Next;
		}
	}
}

int main() {
	const std::vector<std::vector<int>> v{{1}, {1, 2}, {1, 2, 3}, {1, 2, 3, 4}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5, 6}};
	for(const auto& arr : v) {
		lnPtr head = createListForward(arr);
		std::cout << "Before: ";
		printList(head);
		reorderList(head);
		std::cout << "After: ";
		printList(head);
		std::cout << '\n';
	}
}
