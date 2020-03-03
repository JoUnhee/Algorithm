#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int cache[101][101];


string W, S;
int C;
int n;

int match(int w, int s) {
	int& ret = cache[w][s];

	if (ret != -1) return ret;

	while (s < S.size() && w < W.size() && (W[w] == S[s] || W[w] == '?' )) {
		w++, s++;
	}

	if (w == W.size()) {
		return ret = (s == S.size());
	}
	if (W[w] == '*') {
		for (int skip = 0; skip + s <= S.size(); skip++) {
			if (match(w + 1, s+skip)) {
				return ret = 1;
			}
		}
	}

	return ret = 0;
}
void _init() {
	memset(cache, -1, sizeof(cache));
}
void _input() {
	cin >> C;

	for (int c = 1; c <= C; c++) {
		cin >> W;

		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> S;
			_init();

			int ret = match(0, 0);

			if (ret == 0) continue;
			
			cout << S << endl;
		}
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
}