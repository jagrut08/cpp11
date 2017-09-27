#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

 struct ListNode {
	int val;
	std::shared_ptr<ListNode> next, addPtr;

	ListNode(const int i, const std::shared_ptr<ListNode> nxt = nullptr) : val(i), next(nxt), addPtr(nullptr) {}
	ListNode(const ListNode& n) : val(n.val), next(n.next), addPtr(n.addPtr) {}
	~ListNode() {}
	ListNode& operator =(const ListNode& n) = delete;
};

 typedef std::shared_ptr<ListNode> lnPtr;

lnPtr createList() {
	lnPtr threePtr = std::make_shared<ListNode>(3);
//	lnPtr twoPtr = std::make_shared<ListNode>(2, threePtr);
	lnPtr onePtr = std::make_shared<ListNode>(1, threePtr);


//	onePtr->addPtr = threePtr;
//	twoPtr->addPtr = threePtr;
	threePtr->addPtr = onePtr;

	return onePtr;
}

void printList(const lnPtr& head) {
	for(lnPtr tmp = head; tmp; tmp = tmp->next) {
		std::cout << tmp->val << (tmp->next ? "->" : "");
	}
	std::cout << "\nAdd Ptr\n";
	for(lnPtr tmp = head; tmp; tmp = tmp->next) {
		std::cout << tmp->val << " : " << (tmp->addPtr ? std::to_string(tmp->addPtr->val) : "" ) << '\n';
	}
}

// O(N) time, O(N) space because it returns a duplicate of the list, and also creates an unordered_map
lnPtr deepCopyList(lnPtr& head) {

	lnPtr newHead{}, newTmpPtr{};
	std::unordered_map<lnPtr, lnPtr> addrMap;

	addrMap[nullptr] = nullptr;

	for(lnPtr tmpPtr = head; tmpPtr; tmpPtr = tmpPtr->next) {
		const lnPtr newNodePtr = std::make_shared<ListNode>(tmpPtr->val);
		addrMap[tmpPtr] = newNodePtr;

		if(newTmpPtr) {
			newTmpPtr->next = newNodePtr;
		}

		newTmpPtr = newNodePtr;

		if(!newHead) {
			newHead = newTmpPtr;
		}
	}

	newTmpPtr = newHead;

	for(lnPtr tmpPtr = head; tmpPtr && newTmpPtr; tmpPtr = tmpPtr->next, newTmpPtr = newTmpPtr->next) {
		newTmpPtr->addPtr = addrMap[tmpPtr->addPtr];
	}

	return newHead;
}
// Duplicate each node of original list, set addPtrs, disentangle dups from original list.
// O(N) time, O(N) space because it returns a duplicate of the list. No map.
lnPtr deepCopyListOpt(lnPtr& head) {
	for(lnPtr tmp = head; tmp; tmp = tmp->next->next) {
		tmp->next = std::make_shared<ListNode>(tmp->val, tmp->next);
	}


	for(lnPtr tmp = head; tmp; tmp = tmp->next->next) {
		tmp->next->addPtr = tmp->addPtr? tmp->addPtr->next : nullptr;
	}

	lnPtr newHead{};
	for(lnPtr tmp = head; tmp; tmp = tmp->next) {
		if(!newHead) {
			newHead = tmp->next;
		}

		const lnPtr dup = tmp->next;
		tmp->next = dup->next;
		dup->next = dup->next? dup->next->next : nullptr; // Bug: don't check for dup->next->next!
		// If dup->next is nullptr, then evaluating the expression dup->next->next will fail.
	}

	return newHead;

}
int main() {
	lnPtr head = createList();
	std::cout << "Before: \n";
	printList(head);
	const lnPtr& newHead = deepCopyListOpt(head);
//	const lnPtr& newHead = deepCopyList(head);

	std::cout << "\nAfter: \n";
	printList(newHead);
}
