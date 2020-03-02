#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;
typedef struct info {
	int x;
	int y;
	int flag;

	info(int _x,int _y, bool _flag) : x(_x), y(_y), flag(_flag) {}
};
int N, M, T;
int map[101][101];
bool visit[101][101][2];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0, -1,0,1 };

bool isInside(int x, int y) {
	return x >= 1 && x <= M && y >= 1 && y <= N;
}
void _input() {
	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
}
int solve() {
	int t = 0;
	queue<info> q;

	q.push(info(1, 1, 0));
	visit[1][1][0] = true;

	while (t <= T && !q.empty()) {
		int sz = q.size();

		for (int s = 0; s < sz; s++) {
		
			int x = q.front().x;
			int y = q.front().y;
			int gram = q.front().flag;

			q.pop();

			if (map[y][x] == 2) gram = 1;

			if (y == N && x == M) {
				return t;
			}

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!isInside(nx, ny)) continue;
				if (visit[ny][nx][gram]) continue;
				if (gram == 0 && map[ny][nx] == 1)continue;

				visit[ny][nx][gram] = true;
				q.push(info(nx, ny, gram));
			}

		}
		t++;
	}

	return -1;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
	int ret = solve();

	if (ret == -1) {
		cout << "Fail"<<endl;
	}
	else cout << ret << endl;
}