#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <list>

// Generic Trie routines
struct TrieNode {
	std::unordered_map<char, std::shared_ptr<TrieNode>> chars; // Tried unique_ptr but will need to implement move semantics across the code
	bool isTerminal;

	TrieNode() : isTerminal(false) {}
	TrieNode(const TrieNode& t) : chars(t.chars), isTerminal(t.isTerminal) {}
	TrieNode& operator =(const TrieNode& t) = delete;
	~TrieNode() {}
};
	
typedef std::shared_ptr<TrieNode> TrieNodePtr;

void printTrie(const TrieNodePtr& head) {
	TrieNodePtr temp = head;
	std::list<TrieNodePtr> cur;

	for(const auto& child : head->chars) {
			std::cout << child.first << '\t';
			cur.push_back(child.second);
	}

	std::cout << '\n';
	for(; !cur.empty(); ) {
		std::list<TrieNodePtr> next;
		for(; !cur.empty(); ) {
			const TrieNodePtr p = cur.front();
			for(const auto& child : p->chars) {
				std::cout << child.first << (child.second->isTerminal? "(*)" : "" ) << '\t';
				next.push_back(child.second);
			}
			cur.pop_front();
		}
		cur = next;
		std::cout << '\n';
	}
}
void insertIntoTrie(const TrieNodePtr& head, const std::string& str) {
	TrieNodePtr temp = head;
	for(const auto& c : str) {
		if(!temp->chars.count(c)) {
			temp->chars[c] = std::make_shared<TrieNode>();
		}
		temp = temp->chars[c];
	}
	temp->isTerminal = true;
}

TrieNodePtr createTrie(const std::vector<std::string>& v) {
	const TrieNodePtr head = std::make_shared<TrieNode>();
	for(const auto& str : v) {
		insertIntoTrie(head, str);
	}
	return head;
}

bool isInTrie(const TrieNodePtr& head, const std::string& str) {
	TrieNodePtr temp = head;
	for(const auto& c : str) {
		if(!temp->chars[c]) {
			return false;
		}
		temp = temp->chars[c];
	}
	return true;
}
// end Trie routines

std::vector<std::string> generateSuffixes(const std::string& str) {
	std::vector<std::string> res;
	for(size_t start = 0; start < str.size(); ++start) {
			res.emplace_back(str.substr(start));
	}
	return res;
}

// Optimized Trie approach. Complexity O(T * k + b * k)
std::vector<std::string> bigStrSearchTrieOpt(const std::string& b, const std::vector<std::string>& T) {
	std::vector<std::string> res;
	if(b.empty() || T.empty()) {
		return res;
	}
	TrieNodePtr head = createTrie(T), temp = head;
	for(size_t start = 0; start < b.size(); ++start) {
		for(size_t end = start; end < b.size(); ++end) {
			if(temp->chars[b[end]]) {
				temp = temp->chars[b[end]];
				if(temp->isTerminal) {
					res.emplace_back(b.substr(start, end - start + 1));
				}
			} else {
				temp = head;
				break;
			}
		}
	}

//	printTrie(head);
	return res;
}

// Trie approach. Complexity O(b * b + T * k)
std::vector<std::string> bigStrSearchTrie(const std::string& b, const std::vector<std::string>& T) {
	std::vector<std::string> res;
	if(b.empty() || T.empty()) {
		return res;
	}
	TrieNodePtr head = createTrie(generateSuffixes(b));
	for(const auto& str : T) {
		if(isInTrie(head, str)) {
			res.emplace_back(str);
		}
	}
	return res;
}

bool isSubstr(const std::string& b, const std::string& str) {
	for(size_t start = 0; start <= b.size() - str.size(); ++start) {
		if(b.substr(start, str.size()) == str) {
			return true;
		}
	}
	return false;
}

// BF. Complexity O(b * T * k), where k = max length string in T
std::vector<std::string> bigStrSearchBF(const std::string& b, const std::vector<std::string>& T) {
	std::vector<std::string> res;
	if(b.empty() || T.empty()) {
		return res;
	}
	for(const auto& str : T) {
		if(isSubstr(b, str)) {
			res.emplace_back(str);
		}
	}
	return res;
}

int main() {
	const std::vector<std::string> T{"the", "good", "jumped", "jump"};
	const std::string b{"thefoxjumpedgoo"};

	//const std::vector<std::string> T{"i", "is", "pp", "ms"};
	//const std::string b{"mississippi"};

//	const std::vector<std::string> res = bigStrSearchBF(b, T);
//	const std::vector<std::string> res = bigStrSearchTrie(b, T);
	const std::vector<std::string> res = bigStrSearchTrieOpt(b, T);

	for(const auto& str : res) {
		std::cout << str << " ";
	}
	std::cout << '\n';
}
