#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

int romanToInt(const std::string& roman) {
	int res = 0;
	const std::unordered_map<std::string, int> rMap{
{"I", 	1},
{"IV", 	4},
{"V", 	5},
{"IX", 	9},
{"X", 	10},
{"XL", 	40},
{"L", 	50},
{"XC", 	90},
{"C", 	100},
{"CD", 	400},
{"D", 	500},
{"CM", 	900},
{"M", 	1000},
	};

	for(size_t i = 0; i < roman.size(); ++i) {
		// In case there's only 1 character remaining, substr(i, 2) will be a 1 char string
		const std::string tmp = roman.substr(i, 2), tmp1 = roman.substr(i, 1);

		if(rMap.count(tmp)) {
			res += rMap.at(tmp);
			++i;
		} else if(rMap.count(tmp1)) {
			res += rMap.at(tmp1);
		} else {
			throw std::runtime_error("Unexpected characters!");
		}
	}
	return res;
}

int main() {
	std::vector<std::string> v{"I", "V", "VII", "XXXV", "XXXVI", "MMXII", "M", "MCMXCVI"};
	for(const auto& str : v) {
		std::cout << str << " : " << romanToInt(str) << '\n';
	}
}


/*
I => 1
V => 5
VII => 7
XXXV => 35
XXXVI => 36
MMXII => 2012
M => 1000
MCMXCVI => 1996
*/

/*
 *  Different algo from GeeksForGeeks, numbers like 4, 9, etc. are not in the map
 *  Algorithm to convert Roman Numerals to Integer Number :

    Split the Roman Numeral string into Roman Symbols (character).
    Convert each symbol of Roman Numerals into the value it represents.
    Take symbol one by one from starting from index 0:
        If current value of symbol is greater than or equal to the value of next symbol, then add this value to the running total.
        else subtract this value by adding the value of next symbol to the running total.
 *
 *  */
