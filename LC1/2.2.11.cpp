#include <iostream>
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

lnPtr createList() {
	lnPtr fourPtr = std::make_shared<ListNode>(4);
	lnPtr threePtr = std::make_shared<ListNode>(3, fourPtr);
	lnPtr twoPtr = std::make_shared<ListNode>(2, threePtr);
	lnPtr onePtr = std::make_shared<ListNode>(1, twoPtr);

//	fourPtr->next = onePtr;
	return onePtr;
}


bool hasCycle(const lnPtr& head) {
	if(!head || !head->next) {
		return true;
	}

	for(lnPtr p1 = head, p2 = head->next->next; p2 && p2->next; p1 = p1->next, p2 = p2->next->next) {
		if(p1 == p2){
			return true;
		} else if(!p2->next) {
			return false;
		}
	}
	return false;
}

int main() {
	const lnPtr& head = createList();
	std::cout << hasCycle(head);
}

