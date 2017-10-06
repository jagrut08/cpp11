#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

struct ListNode {
	std::string key;
	int value;
	std::shared_ptr<ListNode> prev, next;

	ListNode(const std::string& k, const int val) : key(k), value(val), prev(nullptr), next(nullptr) {}
	ListNode(const ListNode& n)  = delete;
	~ListNode() {}
	ListNode& operator =(const ListNode& n) = delete;
};

typedef std::shared_ptr<ListNode> lnPtr;

// Using DLL as it allows for constant time addition to head, and constant time removal from any position in the list
// if there's a ptr to that Node

// Can use built in std::list - see Approach spreadsheet

// To Do - templatize class, so key could be any compliant type
class LRUCache {
public:
	explicit LRUCache(const size_t c = 3) : cap(c), sz(0), head(nullptr), tail(nullptr) {}
	~LRUCache() {}
	LRUCache(const LRUCache& in) = delete;
	LRUCache& operator =(const LRUCache& in) = delete;

	int get(const std::string& key);
	void set(const std::string& key, const int value);
	void printCache();

private:
	size_t cap, sz;
	lnPtr head, tail;
	std::unordered_map<std::string, lnPtr> cMap;

	void removeFromList(const lnPtr& p);
	void addToHead(const lnPtr& p);
};

void LRUCache::addToHead(const lnPtr& p) {
	if(!head) {
		tail = p;
	} else {
		p->next = head;
		head->prev = p;
	}
	head = p;
}

void LRUCache::removeFromList(const lnPtr& p) {
	const lnPtr before = p->prev, after = p->next;
	if(before) {
		before->next = after;
	}

	if(after) {
		after->prev = before;
	}

	if(p == head) {
		head = after;
	}

	if(p == tail) {
		tail = before;
	}
}

void LRUCache::printCache() {
	std::cout << "\nCache values: ";
	for(lnPtr tmp = head; tmp; tmp = tmp->next) {
		std::cout << "(" << tmp->key << ", " << tmp->value << ")";
		if(tmp->next) {
			std::cout << "->";
		}
	}
	std::cout << '\n';
}

int LRUCache::get(const std::string& key) {
	if(!cMap.count(key)) {
		return -1;
	}
	const lnPtr p = cMap[key];

	if(p != head) {
		removeFromList(p);
		addToHead(p);
	}

	return head->value;
}

void LRUCache::set(const std::string& key, const int value) {
	if(cMap.count(key)){ // Node exists in cache, will be updated. Not increasing size.
		const lnPtr p = cMap[key];

		if(p != head) {
			removeFromList(p);
			addToHead(p);
		}

		if(head->value != value) {
			head->value = value;
		}
	} else { // New node will be added. Size increases, so check against threshold.

		if(sz == cap && tail) {
			removeFromList(tail);
		}

		cMap[key] = std::make_shared<ListNode>(key, value);
		addToHead(cMap[key]);
		++sz;
	}
}

int main() {
	LRUCache c(3);
	c.printCache();

	c.set("a", 1);
	std::cout << "Inserted a";
	c.printCache();

	std::cout << "\nGetting a = " << c.get("a");
	std::cout << "\nGetting z = " << c.get("z");
	c.set("b", 2);
	std::cout << "\nInserted b";
	c.printCache();

	std::cout << "\nGetting a = " << c.get("a");
	c.printCache();

	c.set("c", 3);
	std::cout << "Inserted c";
	c.printCache();

	c.set("d", 4);
	std::cout << "Inserted d";
	c.printCache();


	std::cout << "\nGetting a = " << c.get("a");
	c.printCache();

}
