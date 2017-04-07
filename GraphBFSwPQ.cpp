#include <iostream>
#include <list>
#include <unordered_set>
#include <queue>
#include <vector>
#include <unordered_map>

using std::cout;
using std::list;
using std::unordered_set;
using std::priority_queue;
using std::vector;
using std::unordered_map;

struct Graph_node {

	char value;

	Graph_node(const char c = ' ') : value(c) {}

	// Removed adj list from here as it was causing circular reference
	// Instead moved it to a Graph struct

	bool operator ==(const Graph_node& n) const {
		return value == n.value;
	}
};

struct Node_key_hash {

	size_t operator()(const Graph_node& n) const {
		return n.value;
	}
};

struct Node_key_equal {

	bool operator()(const Graph_node& A, const Graph_node& B) const {
		return A.value == B.value;
	}
};

struct Graph {
	unordered_map<Graph_node, list<Graph_node>, Node_key_hash, Node_key_equal> adj_lists;
};

// Global graph object
Graph G;

struct Pq_compare {

	bool operator()(Graph_node& A, Graph_node& B) const {

		// Sort vector underlying pq by size of adj list ascending
		// or the pq itself by size of adj list descending
		return G.adj_lists[A].size() < G.adj_lists[B].size();
	}

};

bool route_exists(const Graph_node& A, Graph_node& B) {
	
	priority_queue<Graph_node, vector<Graph_node>, Pq_compare> pq;
	unordered_set<Graph_node, Node_key_hash, Node_key_equal> visited;

	pq.emplace(A);
	visited.insert(A);

	while (!pq.empty()) {
		Graph_node elem = pq.top();

		if (B == elem) {
			return true;
		}

		pq.pop();
		const auto& adj = G.adj_lists[elem];

		for (const auto& it : adj) {
			if (it == B) {
				return true;
			}

			if (visited.count(it)) {
				continue;
			} else {
				visited.insert(it);
			}

			pq.emplace(it);
		}
	}
	return false;
}

int main() {

	Graph_node A('a');
	Graph_node B('b');
	Graph_node D('d');
	Graph_node E('e');
	Graph_node F('f');

	// Create adj lists. Shouldn't add adj list to Graph_node as the list members' adj list would be incomplete
	// Not possible to do bottom up creation of objects due to circular dependencies

	G.adj_lists.insert(make_pair(A, list<Graph_node>({D, B})));
	G.adj_lists.insert(make_pair(B, list<Graph_node>({A, D, E})));
	G.adj_lists.insert(make_pair(D, list<Graph_node>({A})));
	G.adj_lists.insert(make_pair(E, list<Graph_node>({B})));
	G.adj_lists.insert(make_pair(F, list<Graph_node>({})));

	cout << route_exists(A, F) << '\n';
}