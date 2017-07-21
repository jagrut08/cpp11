#include <iostream>
#include <memory>
#include <stdexcept>
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

void addNodeToList(lnPtr& head, lnPtr& tail, lnPtr nodePtr) {
	if(!head) {
		head = nodePtr;
		tail = nodePtr;
	} else {
		tail->next = nodePtr;
		tail = nodePtr;
	}
}

void partitionSLL(lnPtr& head, const int x) {
	if(!head) {
		throw std::runtime_error("Invalid list");
	}

	lnPtr preHead{}, preTail{}, postHead{}, postTail{};

	for(lnPtr curPtr = head, nextPtr = head; curPtr; curPtr = nextPtr) {
		nextPtr = nextPtr->next; // Note that nextPtr should never be nullptr before calling this!
		curPtr->next = nullptr;
		if(curPtr->val < x) {
			addNodeToList(preHead, preTail, curPtr);
		} else {
			addNodeToList(postHead, postTail, curPtr);
		}
	}

	if(preTail) {
		preTail->next = postHead;
	}

	head = (preHead ? preHead : postHead);
}

int main() {
	const std::vector<int> v{5, 7, 2};
	const int x = 7;

	lnPtr head = createListForward(v);
	std::cout << "Before: ";
	printList(head);
	partitionSLL(head, x);
	std::cout << "After: ";
	printList(head);
}
