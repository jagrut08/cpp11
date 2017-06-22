#include <iostream>
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

lnPtr createListFromNumber(const int num) {
	std::vector<int> v;
	for(int n = num; n; n /= 10) {
			v.emplace_back(n % 10);
	}
	return createListForward(v);
}

lnPtr addLists(const lnPtr h1, const lnPtr h2) {
	int carry = 0;
	lnPtr headPtr{nullptr}, tailPtr{nullptr};
	for(lnPtr p1 = h1, p2 = h2; p1 || p2; p1 = (p1 ? p1->next : nullptr), p2 = (p2 ? p2->next : nullptr)) {
		int v1 = (p1 ? p1->val : 0);
		int v2 = (p2 ? p2->val : 0);
		int res = v1 + v2 + carry;
		carry = res > 9 ? 1 : 0;
		res %= 10;

		if(!tailPtr) {
			tailPtr = std::make_shared<ListNode>(res);
			headPtr = tailPtr;
		} else {
			tailPtr->next = std::make_shared<ListNode>(res);
			tailPtr = tailPtr->next;
		}
	}
	if(carry == 1) {
		tailPtr->next = std::make_shared<ListNode>(carry);
	}
	return headPtr;
}

int main() {
	const int first = 342, sec = 465;
//	const int first = 2, sec = 34;
//	const int first = 9, sec = 9;

	lnPtr h1 = createListFromNumber(first), h2 = createListFromNumber(sec);
//	printList(h1);
//	printList(h2);
	lnPtr res = addLists(h1, h2);
	printList(res);
}
