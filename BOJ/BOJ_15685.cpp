#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int ans;

bool map[102][102];

int dx[4] = { 1,0,-1,0 };

int dy[4] = { 0,-1,0,1 };


void _input() {
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		int x, y, d, g;

		cin >> x >> y >> d >> g;

		vector<int> curve;
		curve.push_back(d);

		for (int i = 0; i < g; i++) {
			vector<int> merge;

			for (int j = curve.size() - 1; j >= 0; j--) {
				int dir = curve[j];
				merge.push_back((dir + 1) % 4);
			}
			for (int j = 0; j < merge.size(); j++) {
				curve.push_back(merge[j]);
			}
		}

		for (int i = 0; i < curve.size(); i++) {
			map[y][x] = 1;
			x += dx[curve[i]];
			y += dy[curve[i]];
		}
		map[y][x] = 1;
	}
}
void _init() {
	memset(map, 0,sizeof(map));
	ans = 0;
}
int cnt() {
	int ret = 0;
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j] == 1 && map[i + 1][j + 1] == 1) ret++;
		}
	}
	return ret;
}
void solve() {

	_init();
	_input();

	ans = cnt();

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}