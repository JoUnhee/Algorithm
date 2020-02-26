#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int T;
int D, W, K;

int film[13][20];
int chemical[13];
int ret = 0;
void setup() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
}
void init() {
	memset(film, 0, sizeof(film));
	ret = 987654321;
}
void _input() {
	cin >> D >> W >> K;

	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			cin >> film[i][j];
		}
	}

}
void DFS(int depth, int prev[],int prevMax[], int cnt) {
	if (cnt >= ret) return;
	if (depth >= D) {
		for (int w = 0; w < W; w++) {
			if (prevMax[w] < K) return;
		}

		ret = min(ret, cnt);
	}
	else {
		int curMax[20];
		int cur[20];
		int curCell;
		int prevCell;
		for (int che = 2; che >= 0; che--) {
			chemical[depth] = che;

			for (int w = 0; w < W; w++) {
				curCell = (chemical[depth] == 2 ? film[depth][w] : chemical[depth]);
				prevCell = (chemical[depth - 1] == 2 ? film[depth - 1][w] : chemical[depth - 1]);

				cur[w] = (curCell == prevCell ? prev[w] + 1 : 1);
				curMax[w] = max(prevMax[w], cur[w]);

			}

			DFS(depth + 1, cur, curMax, (che == 2 ? cnt : cnt + 1));
		}
	}
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		init();
		_input();

		ret = K;

		int prev[20];
		int prevMax[20];

		for (int i = 2; i >= 0; i--) {
			chemical[0] = i;
			for (int j = 0; j < W; j++) {
				prev[j] = prevMax[j] = 1;
			}
			DFS(1, prev, prevMax,i == 2 ? 0 : 1);
		}

		cout << "#" << t << " "<< ret << endl;

	}
}
int main() {

	setup();
	solve();


}