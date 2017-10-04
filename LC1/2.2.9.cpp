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
	int i = 0;
	for(lnPtr tmp = head; tmp; tmp = tmp->next) {
		std::cout << tmp->val;
		if(tmp->next) {
			std::cout << "->";
		}
		++i;
		if(i > 10) {
			std::cout << "Infinite loop in PrintList!";
			std::terminate();
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


void reverseList(const lnPtr& startPtr, const lnPtr& endPtr) {

	// Note predicate here. You only want to reverse until endPtr, not the whole list!
	for(lnPtr prevPtr{}, curPtr = startPtr, nextPtr = startPtr; prevPtr != endPtr; prevPtr = curPtr, curPtr = nextPtr) {
			nextPtr = curPtr->next;
			curPtr->next = prevPtr;
	}
}

void reverseNodesK(lnPtr& head, const int k) {
	if(k <= 0 || !head) {
		return;
	}

	lnPtr prevPtr{};
	for(lnPtr startPtr = nullptr, endPtr = nullptr, nextPtr = head; nextPtr; ) {
		startPtr = nextPtr;
		endPtr = startPtr;

	//	std::cout << "startPtr " << startPtr->val << '\n';

		for(int i = 0; i < k - 1; ++i) {
			endPtr = endPtr->next;
			if(!endPtr) {
				return;
			}
		}

		nextPtr = endPtr->next;
	//	std::cout << "endPtr " << endPtr->val << '\n';
	//	std::cout << "nextPtr " << nextPtr->val << '\n';

		reverseList(startPtr, endPtr);

		if(head == startPtr) {
			head = endPtr;
	//		std::cout << "Setting head to " << head->val << '\n';
		}

		if(prevPtr) {
			prevPtr->next = endPtr;
		}
		prevPtr = startPtr;
	//	std::cout << "prevPtr " << prevPtr->val << '\n';
		startPtr->next = nextPtr;
//		printList(head);
//		return;
	}
}

int main() {
//	const std::vector<int> arr{1, 2, 3, 4}, kValues{2, 3, 4, 5};
	const std::vector<int> arr{1, 2, 3, 4, 5}, kValues{2, 3, 4, 5};

	for(const auto& k : kValues) {
		std::cout << "k is " << k << '\n';
		lnPtr head = createListForward(arr);
		std::cout << "Before: ";
		printList(head);
		reverseNodesK(head, k);
		std::cout << "After: ";
		printList(head);
	}
}

