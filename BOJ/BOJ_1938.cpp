#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

typedef struct info {
	int x;
	int y;
	bool flag;

	info(int _x, int _y, bool _flag) : x(_x), y(_y), flag(_flag){}
};

int N;
int T;
char map[50][50];

int dx[5] = { 0,0,-1,1,0 };
int dy[5] = { -1,1,0,0,0 };
bool visit[50][50][2];

int ans;
const int INF = 987654321;
pair<int, int> tree[3];
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
bool isFinish(int mx, int my, bool flag) {
	
	if (flag) {
		for (int cur = -1; cur <= 1; cur++) {
			int ny = my + cur;

			if (!isInside(mx, ny)) return false;
			if (map[ny][mx] != 'E') return false;
		}
	
	}
	else {
		for (int cur = -1; cur <= 1; cur++) {
			int nx = mx + cur;

			if (!isInside(nx, my)) return false;
			if (map[my][nx] != 'E') return false;
		}
	}
	
	return true;
}
bool check(int mx, int my, bool flag, int dir) {
	if (dir < 4) {
		if (flag == true) {
			for (int cur = -1; cur <= 1; cur++) {
				int ny = my + cur;

				if (!isInside(mx, ny)) return false;
				if (map[ny][mx] == '1') return false;
			}
		}
		else {
			for (int cur = -1; cur <= 1; cur++) {
				int nx = mx + cur;
				if (!isInside(nx, my)) return false;
				if (map[my][nx] == '1') return false;
			}
		}
	}
	else {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int ny = my + i;
				int nx = mx + j;

				if (!isInside(nx, ny)) return false;
				if (map[ny][nx] == '1') return false;
			}
		}
	}
	return true;
}
int BFS(int _x, int _y, int _flag) {
	queue<info> q;

	q.push(info(_x, _y, _flag));
	visit[_y][_x][_flag] = true;
	int cnt = 0;
	while (!q.empty()) {
		int sz = q.size();
		for (int s = 0; s < sz; s++) {
			int x = q.front().x;
			int y = q.front().y;
			bool flag = q.front().flag;

			q.pop();

			if (isFinish(x, y, flag)) {
				return cnt;
			}

			for (int i = 0; i < 5; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				bool nf = (i == 4 ? flag ^ 1 : flag);

				if (!isInside(nx, ny)) continue;
				if (!check(nx, ny, flag, i)) continue;
				if (visit[ny][nx][nf]) continue;

				visit[ny][nx][nf] = true;
				q.push(info(nx, ny, nf));
			}
		}
		cnt++;
	}
	return 0;
}
void _init() {
	memset(visit, 0, sizeof(visit));
	memset(map, 0, sizeof(map));
	ans = INF;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_init();

	cin >> N;
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'B') {
				tree[cnt].first = i;
				tree[cnt].second = j;
				cnt++;
			}
		}
	}
	bool flag = false;
	// true = ¼¼·Î
	flag = (tree[0].first == tree[1].first ? false : true);
	ans = BFS(tree[1].second, tree[1].first, flag);
	cout << ans << endl;

}