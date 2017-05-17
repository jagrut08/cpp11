#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

// BF
std::vector<std::string> getValidWords(const std::string& startWord, const std::unordered_set<std::string>& visited, const std::unordered_set<std::string>& dict) {
	std::vector<std::string> res;
	for(size_t i = 0; i < startWord.size(); ++i) {
			for(char c = 'a'; c <= 'z'; ++c) {
				if(startWord[i] == c) {
					continue;
				}
				std::string newWord{startWord};
				newWord[i] = c;
				if(dict.count(newWord) && !visited.count(newWord)) {
					res.emplace_back(newWord);
				}
			}
		}
	return res;
}

// O(D) time, O(D) space, D is size of dictionary
bool getWordsRecur(const std::string& startWord, const std::string& endWord, const std::unordered_set<std::string>& dict, std::unordered_set<std::string>& visited, std::vector<std::string>& seq) {
	visited.insert(startWord);
	seq.emplace_back(startWord);
	if(startWord == endWord) {
		return true;
	}
	const std::vector<std::string>& validWords = getValidWords(startWord, visited, dict);
	for(const auto& word : validWords) {
		if(getWordsRecur(word, endWord, dict, visited, seq)) {
			return true;
		}
	}
	visited.erase(startWord);
	seq.pop_back();
	return false;
}

std::vector<std::string> getWords(const std::string& startWord, const std::string& endWord, const std::unordered_set<std::string>& dict) {
	if(startWord.empty() || endWord.empty() || startWord.size() != endWord.size()) {
		throw std::runtime_error("Invalid input");
	}
	std::unordered_set<std::string> visited;
	std::vector<std::string> seq; // To print sequence
	getWordsRecur(startWord, endWord, dict, visited, seq);
	return seq;
}

// Opt. Overall logic remains the same, getValidWords uses pre-processed dict, map of <wild card with 1 letter change, list of matching words>. Additionally, the set of wildcards for a word could also be cached.
std::vector<std::string> getWildCards(const std::string& word) {
	std::vector<std::string> res(word.size());
	for(size_t i = 0; i < word.size(); ++i) {
		res[i] = word.substr(0, i) + "_" + word.substr(i + 1);
	}
	return res;
}

std::vector<std::string> getValidWordsUsingWildcards(const std::string& word, std::unordered_map<std::string, std::vector<std::string>>& wildCardsMap) {
	std::vector<std::string> res;
	const auto& wcs = getWildCards(word);
	for(const auto& wc : wcs) {
		const auto& matches = wildCardsMap[wc];
		for(const auto& match : matches) {
			if(match != word) {
				res.emplace_back(match);
			}
		}
	}
	return res;
}

bool getWordsRecurOpt(const std::string& startWord, const std::string& endWord, std::unordered_map<std::string, std::vector<std::string>>& wildCardsMap, std::unordered_set<std::string>& visited, std::vector<std::string>& seq) {
	visited.insert(startWord);
	seq.emplace_back(startWord);
	if(startWord == endWord) {
		return true;
	}
	const std::vector<std::string>& validWords = getValidWordsUsingWildcards(startWord, wildCardsMap);
	std::cout << "\nstartWord = " << startWord << " ";

	for(const auto& word : validWords) {
		std::cout << "validWord = " << word << " ";
		if(!visited.count(word) && getWordsRecurOpt(word, endWord, wildCardsMap, visited, seq)) {
			return true;
		}
	}
	visited.erase(startWord);
	seq.pop_back();
	return false;
}

void printWildCardsMap(const std::unordered_map<std::string, std::vector<std::string>>& wildCardsMap) {
	for(const auto& it : wildCardsMap) {
		std::cout << it.first << " : ";
		for(const auto& wd : it.second){
			std::cout << wd << " ";
		}
		std::cout << '\n';
	}
}

std::unordered_map<std::string, std::vector<std::string>> preprocessDict(const std::unordered_set<std::string>& dict) {
	std::unordered_map<std::string, std::vector<std::string>> res;
	for(const auto& word : dict) {
		const auto& wcs = getWildCards(word);
		for(const auto& wc : wcs) {
			if(!res.count(wc)) {
				res[wc] = std::vector<std::string>{};
			}
			res[wc].emplace_back(word);
		}
	}
	return res;
}

std::vector<std::string> getWordsOpt(const std::string& startWord, const std::string& endWord, const std::unordered_set<std::string>& dict) {
	if(startWord.empty() || endWord.empty() || startWord.size() != endWord.size()) {
		throw std::runtime_error("Invalid input");
	}
	std::unordered_set<std::string> visited;
	std::vector<std::string> seq; // To print sequence
	std::unordered_map<std::string, std::vector<std::string>> wildCardsMap = preprocessDict(dict);
	printWildCardsMap(wildCardsMap);
	getWordsRecurOpt(startWord, endWord, wildCardsMap, visited, seq);
	return seq;
}

int main() {
	const std::string startWord{"damp"}, endWord{"like"};
	const std::unordered_set<std::string> dict{"damp", "like", "lamp", "limp", "lime", "dime"};
//	const auto& res = getWords(startWord, endWord, dict);
	const auto& res = getWordsOpt(startWord, endWord, dict);

	std::cout << "\nAnswer: ";
	for(const auto& val : res) {
		std::cout << val << " -> ";
	}
}
