bool searchSortedMatrix(const int n, const std::vector<std::vector<int>>& m)
--
{
	{3, 5, 7},
	{10, 15, 19},
	{45, 89, 99} 
}

3 => true
100 => false
7 => true
15 = true
45 => true
17 => false
8 => false
-1 => false
--
size of matrix 0, 1, 2, 
even/odd rows cols
multiple hits? no hits? 
--
bool searchSortedMatrix(n, m)
	// validation
	for each row in rows
		for each column in cols
			if element at r, c == n return true
	return false
O(N*M) time, O(1) space
--
opt
	check the first and last element of each row
	if first <= n and last >= n
		do bsearch of that row
--
opt
	start at 0,0, say r, and c
	newCol = c, newRow = r
	
	while
		if m[r][c] == n
			return true
		if m[r][c] < n 
			newCol = c + 1
			newRow = r+ 1
		if newCol or newRow is invalid, return false
		r = newRow, c = newCol
			
	return false
--
revise bsearch	
		 
	
