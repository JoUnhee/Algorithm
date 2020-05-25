#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>

#define MAXH 32
#define MAXN 11
#define INF 2e9

using namespace std;

int N, M, H;
int m;

int map[MAXH][MAXN];
int ans;

void _init() {
	memset(map, 0, sizeof(map));
	ans = INF;

}
void _input() {
	cin >> N >> M >> H;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;

		map[a][b] = 1;
	}
}
bool simul() {
	
	for (int st = 1; st <= N; st++) {
		int x = st;

		for (int y = 1; y <= H; y++) {
			if (map[y][x] == 1) x++;
			else if (map[y][x - 1] == 1) x--;
		}

		if (x != st) return false;
	}
	return true;
}
bool DFS(int y,int cnt) {
	bool ret = false;

	if (cnt == m) {
		ret = simul();
		return ret;
	}
	else {
		for (int i = y; i <= H; i++) {
			for (int x = 1; x <= N-1; x++) {
				if (map[i][x] == 0 && map[i][x - 1] == 0 && map[i][x + 1] == 0) {
					map[i][x] = 1;
					ret = DFS(i, cnt + 1);
					map[i][x] = 0;

					if (ret) return ret;
				}
			}
		}
	}
	return ret;
}

void solve() {

	_init();
	_input();

	for (m = 0; m <= 3; m++) {
		if (DFS(1, 0)) {
			ans = m;
			break;
		}
	}
	if (ans == INF) ans = -1;
	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}