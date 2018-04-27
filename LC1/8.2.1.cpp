std::unordered_set<std::vector<int>> findSubsets(const std::vector<int>& v)
--
{} => {{}}
{1} => {{}, {1}}
{1, 2} => {{}, {1}, {2}, {1, 2}}
{1, 1} => {{}, {1}, {1, 1}}
{2, 1, 2} => {{}, {1}, {2}, {1, 2}, {2, 2}, {1, 2, 2}}
{1, 1, 1} => {{}, {1}, {1, 1}, {1, 1, 1}}
--
f(v, i)
	if i == v.size()
		return an unordered_set with 1 element, an empty vector
	
	x =  ith elem of v 
	subsets = f(v, i + 1)
	add x to each vector in subsets, creating subsets2
	insert subsets2 into subsets, this will eliminate dups as we use unordered_set
	return subsets
--	
time and space O(2^n), unordered_set eliminates dupes 	
sort v to get subsets in non-decreasing order
--

	
	
