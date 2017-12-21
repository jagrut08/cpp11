// O(logN) time
// If there are dups, it returns the first occurrence of val
int findIndex(const std::vector<int>& v, const int val) {
	if(v.empty()) {
		return 0;
	}
	int low = 0, high = v.size() - 1, mid = 0;

	while(low <= high) { // The default for BS is <=
		mid = low + (high - low) / 2;
		if(val == v[mid]) {
			return mid;
		} else if(val > v[mid]) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return low; // Simpler than below
//	return val > v[mid] ? mid + 1 : mid;
}
