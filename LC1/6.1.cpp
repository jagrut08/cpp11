void mergeSorted(std::vector<int>& a, const std::vector<int>& b)
--
{1, 5, 10}, {2, 6} => {1, 2, 5, 6, 10}
{2, 6}, {1, 5, 10} => ||
{}, {2, 6} => {2, 6}
{2, 6}, {} => {2, 6}
{1}, {2} => {1, 2}
{2}, {1} => {1, 2}
{2}, {2} => {2, 2}
{1, 5}, {100, 200} => {1, 5, 100, 200}
{100, 200}, {1, 5} => {1, 5, 100, 200}
{1, 100}, {10, 20} => {1, 10, 20, 100}
{10, 20}, {1, 100} => ||
--
BF
	create new vector buf of size a.size()
	maintain index ai and bi
	keep adding smaller of ai and bi to buf
	copy buf over to a
--
O(m + n) time, O(m + n) space
--
Opt O(m + n) time, O(1) space

void mergeSortedArrays(std::vector<int>& a, const std::vector<int>& b) {
	int ai = a.size() - 1, bi = b.size() - 1, dst = a.capacity() - 1;
	
	while(ai >= 0 && bi >= 0) {
		a[dst--] = a[ai] > b[bi] ? a[ai--] : b[bi--];
	}
	 
	while(bi >= 0) {
		a[dst--] = b[bi--];
	}
}

std::pair<std::vector<int>, std::vector<int>> createInput(const std::vector<int>& a, const std::vector<int>& b)

int main() {
	std::vector<vector<int>> as = {
	};
	
	std::vector<vector<int>> bs = {
	};
	
	for(size_t i = 0; i < as.size(); ++i) {
		
		printArray(as[i]);
		
		std::vector<int> newA = a.reserve(a.size() + b.size());
		mergeSortedArrays(newA, bs[i]);
		
	}
		
}

