#include <iostream>
#include <stdexcept>
#include <vector>

// BF O(N^2) time
bool tryRoute(const std::vector<int>& gas, const std::vector<int>& cost, const size_t idx) {
	long long int curGas = 0;
	for(size_t i = 0; i < gas.size(); ++i){
		size_t actualIdx = (idx + i) % gas.size();
		curGas += gas[actualIdx] - cost[actualIdx];
		if(curGas < 0) {
			return false;
		}
	}
	return true;
}
int canTravel(const std::vector<int>& gas, const std::vector<int>& cost) {
	if(gas.size() != cost.size() || gas.empty()) {
		throw std::runtime_error("Invalid input");
	}
	for(size_t i = 0; i < gas.size(); ++i) {
		if(tryRoute(gas, cost, i)) {
			return i;
		}
	}
	return -1;
}

// Opt O(N) time. Similar to max sub array
int canTravelOpt(std::vector<int>& gas, std::vector<int>& cost) {
	int runningContrib = 0; // track current contributions
	int totalContrib = 0; // track global contributions
	int start = 0;

	for (size_t i = 0; i < gas.size(); ++i) {
		int remaining = gas[i] - cost[i];
		totalContrib += remaining;

		//if sum remaining of (i-1) >= 0, add the contribution of this gas station.
		if (runningContrib >= 0) {
			runningContrib += remaining;
		//otherwise, reset start index to be current. Reset contribution to be current contrib
		} else {
			runningContrib = remaining;
			start = i;
		}
	}

	return totalContrib >= 0 ? start : -1;
}

int main() {
//	std::vector<int> gas{8, 4, 1}, cost{1, 6, 6};
	std::vector<int> gas{8, 6, 30, 9, 15, 21, 2, 18}, cost{15, 8, 2, 6, 18, 9, 21, 30};
	std::cout << "BF: " << canTravel(gas, cost) << '\n' << "Opt: ";
	std::cout << canTravelOpt(gas, cost);
}
