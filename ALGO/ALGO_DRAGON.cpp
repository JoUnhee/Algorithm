#include<cstring>
#include<iostream>
#include<algorithm>
#include<cassert>
using namespace std;

const int MAX = 1000000000 + 1;

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

int Length[51];

void precal() {
	Length[0] = 1;

	for (int i = 1; i <= 50; i++) {
		Length[i] = min(MAX, Length[i - 1] * 2 + 2);
	}
}

char expand(const string& dragon, int n, int skip) {
	
	if (n == 0) {
		assert(skip < dragon.size());
		return dragon[skip];
	}

	for (int i = 0; i < dragon.size(); i++) {
		if (dragon[i] == 'X' || dragon[i] == 'Y') {
			if (skip >= Length[n]) {
				skip -= Length[n];
			}
			else if (dragon[i] == 'X') {
				return expand(EXPAND_X, n - 1, skip);
			}
			else if (dragon[i] == 'Y') {
				return expand(EXPAND_Y, n - 1, skip);
			}
		}
		else if (skip > 0) skip--;
		else return dragon[i];
	}
}

void _solve() {
	int C, N, P, L;
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;
	precal();
	for (int t = 1; t <= C; t++) {
		cin >> N >> P >> L;

		string ans = "";

		for (int i = 0; i < L; i++) {
			ans += expand("FX", N, P+i-1);
		}
		cout << ans << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_solve();
}