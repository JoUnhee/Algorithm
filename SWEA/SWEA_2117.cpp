#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int T, N, M;

int MAP[20][20];
int ret = 0;
int H;
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
void init() {
	ret = 0; H = 0;
	memset(MAP, 0, sizeof(MAP));
}
void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) H++;
		}
	}

}
void check(int x, int y, int K) {
	int cnt = 0;
	for (int i = 1; i < K; i++) {
		int top = y - (K - i);
		int bottom = y + (K - i);
		int std = 2 * i - 1;
		int cursor = std / 2;

		for (int nx = x - cursor; nx <= x + cursor; nx++) {
			if (isInside(nx, top) && MAP[top][nx] == 1) cnt++;
			if (isInside(nx, bottom) && MAP[bottom][nx] == 1) cnt++;
		}
	}

	int std = 2 * K - 1;
	int cursor = std / 2;

	for (int nx = x - cursor; nx <= x + cursor; nx++) {
		if (isInside(nx, y) && MAP[y][nx] == 1) cnt++;
	}

	int cost = K * K + (K - 1) * (K - 1) - M*cnt;
	if (cost <= 0) {
		ret = max(ret, cnt);
	}

}

void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		init();
		_input();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 1; k <= N+1; k++) {
					if (H * M < (k * k + (k - 1) * (k - 1))) break;
					check(j, i, k);
				}
			}
		}

		cout << "#" << t << " " << ret << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}