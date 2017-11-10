lnPtr mergeKSortedLists(const std::vector<lnPtr>& v)
--

{1, 10, 100}
{15, 25} 		=> {1, 10, 15, 25, 100}

{1, 10} => {1, 10}
{} => {}

{}
{1, 5} => {1, 5}

{1, 5} 
{10, 20} => {1, 5, 10, 20}

{10, 20}
{1, 5, 7} => {1, 5, 7, 10, 20}

{1, 4}
{1, 4} => {1, 1, 4, 4}
--
Opt

	iterate over all lists, add head to wLst 
	
	while(wLst not empty)
		find the smallest element of wLst // O(K)
		remove it from wLst and replace with its successor // O(1)
		add it to return list // O(1)
	
	return rHead
--
Time: O(KN) nodes processed + O(K) linear search for each node, so O(K^2N + KN))
Space: O(KN) + O(K) of wLst
 	
--
Opt
	check empty input
	create BST (std::set) of lnPtr bst
	create new return list, rHd
	
	iterate over all lists, and if not null, add head to bst 
	
	while(bst not empty)
		pop the smallest element from bst // O(1) time
		add it to return list
		add the next list node, corresponding to the node that was popped to bst, if next is not null // log(K)
 	
 	return rHd
--
K lists, N nodes max. Each node inserted into bst once.  
Time: O(KN) + (logK * KN) = KN(1 + logK)
Space: O(KN) due to return data structure space + O(K) space of bst
--
#include <iostream>
#include <vector>
#include <list>
#include <set>

struct ListNodeComparator{
	
	bool operator(const lnPtr& p1, const lnPtr& p2) const {
		return p1->val < p2->val;
	}	
} listNodeComparator;

lnPtr mergeKSortedLists(const std::vector<lnPtr>& v) {
	std::set<lnPtr, listNodeComparator> bst;
	lnPtr rHead{nullptr}, rTail{nullptr};
	
	for(lnPtr h : v) {
		if(h) {
			bst.insert(h);
		}
	}
	
	while(!bst.empty()) {
		lnPtr nxt = *bst.begin();
		if(!rHead) {
			rHead = nxt;
			rTail = nxt;
		} else {
			rTail->next = nxt;
			rTail = rTail->next;
		}
		bst.erase(bst.begin()); // Confirm if iterator works
		if(nxt->next) {
			bst.insert(nxt->next);
		}
	}
	return rHead;
}
 


