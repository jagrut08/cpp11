
#include <iostream>
#include <stdexcept>
#include <memory>
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

void deleteDups(lnPtr& head) {
	if(!head) {
		return;
	}

	for(lnPtr p0, p1 = head, p2 = head->next; p2; ) {

		if(p1->val == p2->val) {
			for(; p2 && p1->val == p2->val; p2 = p2->next)
			{}

			if(p0) {
				p0->next = p2;
			} else {
				head = p2;
			}

			p1 = p2;
			if(p1) {
				p2 = p1->next;
			} else {
				break;
			}

		} else {
			p0 = p1;
			p1 = p2;
			p2 = p2->next;
		}

	}
}
// If/else optimization over deleteDups
void deleteDups2(lnPtr& head) {
	if(!head) {
		return;
	}

	for(lnPtr p0, p1 = head, p2 = head->next; p2; ) {
		if(p1->val == p2->val) {
			for(; p2 && p1->val == p2->val; p2 = p2->next)
			{}

			if(p0) {
				p0->next = p2;
			} else {
				head = p2;
			}

		} else {
			p0 = p1;
		}
		p1 = p2;
		if(p1) {
			p2 = p1->next;
		}
	}
}


int main() {
//	const std::vector<int> v{1, 2, 2};
//	const std::vector<int> v{1, 2, 2, 3};
//	const std::vector<int> v{1, 1, 2 };
//	const std::vector<int> v{1, 1};
//	const std::vector<int> v{1, 1, 2, 2};
//	const std::vector<int> v{1};
//	const std::vector<int> v{1, 2, 2, 2};
//	const std::vector<int> v{1, 1, 1, 2};
//	const std::vector<int> v{1, 2, 2, 2, 3};
//	const std::vector<int> v{1, 2, 2, 2, 3, 4, 4, 6};
	const std::vector<int> v{1, 2, 2, 2, 3, 4, 4, 6, 6};


	lnPtr head = createListForward(v);
	std::cout << "Before: ";
	printList(head);
	deleteDups2(head);
	std::cout << "After: ";
	printList(head);
}
