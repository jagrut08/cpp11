#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
using namespace std;

string toBinary(int n) {

	string res;

	while (n) {

		if (n % 2) res.append("1");
		else res.append("0");

		n /= 2;
	}

	reverse(res.begin(), res.end());
	return res;
}

int main() {
	int n, m, first, sec, wt, tot=0;
	cin >> n >> m;

	vector<vector<int>> v(n + 1);
	fill(v.begin(), v.end(), vector<int>(n + 1, INT_MAX));

	while (m--) {
		cin >> first >> sec >> wt;

		if( v[first][sec] == INT_MAX) v[first][sec] = v[sec][first] = pow(2, wt);
		else v[first][sec] = v[sec][first] = min((int) pow(2, wt), v[first][sec]);
	}

	for (int i = 1; i <= n; ++i) v[i][i] = 0;

	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {

				if (i == j) continue;

				if (v[i][k] == INT_MAX || v[k][j] == INT_MAX ) continue;

				if (v[i][j] > v[i][k] + v[k][j]) {
					v[i][j] = v[i][k] + v[k][j];
					v[j][i] = v[i][j];
				}
			
				//cout << i << ":" << k << ":" << j<< ":" << v[i][j] << '\n';
			}

	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) tot += v[i][j];

	//cout << tot << '\n';

	cout << toBinary(tot) << '\n';
}
