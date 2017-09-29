#include <iostream>
#include <memory>
#include <string>

 struct ListNode {
	int val;
	std::shared_ptr<ListNode> next;

	ListNode(const int i, const std::shared_ptr<ListNode> nxt = nullptr) : val(i), next(nxt) {}
	ListNode(const ListNode& n) : val(n.val), next(n.next) {}
	~ListNode() {}
	ListNode& operator =(const ListNode& n) = delete;
};

typedef std::shared_ptr<ListNode> lnPtr;

lnPtr createList() {
	lnPtr fourPtr = std::make_shared<ListNode>(4);
	lnPtr threePtr = std::make_shared<ListNode>(3, fourPtr);
	lnPtr twoPtr = std::make_shared<ListNode>(2, threePtr);
	lnPtr onePtr = std::make_shared<ListNode>(1, twoPtr);

	fourPtr->next = twoPtr;
	return onePtr;
}
// CTCI
lnPtr findCycleNode(const lnPtr& head) {
	lnPtr slow = head, fast = head;

	while(fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;

		if(fast == slow) {
			break;
		}
	}

	if(!fast || !fast->next) {
		return nullptr;
	}

	slow = head;

	while(slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}

	return fast;
}


int main() {
	const lnPtr& head = createList();
	const lnPtr node = findCycleNode(head);
	std::cout << (node ? std::to_string(node->val) : "No cycle");
}

