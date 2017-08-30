#include <iostream>
#include <vector>
#include <memory>
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

lnPtr getListTailAndLen(const lnPtr& head, size_t& len) {
	len = 1;
	lnPtr tmp = head;
 	for(; tmp->next; tmp = tmp->next) {
 		++len;
 	}
 	return tmp;
 }

 void rotateList(lnPtr& head, const int k) {
 	if(!head || !head->next || !k) {
 		return;
 	} else if(k < 0) {
 		throw std::runtime_error("Invalid k");
 	}

 	size_t len = 0;
 	lnPtr tailPtr = getListTailAndLen(head, len);

	if(!(k % len)) {
 		return;
 	}

 	int cnt = len - (k % len) - 1;
 	lnPtr cur = head;

 	for(int i = 0; i < cnt; ++i) {
 		cur = cur->next;
 	}
 	const lnPtr newHead = cur->next;
 	cur->next = nullptr;
 	tailPtr->next = head;
 	head = newHead;
 }

 int main() {
//	const std::vector<int> v{1, 2, 3};
//	const std::vector<int> v{1, 2, 3, 4, 5};
	const std::vector<int> v{1, 2};

	const int k = 5;

	lnPtr head = createListForward(v);
	std::cout << "Before: ";
	printList(head);
	rotateList(head, k);
	std::cout << "After: ";
	printList(head);
}
