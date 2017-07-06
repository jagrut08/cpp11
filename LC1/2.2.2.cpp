#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

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

void reverseList(const lnPtr headPtr, const lnPtr tailPtr) {
	for(lnPtr p1, p2 = headPtr, p3 = headPtr; p1 != tailPtr; p1 = p2, p2 = p3) {
		p3 = p3->next;
		p2->next = p1;
	}
}

void reverseList(lnPtr& head, const int start, const int end) {
	if(start > end) {
		throw std::runtime_error("start cannot be more than end!");
	} else if(start <= 0 ) {
		throw std::runtime_error("Invalid start!");
	}

	if(!head) {
		throw std::runtime_error("Invalid list");
	}

	lnPtr startPtr{nullptr}, beforeStartPtr{nullptr}, endPtr{nullptr}, afterEndPtr{nullptr}, tempPtr{head};

	for(int i = 1; i < start; ++i) {
		beforeStartPtr = tempPtr;
		tempPtr = tempPtr->next;
		if(!tempPtr) {
			throw std::runtime_error("start position not reachable");
		}
	}
	startPtr = tempPtr;

	for(int i = 0; i < end - start; ++i) {
		tempPtr = tempPtr->next;
		if(!tempPtr) {
			throw std::runtime_error("end position not reachable");
		}
	}
	endPtr = tempPtr;
	afterEndPtr = endPtr->next;

	reverseList(startPtr, endPtr);

	if(beforeStartPtr) {
		beforeStartPtr->next = endPtr;
	} else {
		head = endPtr;
	}
	startPtr->next = afterEndPtr;
}

void reverseListOnePass(lnPtr& head, const int start, const int end) {
	if(start > end) {
		throw std::runtime_error("start cannot be more than end!");
	} else if(start <= 0 ) {
		throw std::runtime_error("Invalid start!");
	}

	if(!head) {
		throw std::runtime_error("Invalid list");
	}

	lnPtr prevPtr{nullptr}, curPtr{head}, nextPtr{nullptr}, oneBeforeStartPtr{nullptr}, startPtr{nullptr};

	for(int i = 1; i < start; ++i) {
		oneBeforeStartPtr = curPtr;
		curPtr = curPtr->next;
		if(!curPtr) {
			throw std::runtime_error("start position not reachable");
		}
	}
	nextPtr = curPtr;
	startPtr = curPtr;
//	std::cout << curPtr->val << '\n';

	for(int i = 0; i < end - start + 1; ++i) {
		if(!nextPtr) {
			throw std::runtime_error("end position not reachable");
		}
		nextPtr = nextPtr->next;
		curPtr->next = prevPtr;
		prevPtr = curPtr;
		curPtr = nextPtr;
	}

	if(oneBeforeStartPtr) {
		oneBeforeStartPtr->next = prevPtr;
	} else {
		head = prevPtr;
	}
	startPtr->next = nextPtr;
}

int main() {
	std::vector<int> listInput{1, 2, 3};
	const int start = 3, end = 3;

	lnPtr head = createListForward(listInput);
	printList(head);
//	reverseList(head, start, end);
	reverseListOnePass(head, start, end);

	printList(head);
}
