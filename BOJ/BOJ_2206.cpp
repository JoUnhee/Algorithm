#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
typedef struct Point {
	int x;
	int y;
	bool flag;

	Point(int _x, int _y, bool _flag = true) : x(_x), y(_y), flag(_flag) {}
};

int N, M;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int map[1000][1000];
bool visit[1000][1000][2];

void _input() {
	cin >> N >> M;

	for(int i = 0 ; i < N; i++){
		for (int j = 0; j < M; j++) {
			char num;
			cin >> num;
			map[i][j] = num - '0';
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
int solve() {
	
	queue<Point> q;

	q.push(Point(0, 0));
	visit[0][0][1] = true;
	int cnt = 1;
	while (!q.empty()) {
		int sz = q.size();

		for (int s = 0; s < sz; s++) {
			int x = q.front().x;
			int y = q.front().y;
			bool f = q.front().flag;

			q.pop();

			if (y == N - 1 && x == M - 1) {
				return cnt;
			}

			if (map[y][x] == 1) f = false;

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (!isInside(nx, ny)) continue;
				if (visit[ny][nx][f]) continue;
				if (map[ny][nx] == 1 && !f) continue;

				visit[ny][nx][f] = true;
				q.push(Point(nx, ny, f));
			}
		}
		cnt++;
	}

	return -1;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
	cout << solve() << endl;
}